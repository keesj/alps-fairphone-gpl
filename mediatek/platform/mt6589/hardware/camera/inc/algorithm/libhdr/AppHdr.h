#ifndef _APP_HDR_H
#define _APP_HDR_H


#include "MTKHdr.h"

#define HDR_LOG_BUFFER_SIZE 128


/*****************************************************************************
	Class Define
******************************************************************************/
class AppHdr : public MTKHdr {
public:    
    static MTKHdr* getInstance();
    virtual void destroyInstance();
    
    AppHdr();
    virtual ~AppHdr();   
    // Process Control
    MRESULT HdrInit(void* InitInData, void* InitOutData);
    MRESULT HdrMain(HDR_PROC_STATE_ENUM HdrState);
    MRESULT HdrReset();   //Reset
            
	// Feature Control        
	MRESULT HdrFeatureCtrl(MUINT32 FeatureID, void* pParaIn, void* pParaOut);
private:
};


#endif
