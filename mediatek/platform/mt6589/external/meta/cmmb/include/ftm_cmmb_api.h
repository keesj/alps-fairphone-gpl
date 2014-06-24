#ifndef FTM_CMMB_API_H
#define FTM_CMMB_API_H
/* 
 * ftm_cmmb_api.h - Factory Test Module of CMMB, interface
 */
#include "cmmb_errcode.h"
#include "meta_cmmb_para.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Return value:
 *	CMMB_S_OK: success, others: fail
 */
CmmbResult CmmbFtInit();

/*
 * Return value:
 *	CMMB_S_OK: success, others: fail
 */
CmmbResult CmmbFtTerm();

/* 
 * Parameters:
 *	int channel	- channel number, from 13 to 48
 *	int freq	- frequency, from 474000000 to 794000000
 * 
 * Return value:
 *	0: break scan, others: continue
 */
typedef int (*CMMB_AUTOSCAN_CALLBACK)(int channel, int freq);

CmmbResult CmmbFtAutoScan(CMMB_AUTOSCAN_CALLBACK scanProc);

/* 
 * Description:
 *	Test if the signal in this channel is available
 *
 * Parameters:
 *	[in] int channel	- channel number, from 13 to 48
 *
 * Return value:
 *	CMMB_S_OK: the channel is valid 
 *	Others: the channel is invalid
 */
CmmbResult CmmbFtChannelTest(int channel);

/* 
 * Description:
 *	Begin receiving the signal from this channel
 *
 * Parameters:
 *	[in] int channel	- channel number, from 13 to 48
 *
 * Return value:
 *	CMMB_S_OK: success, others: fail
 */
CmmbResult CmmbFtSetChannel(int channel);

/* 
 * Parameters:
 *	int serviceId	- service ID
 * 
 * Return value:
 *	0: break callback, others: continue
 */
typedef int (*CMMB_SERVICE_CALLBACK)(int serviceId);

CmmbResult CmmbFtListServices(CMMB_SERVICE_CALLBACK srvProc);

/* 
 * Parameters:
 *	const char* szMfsFile - full path of MFS file
 *
 * Return value:
 *	CMMB_S_OK: success, others: fail
 */
CmmbResult CmmbFtStartService(int serviceId, const char* szMfsFile);

/*
 * Return value:
 *	CMMB_S_OK: success, others: fail
 */
CmmbResult CmmbFtStopService();

#define CMMB_PROP_SNR				1
#define CMMB_PROP_PRE_BER		2
#define CMMB_PROP_RSSI				3

/* 
 * Parameters:
 *	[in] int propId		- property ID
 *	[out]int* propVal	- property value
 *
 * Return value:
 *	CMMB_S_OK: success, others: fail
 */

CmmbResult CmmbFtGetProp(CmmbProps* props);


#ifdef __cplusplus
}
#endif

#endif // FTM_CMMB_API_H
