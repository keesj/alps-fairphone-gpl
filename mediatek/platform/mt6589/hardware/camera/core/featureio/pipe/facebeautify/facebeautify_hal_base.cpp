#define LOG_TAG "facebeautify_hal_base"
     
#include <stdlib.h>
#include <stdio.h>
#include "common/CamLog.h"
#include "common/CamTypes.h"
#include "featureio/facebeautify_hal_base.h"
#include "facebeautify_hal.h"
     
#define LOGD(fmt, arg...)      CAM_LOGD(fmt, ##arg)

/*******************************************************************************
*
********************************************************************************/
halFACEBEAUTIFYBase* 
halFACEBEAUTIFYBase::createInstance(HalFACEBEAUTIFYObject_e eobject)
{
    if (eobject == HAL_FACEBEAUTY_OBJ_SW) {
        return halFACEBEAUTIFY::getInstance();
    }
       
    else {
        return halFACEBEAUTIFYTmp::getInstance();
    }

    return NULL;
}

/*******************************************************************************
*
********************************************************************************/
halFACEBEAUTIFYBase*
halFACEBEAUTIFYTmp::
getInstance()
{
    LOGD("[halFACEBEAUTIFYTmp] getInstance \n");
    static halFACEBEAUTIFYTmp singleton;
    return &singleton;
}

/*******************************************************************************
*
********************************************************************************/
void   
halFACEBEAUTIFYTmp::
destroyInstance() 
{
}

