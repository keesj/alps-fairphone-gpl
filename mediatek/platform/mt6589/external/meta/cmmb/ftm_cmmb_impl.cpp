// ftm_cmmb_impl.c - Factory Test Module of CMMB, implementation
//
#include <string.h>
#include "ftm_cmmb_api.h"
#include "CmmbHelper.h"
#include "CmmbAdapter.h"
#ifdef CMMB_CHIP_INNO
#include "InnoAppDriver.h"
#endif

typedef enum
{
	CMMB_NONE = 0,
	CMMB_IDLE,		// after init
	CMMB_READY,		// after Tune
	CMMB_PLAYING,	// after StartService
	CMMB_ERROR,
} CMMB_STATE;

static CMMB_STATE g_cmmbState = CMMB_NONE;
static int g_curChannel = 0;
static int g_curSrvId = 0;

int cmmbFrequency[]=
{
	474000000,482000000,490000000,498000000,506000000,514000000,522000000,530000000,538000000,
	546000000,554000000,562000000,610000000,618000000,626000000,634000000,642000000,650000000,
	658000000,666000000,674000000,682000000,690000000,698000000,706000000,714000000,722000000,
	730000000,738000000,746000000,754000000,762000000,770000000,778000000,786000000,794000000
};

#define CMMB_CHANNEL_MIN	13
#define CMMB_CHANNEL_MAX	48

inline bool IsValidCmmbChannel(int channel)
{
	return CMMB_CHANNEL_MIN <= channel
		&& channel <= CMMB_CHANNEL_MAX;
}

inline int CmmbFreqFromChannel(int channel)
{
	return cmmbFrequency[channel-CMMB_CHANNEL_MIN];
}

CmmbResult CmmbFtInit()
{
	CmmbResult errCode;

	// initialize host library
	errCode = HostLibInit();
	cmmb_build_crc_table();

	if (errCode == CMMB_S_OK)
	{
		// update service provider state
		g_cmmbState = CMMB_IDLE;

		SP_LOGE( "CmmbFtInit() OK");
	}
	else
	{
		SP_LOGE( "CmmbInit() error");
	}

	return errCode;
}

CmmbResult CmmbFtTerm()
{
	// terminage host library
	HostLibTerminate();

	// update service provider state
	g_cmmbState = CMMB_NONE;

	return CMMB_S_OK;
}

CmmbResult CmmbFtAutoScan(CMMB_AUTOSCAN_CALLBACK scanProc)
{
        CmmbResult ret;
	if (scanProc == null)
		return CMMB_E_INVALID_ARG;

	for (int ch = CMMB_CHANNEL_MIN; ch <= CMMB_CHANNEL_MAX; ch++)
	{
		SP_LOGE( "scan test channel: %d", ch);
                ret = CmmbFtChannelTest(ch);
		if (ret == CMMB_S_OK)
		{
			SP_LOGE( "channel: %d has signal", ch);

			int freq = CmmbFreqFromChannel(ch);

			if (scanProc(ch, freq) == 0)
				break;
		}
		else if(ret == CMMB_E_TIMEOUT){            // tune fail,stop auto scan
                   return ret; 
		}
	}

	return CMMB_S_OK;
}

CmmbResult CmmbFtChannelTest(int channel)
{
        CmmbResult ret;
	if (!IsValidCmmbChannel(channel))
		return CMMB_E_INVALID_ARG;

	if (g_cmmbState == CMMB_NONE)
		return CMMB_E_WRONGSTATE;

        ret = Tune(channel);
	return ret;
}

CmmbResult CmmbFtSetChannel(int channel)
{
	if (!IsValidCmmbChannel(channel))
		return CMMB_E_INVALID_ARG;

	if (g_cmmbState == CMMB_NONE)
		return CMMB_E_WRONGSTATE;

	// check current channel
	if (g_curChannel == channel)
	{
		return CMMB_S_OK;
	}

	CmmbResult errCode;

	errCode = Tune(channel);

	if (errCode != CMMB_S_OK)
	{
		return errCode;
	}

	errCode = StartTs0();

	if (errCode != CMMB_S_OK)
	{
		return errCode;
	}

	errCode = StopTs0();

	if (errCode != CMMB_S_OK)
	{
		return errCode;
	}

	errCode = ParseTs0();

	if (errCode != CMMB_S_OK)
	{
		return errCode;
	}

	g_cmmbState = CMMB_READY;
	g_curChannel = channel;

	return CMMB_S_OK;
}

CmmbResult CmmbFtListServices(CMMB_SERVICE_CALLBACK srvProc)
{
	if (srvProc == null)
		return CMMB_E_INVALID_ARG;

	if (g_cmmbState != CMMB_READY
		&& g_cmmbState != CMMB_PLAYING)
	{
		return CMMB_E_WRONGSTATE;
	}

	UINT16 numSrvs = CmmbGetDemuxer().m_CSct.NumServices;

	for (UINT16 i = 0; i < numSrvs; i++)
	{
		if (srvProc(CmmbGetDemuxer().m_CSct.ServiceIdArr[i]) == 0)
			break;
	}

	return CMMB_S_OK;
}


CmmbResult CmmbFtStartService(int serviceId, const char* szMfsFile)
{
	if (g_cmmbState == CMMB_PLAYING
		&& g_curSrvId == serviceId)
	{
		return CMMB_S_OK;
	}

	if (g_cmmbState != CMMB_READY)
		return CMMB_E_WRONGSTATE;

	if (StartService(serviceId) == CMMB_S_OK)
	{
		g_cmmbState = CMMB_PLAYING;
		g_curSrvId = serviceId;

		mfsWriter.close();

		if (szMfsFile != null)
		{
			mfsWriter.open(szMfsFile);
		}
		else
		{
                    SP_LOGD("szMfsFile ==NULL, not save mfs");
		}
	
		return CMMB_S_OK;
	}

	return CMMB_E_UNKNOWN;
}

CmmbResult CmmbFtStopService()
{
	if (g_cmmbState == CMMB_PLAYING)
	{
		if (StopService() == CMMB_S_OK)
		{
			g_cmmbState = CMMB_READY;
			mfsWriter.close();

			return CMMB_S_OK;
		}
		else
			return CMMB_E_UNKNOWN;
	}
	else
		return CMMB_E_WRONGSTATE;
}

//CmmbResult CmmbFtGetProp(int propId, int* propVal)
CmmbResult CmmbFtGetProp(CmmbProps* props)
{
#if 0
	if (propVal == null)
		return CMMB_E_INVALID_ARG;

	int statId = 0;

	switch (propId)
	{
	case CMMB_PROP_SNR:
		statId = STATTYPE_SIGNAL_STRENGTH;
		break;

	case CMMB_PROP_PRE_BER:
		statId = STATTYPE_BER_COUNT;
		break;

	case CMMB_PROP_RSSI:
		statId = STATTYPE_SNR_COUNT;
		break;

	default:
		SP_LOGE( "error! unknown property ID");
		return CMMB_E_INVALID_ARG;
	}

	*propVal = GetSystemStatus(statId);
#else
       CmmbResult ret;
	ret = GetSystemStatus(props);
#endif
	return CMMB_S_OK;
}
