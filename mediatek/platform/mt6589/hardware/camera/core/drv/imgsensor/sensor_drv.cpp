#define LOG_TAG "SensorDrv"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
//
#include "imgsensor_drv.h"
#include "atvsensor_drv.h"

/*******************************************************************************
*
********************************************************************************/
SensorDrv* 
SensorDrv::createInstance(MINT32 sensorDev)
{
    if ((sensorDev & SENSOR_MAIN) || (sensorDev & SENSOR_MAIN_2) ||(sensorDev & SENSOR_SUB)) {
        return ImgSensorDrv::getInstance();
    }
    else {
        return AtvSensorDrv::getInstance();
    }
}

/*******************************************************************************
*
********************************************************************************/
MINT32
SensorDrv::searchSensor(pfExIdChk pExIdChkCbf)
{
    return ImgSensorDrv::getInstance()->impSearchSensor(pExIdChkCbf);
}

