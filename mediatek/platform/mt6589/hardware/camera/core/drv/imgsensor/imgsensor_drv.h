#ifndef _IMGSENSOR_DRV_H
#define _IMGSENSOR_DRV_H

#include "sensor_drv.h"
#include "camera_custom_sensor.h"
#include "kd_camera_feature.h"
#include <utils/threads.h>
#include <utils/Errors.h>
#include <cutils/log.h>

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

#define YUV_TUNING_SUPPORT 


/*******************************************************************************
*
********************************************************************************/
class ImgSensorDrv : public SensorDrv {
public:
    static SensorDrv* getInstance();

private:
    ImgSensorDrv();
    virtual ~ImgSensorDrv();

public:
    virtual void destroyInstance();

public:

    virtual MINT32 init(MINT32 sensorIdx);
    virtual MINT32 uninit();
    
    virtual MINT32 open();
    virtual MINT32 close();
    
    virtual MINT32 setScenario(ACDK_SCENARIO_ID_ENUM sId[2],SENSOR_DEV_ENUM sensorDevId[2]);

    virtual MINT32 start();
    virtual MINT32 stop();

    virtual MINT32 getInfo(ACDK_SCENARIO_ID_ENUM ScenarioId[2],ACDK_SENSOR_INFO_STRUCT *pSensorInfo[2],ACDK_SENSOR_CONFIG_STRUCT *pSensorConfigData[2]);
    virtual MINT32 getResolution(ACDK_SENSOR_RESOLUTION_INFO_STRUCT *pSensorResolution[2]);

    virtual MINT32 sendCommand( SENSOR_DEV_ENUM sensorDevId, MUINT32 cmd, MUINT32 *parg1 = NULL, MUINT32 *parg2 = NULL, MUINT32 *parg3 = NULL);

    virtual MINT32 setFoundDrvsActive(MUINT32 socketIdxes);
    virtual MUINT32 getMainSensorID() const { return m_mainSensorId; }
    virtual MUINT32 getMain2SensorID() const { return m_main2SensorId; }
    virtual MUINT32 getSubSensorID() const { return m_subSensorId; }
    virtual IMAGE_SENSOR_TYPE getCurrentSensorType(SENSOR_DEV_ENUM sensorDevId); 
    virtual NSFeature::SensorInfoBase*  getMainSensorInfo() const { return  m_pMainSensorInfo; }
    virtual NSFeature::SensorInfoBase*  getMain2SensorInfo() const { return  m_pMain2SensorInfo; }	
    virtual NSFeature::SensorInfoBase*  getSubSensorInfo()  const { return  m_pSubSensorInfo;  }

private:
    virtual MINT32 impSearchSensor(pfExIdChk pExIdChkCbf);
    MINT32 featureControl(CAMERA_DUAL_CAMERA_SENSOR_ENUM InvokeCamera, ACDK_SENSOR_FEATURE_ENUM FeatureId,  UINT8 *pFeaturePara,MUINT32 *pFeatureParaLen);    
    MINT32 getSensorDelayFrameCnt(SENSOR_DEV_ENUM sensorDevId, halSensorDelayFrame_e mode); 
    IMGSENSOR_SOCKET_POSITION_ENUM getSocketPosition(CAMERA_DUAL_CAMERA_SENSOR_ENUM socket);

#if defined (YUV_TUNING_SUPPORT)
    void customerInit(void);
    char* getHexToken(char *inStr, MUINT32 *outVal);
#endif 

private:
    int     m_fdSensor;
    //int     m_userCnt;     

    MUINT32  m_LineTimeInus[2];

    MUINT32     m_mainSensorId;
    MUINT32     m_main2SensorId;
    MUINT32     m_subSensorId;
    
    enum { BAD_SENSOR_INDEX = 0xFF };
    UINT8   m_mainSensorIdx; 
    UINT8   m_main2SensorIdx; 
    UINT8   m_subSensorIdx; 

    SENSOR_DRIVER_LIST_T m_mainSensorDrv;
    SENSOR_DRIVER_LIST_T m_main2SensorDrv;
    SENSOR_DRIVER_LIST_T m_subSensorDrv;

    NSFeature::SensorInfoBase*  m_pMainSensorInfo;
    NSFeature::SensorInfoBase*  m_pMain2SensorInfo;
    NSFeature::SensorInfoBase*  m_pSubSensorInfo;

    MSDK_SENSOR_INIT_FUNCTION_STRUCT*   m_pstSensorInitFunc;
    ACDK_SENSOR_RESOLUTION_INFO_STRUCT  m_SenosrResInfo[2];
	ACDK_SENSOR_INFO_STRUCT m_sensorInfo[2];
	ACDK_SENSOR_INFO_STRUCT* m_psensorInfo[2];
	ACDK_SENSOR_CONFIG_STRUCT m_sensorConfigData[2];
	ACDK_SENSOR_CONFIG_STRUCT* m_psensorConfigData[2];
	
    //pthread_mutex_t                     m_sensorMutex;
    volatile int mUsers;
    mutable Mutex mLock;    

}; 

/*******************************************************************************
*
********************************************************************************/

#endif // _IMGSENSOR_DRV_H

