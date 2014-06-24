#define LOG_TAG "autorama_hal_base"
     
#include <stdlib.h>
#include <stdio.h>
#include <common/CamLog.h>
#include <common/CamTypes.h>
#include "autorama_hal_base.h"
#include "autorama_hal.h"
     
/*******************************************************************************
*
********************************************************************************/
halAUTORAMABase* 
halAUTORAMABase::createInstance(HalAUTORAMAObject_e eobject)
{
    if (eobject == HAL_AUTORAMA_OBJ_AUTO) {
        return halAUTORAMA::getInstance();
    }
       
    else {
        return halAUTORAMATmp::getInstance();
    }

    return NULL;
}

/*******************************************************************************
*
********************************************************************************/
halAUTORAMABase*
halAUTORAMATmp::
getInstance()
{
    CAM_LOGD("[halAUTORAMATmp] getInstance \n");
    static halAUTORAMATmp singleton;
    return &singleton;
}

/*******************************************************************************
*
********************************************************************************/
void   
halAUTORAMATmp::
destroyInstance() 
{
}

