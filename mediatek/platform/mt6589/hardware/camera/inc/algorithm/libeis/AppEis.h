#ifndef _APP_EIS_H
#define _APP_EIS_H


#include "MTKEis.h"


/*****************************************************************************
	Class Define
******************************************************************************/
class AppEis : public MTKEis {
public:    
	static MTKEis* getInstance();
    virtual void destroyInstance();
    
    AppEis();
    virtual ~AppEis();   
    // Process Control
	MRESULT EisInit(void* InitInData);
	MRESULT EisMain(EIS_RESULT_INFO_STRUCT *pEisResult);
	MRESULT EisReset();   //Reset

	// Feature Control
	MRESULT EisFeatureCtrl(MUINT32 FeatureID, void* pParaIn, void* pParaOut);
private:
};


#endif
