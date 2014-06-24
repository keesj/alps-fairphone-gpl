#ifndef _AAA_SENSOR_MGR_H_
#define _AAA_SENSOR_MGR_H_

namespace NS3A
{

typedef struct
{
  MUINT16 u2SensorPreviewWidth;
  MUINT16 u2SensorPreviewHeight;
  MUINT16 u2SensorFullWidth;
  MUINT16 u2SensorFullHeight;
  MUINT16 u2SensorVideoWidth;
  MUINT16 u2SensorVideoHeight;
} SENSOR_RESOLUTION_INFO_T;

/*******************************************************************************
*
*******************************************************************************/
class AAASensorMgr
{

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Ctor/Dtor.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:    ////    Disallowed.
    //  Copy constructor is disallowed.
    AAASensorMgr(AAASensorMgr const&);
    //  Copy-assignment operator is disallowed.
    AAASensorMgr& operator=(AAASensorMgr const&);

public:  ////
    AAASensorMgr();
    ~AAASensorMgr();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Operations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    static AAASensorMgr& getInstance();
    MRESULT init();
    MRESULT uninit();
    MRESULT setSensorDev(MINT32 i4SensorDev);
    MRESULT getSensorSyncinfo(MINT32 *i4SutterDelay, MINT32 *i4SensorGainDelay, MINT32 *i4IspGainDelay);
    MRESULT getSensorWidthHeight(MINT32 i4SensorDev, SENSOR_RESOLUTION_INFO_T* a_rSensorResolution);
    MRESULT setSensorExpTime(MUINT32 a_u4ExpTime);
    MUINT32 getSensorExpTime();    
    MRESULT setSensorGain(MUINT32 a_u4SensorGain);
    MUINT32 getSensorGain();
    MRESULT setSensorFrameRate(MUINT32 a_u4SensorFrameRate);
    MUINT32 getSensorFrameRate();
    MRESULT setSensorExpLine(MUINT32 a_u4ExpLine);
    MRESULT setFlickerFrameRateActive(MBOOL a_bFlickerFPSAvtive);
    MUINT32 getFlickerFrameRateActive();
    MRESULT setSensorParams(MUINT32 a_u4ExpTime, MUINT32 a_u4SensorGain, MUINT32 a_u4RawGain);
    MRESULT setPreviewParams(MUINT32 a_u4ExpTime, MUINT32 a_u4SensorGain);
    MRESULT setCaptureParams(MUINT32 a_u4ExpTime, MUINT32 a_u4SensorGain);
    MRESULT setPreviewLineBaseParams(MUINT32 a_u4ExpLine, MUINT32 a_u4SensorGain);
    MRESULT setCaptureLineBaseParams(MUINT32 a_u4ExpLine, MUINT32 a_u4SensorGain);

private:
    MINT32 getSensorDelayFrame(halSensorDev_e eSensorDEv, MINT32 mode);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Data member
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
    SensorHal *m_pSensorHalObj;
    halSensorDev_e m_eSensorDevId;
    volatile MINT32        m_Users;
    mutable android::Mutex m_Lock;
    MBOOL    m_bDebugEnable;
    MBOOL    m_bFlickerState;
    MUINT32 m_u4ExpTime;
    MUINT32 m_u4SensorGain;
    MUINT32 m_u4SensorFrameRate;
    MINT32 m_i4ShutterDelayFrame;
    MINT32 m_i4SensorGainDelayFrame;
    MINT32 m_i4IspGainDelayFrame;    
};

};  //  namespace NS3A
#endif // _AAA_SENSOR_MGR_H_

