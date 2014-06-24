#define LOG_TAG "aaa_hal_base"

#include <stdlib.h>
#include <stdio.h>
#include <cutils/log.h>
#include <aaa_types.h>
#include <aaa_error_code.h>
#include "aaa_hal.h"
#include "aaa_hal_yuv.h"
//
#include <sensor_hal.h>

using namespace NS3A;

/*******************************************************************************
*
********************************************************************************/
Hal3ABase*
Hal3ABase::createInstance(MINT32 const i4SensorDevId)
{
    halSensorType_e eSensorType;    // sensor hal defined

    SensorHal* pSensorHal = SensorHal::createInstance();
    if ( !pSensorHal )
    {
        return NULL;
    }
    //
    pSensorHal->sendCommand(static_cast<halSensorDev_e>(i4SensorDevId), 
                            SENSOR_CMD_SET_SENSOR_DEV,
                            0,
                            0,
                            0
                           );
    //
    pSensorHal->init();
    //
    pSensorHal->sendCommand(static_cast<halSensorDev_e>(i4SensorDevId), 
                             SENSOR_CMD_GET_SENSOR_TYPE, 
                             reinterpret_cast<int>(&eSensorType), 
                             0, 
                             0
                            );
    //
    if  ( pSensorHal )
    {
        pSensorHal->uninit();
        pSensorHal->destroyInstance();
        pSensorHal = NULL;
    }
    
    if (eSensorType == SENSOR_TYPE_RAW) {
#ifdef USING_MTK_LDVT
    static Hal3ABase singleton;
    return &singleton;
#else
        return Hal3A::createInstance(i4SensorDevId);
#endif
    }
    else if (eSensorType == SENSOR_TYPE_YUV)
    {
#ifdef USING_MTK_LDVT
         static Hal3ABase singleton;
         return &singleton;
#else
        return Hal3AYuv::createInstance(i4SensorDevId);
#endif        
    }
    else {
#if 1        
    static Hal3ABase singleton;
    return &singleton;        
#else    
    return NULL;//Hal3AYuv::getInstance();
#endif
    }
}

