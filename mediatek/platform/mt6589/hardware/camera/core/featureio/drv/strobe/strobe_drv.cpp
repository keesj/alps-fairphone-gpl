#define LOG_TAG "StrobeDrv"
#include <utils/Errors.h>
//
#include "MediaTypes.h"
#include "strobe_drv.h"
#include "flashlight_drv.h"

#define DEBUG_STROBE_DRV
#ifdef DEBUG_STROB_DRV
#define STROB_DRV_DBG(fmt, arg...) LOGD(LOG_TAG fmt, ##arg)
#define STROB_DRV_ERR(fmt, arg...) LOGE(LOG_TAG "Err: %5d:, "fmt, __LINE__, ##arg)
#else
#define STROB_DRV_DBG(a,...)
#define STROB_DRV_ERR(a,...)
#endif


/*******************************************************************************
*
********************************************************************************/
StrobeDrv::~StrobeDrv()
{
}

/*******************************************************************************
*
********************************************************************************/
StrobeDrv*   
StrobeDrv::createInstance()
{
    return FlashlightDrv::getInstance();
}

