// CmmbAdapterInno.cpp - CMMB hostlib adapter layer, Innofidei version
//
#include "CmmbHelper.h"
#include "CmmbAdapter.h"
#include "InnoAppDriver.h"

#define TS0_BPSK_DEMOD			0x04
#define SERVICE_HANDLE_OFFSET	2

bool channelState[2] = { true, true };
bool startTs0 = false;
BYTE g_curSrvHdl = 0;

CmmbResult ErrCodeFromInno(INNO_RET res)
{
	CmmbResult errCode;

	switch (res)
	{
	case INNO_NO_ERROR:
		errCode = CMMB_S_OK;
		break;

	case INNO_TIMEOUT_ERROR:
		errCode = CMMB_E_TIMEOUT;
		break;

	case INNO_PARAMETER_ERROR:
		errCode = CMMB_E_INVALID_ARG;
		break;

	default:
		errCode = CMMB_E_UNKNOWN;
		break;
	}

	return errCode;
}

void InnoMpxFrameCallBack(BYTE *buffer, int buf_size, BYTE channel_id)
{
	UINT32 serviceHdl = 0;

	if (startTs0)
	{
		serviceHdl = SERVICE_HANDLE_TS0;
	}
	else
	{
		serviceHdl = channel_id+SERVICE_HANDLE_OFFSET;
	}

	// send data to common data processing function
	UserDataCallback(serviceHdl, buffer, buf_size);
}

CmmbResult HostLibInit()
{
	INNO_RET res;
	res = InnoAppDriverInit(InnoMpxFrameCallBack);
	return ErrCodeFromInno(res);
}

CmmbResult HostLibTerminate()
{
	INNO_RET res;
	res = InnoAppDriverDeinit();
	return ErrCodeFromInno(res);
}

CmmbResult Tune(int channel)
{
	channelState[0] = true;
	channelState[1] = true;

	INNO_RET res;
	res = InnoSetTunerFrequency((BYTE)channel);

	return ErrCodeFromInno(res);
}

CmmbResult StartTs0()
{
	CmmbResult errCode;
	INNO_RET res;

	g_curReq = REQ_START_TS0;
	g_rspEvent.Clear();
	startTs0 = true;

	// send request
	res = InnoSetChannelConfig(0, 0, 1, TS0_BPSK_DEMOD, 0);

	if (res == INNO_NO_ERROR)
	{
		// wait for response
		errCode = g_rspEvent.Wait(CMMB_CMD_RES_MAX_TIME);
		g_curReq = REQ_NONE;
	}
	else
		errCode = ErrCodeFromInno(res);

	SP_LOGE("res: %d", res);

	startTs0 = false;
	return errCode;
}

CmmbResult StopTs0()
{
	INNO_RET res;
	res = InnoCloseChannel(0);
	SP_LOGE( "res: %d", res);
	return ErrCodeFromInno(res);
}

BYTE GetMpxFrameDemod(MTKCmmbParserMpxFrame& mpxFrm)
{
	BYTE demode =((mpxFrm.Constellation<<6 & 0xC0)
			| (mpxFrm.RsCr<<4 & 0x30)
			| (mpxFrm.InterleavingMode<<2 & 0x0C)
			| (mpxFrm.LdpcCr & 0x03));

	return demode;
}

CmmbResult StartService(int serviceId)
{
	SP_LOGE( "INNO enter");

	// get service information from service ID
	MTKCmmbParserMpxFrame* mpxFrm = FindMpxFrameInfo(serviceId);

	if (mpxFrm == null)
	{
		SP_LOGE( "FindMpxFrameInfo failed!");
		return CMMB_E_INVALID_ARG;
	}

	// find channel
	BYTE channel_id = 0xFF;

	if (channelState[1])
		channel_id = 1;
	else if (channelState[0])
		channel_id = 0;
	else
	{
		SP_LOGE( "error: has no empty channel!");
		return CMMB_E_WRONGSTATE;
	}

	// start service
	INNO_RET res;
	BYTE demod = GetMpxFrameDemod(*mpxFrm);

	SP_LOGE( "channel_id: %d, firtsTS: %d, ts count: %d, demod: %d", channel_id, mpxFrm->FirstTimeslot, mpxFrm->NumTimeSlots, demod);

	res = InnoSetChannelConfig(channel_id, mpxFrm->FirstTimeslot, mpxFrm->NumTimeSlots, demod, 0);

	if (res == INNO_NO_ERROR)
	{
		channelState[channel_id] = false;

		// save service handle
		g_curSrvHdl = channel_id+SERVICE_HANDLE_OFFSET;
	}

	return ErrCodeFromInno(res);
}

CmmbResult StopService()
{
	INNO_RET res;
	BYTE channel_id = g_curSrvHdl-SERVICE_HANDLE_OFFSET;

	res = InnoCloseChannel(channel_id);

	if (res == INNO_NO_ERROR)
		channelState[channel_id] = true;

	return ErrCodeFromInno(res);
}

CmmbResult GetSystemStatus(CmmbProps* props)
{
#if 0
	UINT32 status = 0;
	inno_sys_state state = inno_sys_state();
	state.stattype = statId;

	INNO_RET ret = InnoGetSysStatus(&state);
	SP_LOGE("stattype: %d, InnoGetSysStatus return %d", statId,  ret);

	if (ret ==INNO_NO_ERROR)
	{
		SP_LOGE(" status: %d", state.statdata.signal_quality);
		status = state.statdata.signal_quality;
	}
	return status;
#else 
	UINT32 status = 0;
       INNO_RET ret;
	inno_sys_state state = inno_sys_state();

	//get signal strength
	state.stattype = STATTYPE_SIGNAL_STRENGTH;
	ret = InnoGetSysStatus(&state);
	SP_LOGE("stattype: %d, InnoGetSysStatus return %d", STATTYPE_SIGNAL_STRENGTH,  ret);

	if (ret !=INNO_NO_ERROR)
	{
		SP_LOGE(" Fail InnoGetSysStatus STATTYPE_SIGNAL_STRENGTH: %d" );
		return ErrCodeFromInno(ret);
	}
	props->RSSI=state.statdata.signal_strength;

       //get SNR
	state.stattype = STATTYPE_SNR_COUNT;
	ret = InnoGetSysStatus(&state);
	SP_LOGE("stattype: %d, InnoGetSysStatus return %d", STATTYPE_SNR_COUNT,  ret);

	if (ret !=INNO_NO_ERROR)
	{
		SP_LOGE(" Fail InnoGetSysStatus STATTYPE_SNR_COUNT: %d" );
		return ErrCodeFromInno(ret);
	}
	props->SNR=state.statdata.SNR;


      //get ber
	state.stattype = STATTYPE_BER_COUNT;
	ret = InnoGetSysStatus(&state);
	SP_LOGE("stattype: %d, InnoGetSysStatus return %d", STATTYPE_BER_COUNT,  ret);

	if (ret !=INNO_NO_ERROR)
	{
		SP_LOGE(" Fail InnoGetSysStatus STATTYPE_BER_COUNT: %d" );
		return ErrCodeFromInno(ret);
	}
	props->PRE_BER=state.statdata.BER;
        return ErrCodeFromInno(ret);
#endif
}

