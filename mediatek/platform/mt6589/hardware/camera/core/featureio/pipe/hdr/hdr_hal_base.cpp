#define LOG_TAG "hdr_hal_base"
     
#include "hdr_hal_base.h"
#include "hdr_hal.h"


     
/*******************************************************************************
*
********************************************************************************/
HdrHalBase* 
HdrHalBase::createInstance()
{
    return HdrHal::getInstance();
}

