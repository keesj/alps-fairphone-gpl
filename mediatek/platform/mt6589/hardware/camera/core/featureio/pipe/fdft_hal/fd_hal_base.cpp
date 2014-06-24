#define LOG_TAG "fd_hal_base"
     
#include <stdlib.h>
#include <stdio.h>
#include <cutils/log.h>
#include "fd_hal_base.h"
//#include "fd_hal.h"
#include "fdvt_hal.h"
     
/*******************************************************************************
*
********************************************************************************/
halFDBase* 
halFDBase::createInstance(HalFDObject_e eobject)
{
    if (eobject == HAL_FD_OBJ_SW) {
        return halFDVT::getInstance();
    }
    else if (eobject == HAL_FD_OBJ_HW) {
        return halFDVT::getInstance();
    }
    else if (eobject == HAL_FD_OBJ_FDFT_SW) {
        return halFDVT::getInstance();
    }    
    else {
        return halFDTmp::getInstance();
    }

    return NULL;
}

/*******************************************************************************
*
********************************************************************************/
halFDBase*
halFDTmp::
getInstance()
{
    //LOGD("[halFDTmp] getInstance \n");
    static halFDTmp singleton;
    return &singleton;
}

/*******************************************************************************
*
********************************************************************************/
void   
halFDTmp::
destroyInstance() 
{
}

