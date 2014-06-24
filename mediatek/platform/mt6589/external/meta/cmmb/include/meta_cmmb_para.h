#ifndef META_CMMB_PARA_H
#define META_CMMB_PARA_H

// meta_cmmb_para.h
//
#include "cmmb_errcode.h"

#include "FT_Public.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	META_CMMB_CMD_INIT = 0,
	META_CMMB_CMD_TERM,
	META_CMMB_CMD_AUTO_SCAN,
	META_CMMB_CMD_CANCEL_SCAN,
	META_CMMB_CMD_SET_CHANNEL,
	META_CMMB_CMD_LIST_SRVS,
	META_CMMB_CMD_START_SRV,
	META_CMMB_CMD_STOP_SRV,
	META_CMMB_CMD_GET_PROPS,
	META_CMMB_CMD_END
} MetaCmmbCmd;

typedef enum
{
	META_CMMB_PROP_SNR,		
	META_CMMB_PROP_PRE_BER,	
	META_CMMB_PROP_RSSI		
} MetaCmmbProp;

typedef struct
{
	union {
		int channel;		// for META_CMMB_CMD_SET_CHANNEL
		int serviceId;		// for META_CMMB_CMD_START_SRV
	} data;

	char szMfsFile[260];	// for META_CMMB_CMD_START_SRV
} CmmbReqParam;

typedef struct
{
    FT_H                header;
    MetaCmmbCmd     	cmd;
    CmmbReqParam	param;
} MetaCmmbReq;

typedef struct
{
	int channel;
	int freq;
} CmmbChannelInfo;

typedef struct
{
	int SNR;
	int PRE_BER;
	int RSSI;
} CmmbProps;

typedef struct
{
        int flag;                      // 0: continue ,1: finished
        CmmbChannelInfo chInfo;
}CmmbScanChannel;

typedef struct
{
        int flag;                      // 0: continue ,1: finished
        int serviceId;
}CmmbListService;

typedef struct
{
	CmmbResult	errCode;	// command detal result

	union {
//		CmmbChannelInfo chInfo;	// for META_CMMB_CMD_AUTO_SCAN, maybe multi-confirm for this request
//		int serviceId;		// for META_CMMB_CMD_LIST_SRVS, maybe multi-confirm for this request
                CmmbScanChannel scanChn;
                CmmbListService listSrv;
		CmmbProps props;	// for META_CMMB_CMD_GET_PROPS
	} data;
} CmmbCnfParam;

typedef enum
{
	CMMB_CNF_DONE = 0,		// succeeded
	CMMB_CNF_FAIL,			// failed
//	CMMB_CNF_CONTINUE,		// command not finished, maybe more confirm message will arrival
//	CMMB_CNF_FINISHED		// command finished
} CmmbCnfStatus;

typedef struct
{
    FT_H		header;
    MetaCmmbCmd          cmd;
    CmmbCnfStatus	status;		
    CmmbCnfParam	result;
} MetaCmmbCnf;

void META_CMMB_OP(MetaCmmbReq* req);

#ifdef __cplusplus
}
#endif

#endif // META_CMMB_PARA_H
