#ifndef _SENSOR_HAL_IMP_H_
#define _SENSOR_HAL_IMP_H_


#include <utils/Errors.h>
#include <cutils/log.h>

#include "sensor_hal.h"
#include "sensor_drv.h"
#include <IBaseCamExif.h>


using namespace android;

#ifndef USING_MTK_LDVT
#define LOG_MSG(fmt, arg...)    ALOGD("[%s]"fmt, __FUNCTION__, ##arg)
#define LOG_WRN(fmt, arg...)    ALOGD("[%s]Warning(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    ALOGE("[%s]Err(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#else
#include "uvvf.h"

#if 1
#define LOG_MSG(fmt, arg...)    VV_MSG("[%s]"fmt, __FUNCTION__, ##arg)
#define LOG_WRN(fmt, arg...)    VV_MSG("[%s]Warning(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    VV_ERRMSG("[%s]Err(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#else
#define LOG_MSG(fmt, arg...)    
#define LOG_WRN(fmt, arg...)    
#define LOG_ERR(fmt, arg...)    
#endif   
#endif

/*******************************************************************************
*
********************************************************************************/
class SensorHalImp : public SensorHal {
public:
    static SensorHal* getInstance();
    virtual void destroyInstance();
//
private:
    SensorHalImp();
    virtual ~SensorHalImp();
//
public:
    virtual MINT32 searchSensor();
    //
    virtual MINT32 init();
    //
    virtual MINT32 uninit();
    //
    virtual MINT32 setATVStart();
	//
    virtual MINT32 setConf(halSensorIFParam_t halSensorIFParam[2]);
    //
    virtual MINT32 sendCommand(
    	halSensorDev_e cameraId,
        int cmd,
        int arg1 = 0,
        int arg2 = 0,
        int arg3 = 0);
    //
    virtual MINT32 dumpReg();  
	//
	virtual MINT32 setDebugInfo(IBaseCamExif *pIBaseCamExif);
//
	virtual MINT32 reset();
//
private:
    MINT32 mSensorDev;
	static MINT32 mSearchSensorDev;
    halSensorType_e mIspSensorType[2];
    MINT32 mImageSensorType[2];
    mutable Mutex mImpLock;
    mutable Mutex mLock;
    volatile int mUsers;
    volatile int mInit;
	ACDK_SCENARIO_ID_ENUM mSensorScenarioId[2];
	SENSOR_DEV_ENUM mCameraId[2];
	
    //
    MINT32 createImp();
    //
    MINT32 deleteImp();
    //
    MINT32 initSensor();
    //
    MINT32 openSensor();
    //
    MINT32 getSensorInfo(ACDK_SCENARIO_ID_ENUM mode[2]);
    //
    MINT32 setTgPhase();
    //
    MINT32 initCSI2Peripheral(MINT32 initCSI2);
    //
    MINT32 setCSI2Config(MINT32 enableCSI2);
    //
    MINT32 setSensorIODrivingCurrent();
    //
    MINT32 getRawInfo(halSensorDev_e sensorDevId,halSensorRawImageInfo_t *pinfo, MINT32 mode = 0);
    //
    MINT32 querySensorInfo();


};

#endif //_SENSOR_HAL_IMP_H_

