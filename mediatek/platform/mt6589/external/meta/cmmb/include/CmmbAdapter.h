#ifndef CMMB_ADAPTER_H
#define CMMB_ADAPTER_H
#include "ftm_cmmb_api.h"
// CmmbAdapter.h
//
CmmbResult HostLibInit();
CmmbResult HostLibTerminate();
CmmbResult Tune(int channel);
CmmbResult StartTs0();
CmmbResult StopTs0();
CmmbResult StartService(int serviceId);
CmmbResult StopService();
//int GetSystemStatus(int statId);
CmmbResult GetSystemStatus(CmmbProps* props);

#endif // CMMB_ADAPTER_H
