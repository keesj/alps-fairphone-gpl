#define LOG_TAG "nvram_drv_mgr"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (0)
#endif

#include <aaa_types.h>
#include <aaa_log.h>
#include <aaa_error_code.h>
#include <nvram_drv.h>
#include <sensor_hal.h>
#include <isp_tuning.h>
#include "nvram_drv_mgr.h"

using namespace NS3A;
using namespace NSIspTuning;

/*******************************************************************************
* NVRAM Driver Manager Context
*******************************************************************************/
class NvramDrvMgrCtx : public NvramDrvMgr
{
    friend class NvramDrvMgr;
protected:
    NvramDrvMgrCtx();
    ~NvramDrvMgrCtx();

protected:  ////    Data Members.
    NvramDrvBase*                   m_pNvramDrv;

    MUINT32                         m_u4SensorID;
    CAMERA_DUAL_CAMERA_SENSOR_ENUM  m_eSensorEnum;

public:     ////    Interfaces.

    virtual MRESULT     init(
        MINT32 const i4SensorDev
    );

    virtual MRESULT     uninit();

private:    ////
    template <class Buf_T>
    Buf_T*  getRefBuf() const
    {
        NSNvram::BufIF<Buf_T>*const pBufIF = m_pNvramDrv->getBufIF<Buf_T>();
        if  ( ! pBufIF )
        {
            return  NULL;
        }
        return  pBufIF->getRefBuf(m_eSensorEnum, m_u4SensorID);
    }

public:     ////    Interfaces.

    virtual MVOID   getRefBuf(NVRAM_CAMERA_ISP_PARAM_STRUCT*& rpBuf) const;
    virtual MVOID   getRefBuf(NVRAM_CAMERA_SHADING_STRUCT*& rpBuf) const;
    virtual MVOID   getRefBuf(NVRAM_CAMERA_3A_STRUCT*& rpBuf) const;
    virtual MVOID   getRefBuf(AE_PLINETABLE_T*& rpBuf) const;
    virtual MVOID   getRefBuf(NVRAM_LENS_PARA_STRUCT*& rpBuf) const;
    virtual MVOID   getRefBuf(NVRAM_CAMERA_STROBE_STRUCT*& rpBuf) const;

};


NvramDrvMgr&
NvramDrvMgr::
getInstance()
{
    static NvramDrvMgrCtx singleton;
    return singleton;
}


NvramDrvMgrCtx::
NvramDrvMgrCtx()
    : NvramDrvMgr()
    , m_pNvramDrv(NULL)
    , m_u4SensorID(0)
    , m_eSensorEnum(DUAL_CAMERA_NONE_SENSOR)
{
}


NvramDrvMgrCtx::
~NvramDrvMgrCtx()
{
    uninit();
}


MRESULT
NvramDrvMgrCtx::
init(MINT32 const i4SensorDev)
{
    MRESULT err = S_NVRAM_OK;

    //  Sensor driver.
    SensorHal*const pSensorHal = SensorHal::createInstance();
    if  ( ! pSensorHal )
    {
        MY_ERR("Cannot create Sensor driver");
        err = E_NVRAM_BAD_SENSOR_DRV;
        goto lbExit;
    }

    //  Query sensor ID & sensor enum.
    switch  ( i4SensorDev )
    {
    case ESensorDev_Main:
        m_eSensorEnum = DUAL_CAMERA_MAIN_SENSOR;
        pSensorHal->sendCommand(SENSOR_DEV_MAIN, SENSOR_CMD_GET_SENSOR_ID, reinterpret_cast<MINT32>(&m_u4SensorID), 0, 0);
        break;
    case ESensorDev_Sub:
        m_eSensorEnum = DUAL_CAMERA_SUB_SENSOR;
        pSensorHal->sendCommand(SENSOR_DEV_SUB, SENSOR_CMD_GET_SENSOR_ID, reinterpret_cast<MINT32>(&m_u4SensorID), 0, 0);
        break;
    case ESensorDev_MainSecond:
        m_eSensorEnum = DUAL_CAMERA_MAIN_SECOND_SENSOR;
        pSensorHal->sendCommand(SENSOR_DEV_MAIN_2, SENSOR_CMD_GET_SENSOR_ID, reinterpret_cast<MINT32>(&m_u4SensorID), 0, 0);
        break;
    default:    //  Shouldn't happen.
        MY_ERR("Invalid sensor device: %d", i4SensorDev);
        err = E_NVRAM_BAD_PARAM;
        goto lbExit;
    }

    //  Nvram driver.
    if  ( ! m_pNvramDrv )
        m_pNvramDrv = NvramDrvBase::createInstance();
    if  ( ! m_pNvramDrv )
    {
        MY_ERR("Cannnot create NVRAM driver");
        err = E_NVRAM_BAD_NVRAM_DRV;
        goto lbExit;
    }

lbExit:
    if  ( pSensorHal )
        pSensorHal->destroyInstance();

    return  err;
}


MRESULT
NvramDrvMgrCtx::
uninit()
{
    if  ( m_pNvramDrv )
    {
        m_pNvramDrv->destroyInstance();
        m_pNvramDrv = NULL;
    }

    m_u4SensorID = 0;
    m_eSensorEnum = DUAL_CAMERA_NONE_SENSOR;

    return  S_NVRAM_OK;
}


MVOID
NvramDrvMgrCtx::
getRefBuf(NVRAM_CAMERA_ISP_PARAM_STRUCT*& rpBuf) const
{
    rpBuf = getRefBuf<NVRAM_CAMERA_ISP_PARAM_STRUCT>();
}


MVOID
NvramDrvMgrCtx::
getRefBuf(NVRAM_CAMERA_SHADING_STRUCT*& rpBuf) const
{
    rpBuf = getRefBuf<NVRAM_CAMERA_SHADING_STRUCT>();
}


MVOID
NvramDrvMgrCtx::
getRefBuf(NVRAM_CAMERA_3A_STRUCT*& rpBuf) const
{
    rpBuf = getRefBuf<NVRAM_CAMERA_3A_STRUCT>();
}

MVOID
NvramDrvMgrCtx::
getRefBuf(NVRAM_CAMERA_STROBE_STRUCT*& rpBuf) const
{
    rpBuf = getRefBuf<NVRAM_CAMERA_STROBE_STRUCT>();
}

MVOID
NvramDrvMgrCtx::
getRefBuf(AE_PLINETABLE_T*& rpBuf) const
{
    rpBuf = getRefBuf<AE_PLINETABLE_T>();
}

MVOID
NvramDrvMgrCtx::
getRefBuf(NVRAM_LENS_PARA_STRUCT*& rpBuf) const
{
    rpBuf = getRefBuf<NVRAM_LENS_PARA_STRUCT>();
}

