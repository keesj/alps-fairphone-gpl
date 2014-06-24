#define LOG_TAG "asd_hal_base"
     
#include <stdlib.h>
#include <stdio.h>
#include <cutils/log.h>
#include "asd_hal_base.h"
#include "asd_hal.h"
     
/*******************************************************************************
*
********************************************************************************/
halASDBase* 
halASDBase::createInstance(HalASDObject_e eobject)
{
    if (eobject == HAL_ASD_OBJ_AUTO) {
        return halASD::getInstance();
    }
       
    else {
        return halASDTmp::getInstance();
    }

    return NULL;
}

/*******************************************************************************
*
********************************************************************************/
halASDBase*
halASDTmp::
getInstance()
{
    //LOGD("[halASDTmp] getInstance \n");
    static halASDTmp singleton;
    return &singleton;
}

/*******************************************************************************
*
********************************************************************************/
void   
halASDTmp::
destroyInstance() 
{
}

