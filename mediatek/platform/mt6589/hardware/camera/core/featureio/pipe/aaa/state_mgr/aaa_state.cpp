#define LOG_TAG "aaa_state"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <aaa_types.h>
#include <aaa_error_code.h>
#include <aaa_log.h>
#include <dbg_aaa_param.h>
#include <aaa_hal.h>
#include "aaa_state.h"
#include <camera_custom_nvram.h>
#include <awb_param.h>
#include <awb_mgr.h>
#include <buf_mgr.h>
#include <sensor_hal.h>
#include <af_param.h>
#include <mcu_drv.h>
#include <isp_reg.h>
#include <af_mgr.h>
#include <ae_param.h>
#include <CamDefs.h>
#include <ae_mgr.h>
#include <flash_mgr.h>


using namespace NS3A;

EState_T g_ePrevState;

EState_T g_preStateForAe;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  IState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
IState*
IState::sm_pCurrState =
IState::getStateInstance(eState_Uninit);

MINT32 IState::m_i4FrameCount = 0;

IState::EAFState_T IState::m_eAFState = IState::eAFState_None;

IState*
IState::
getCurrStateInstance()
{
    return  IState::sm_pCurrState;
}


IState*
IState::
getStateInstance(EState_T const eState)
{
    switch  (eState)
    {
#define INSTANTIATE_STATE(_name_)\
    case eState_##_name_:\
        {\
            static  State##_name_ singleton;\
            return  &singleton;\
        }

    INSTANTIATE_STATE(Uninit);
    INSTANTIATE_STATE(Init);
    INSTANTIATE_STATE(CameraPreview);
    INSTANTIATE_STATE(CamcorderPreview);
    INSTANTIATE_STATE(Precapture);
    INSTANTIATE_STATE(Capture);
    INSTANTIATE_STATE(Recording);
    INSTANTIATE_STATE(AF);
    default:
        break;
    };

    return  MNULL;
}


MRESULT
IState::
transitState(EState_T const eCurrState, EState_T const eNewState)
{
    IState*const pNewState = getStateInstance(eNewState);
    if  ( ! pNewState )
    {
        MY_ERR("[StateCommon::transitState] pNewState==NULL");
        return  E_3A_INCORRECT_STATE;
    }

    if (eCurrState == eState_CameraPreview || eCurrState == eState_CamcorderPreview || eCurrState == eState_Recording)
    {g_ePrevState = eCurrState;}

    g_preStateForAe = eCurrState;

    MY_LOG("[StateCommon::transitState] %s --> %s", sm_pCurrState->getName(), pNewState->getName());

    sm_pCurrState = pNewState;
    return  S_3A_OK;
}


IState::
IState(char const*const pcszName)
    : m_pHal3A(Hal3A::getInstance())
    , m_pcszName(pcszName)
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateUninit
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
StateUninit::
StateUninit()
    : IState("StateUninit")
{
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_Init
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateUninit::
sendIntent(intent2type<eIntent_Init>)
{
    MY_LOG("[StateUninit::sendIntent]<eIntent_Init>");

    // DMA buffer init
    MRESULT err = BufMgr::getInstance().init();
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().init() fail\n");
        return err;
    }

    // State transition: eState_Uninit --> eState_Init
    transitState(eState_Uninit, eState_Init);

    return  S_3A_OK;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateInit
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
StateInit::
StateInit()
    : IState("StateInit")
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_Uninit
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateInit::
sendIntent(intent2type<eIntent_Uninit>)
{
    MY_LOG("[StateInit::sendIntent]<eIntent_Uninit>");
    FlashMgr::getInstance()->turnOffFlashDevice();


    // DMA buffer uninit
    MRESULT err = BufMgr::getInstance().uninit();
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().uninit() fail\n");
        return err;
    }

    // State transition: eState_Init --> eState_Uninit
    transitState(eState_Init, eState_Uninit);

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_CameraPreviewStart
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateInit::
sendIntent(intent2type<eIntent_CameraPreviewStart>)
{
    MRESULT err;

    MY_LOG("[StateInit::sendIntent]<eIntent_CameraPreviewStart>");

    // Get parameters
    Param_T rParam;
    m_pHal3A->getParams(rParam);
    MINT32 i4SensorDev = m_pHal3A->getSensorDev();

    // AE init
    err = AeMgr::getInstance().cameraPreviewInit(i4SensorDev, rParam);
    if (FAILED(err)) {
        MY_ERR("AebMgr::getInstance().cameraPreviewInit() fail\n");
        return err;
    }

    // AF init
    err = AfMgr::getInstance().init();
    if (FAILED(err)) {
        MY_ERR("AfMgr::getInstance().init() fail\n");
        return err;
    }

    // AWB init
    err = AwbMgr::getInstance().cameraPreviewInit(i4SensorDev, rParam);
    if (FAILED(err)) {
        MY_ERR("AwbMgr::getInstance().cameraPreviewInit() fail\n");
        return err;
    }

    // Flash init
    err = FlashMgr::getInstance()->init(i4SensorDev);
    if (FAILED(err)) {
        MY_ERR("AwbMgr::getInstance().cameraPreviewInit() fail\n");
        return err;
    }

#if 0
    // AAO DMA buffer init
    err = BufMgr::getInstance().init();
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().init() fail\n");
        return err;
    }
#endif

    // AAO DMA / state enable
    err = BufMgr::getInstance().DMAInit(camdma2type<ECamDMA_AAO>());
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().DMAInit(ECamDMA_AAO) fail\n");
        return err;
    }

    err = BufMgr::getInstance().AAStatEnable(MTRUE);
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().AAStatEnable(MTRUE) fail\n");
        return err;
    }

    // AFO DMA / state enable
    err = BufMgr::getInstance().DMAInit(camdma2type<ECamDMA_AFO>());
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().DMAInit(ECamDMA_AFO) fail\n");
        return err;
    }

    err = BufMgr::getInstance().AFStatEnable(MTRUE);
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().AFStatEnable(MTRUE) fail\n");
        return err;
    }

    // Reset frame count to -2
    resetFrameCount();


    // State transition: eState_Init --> eState_CameraPreview
    transitState(eState_Init, eState_CameraPreview);

    return  S_3A_OK;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_CamcorderPreviewStart
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateInit::
sendIntent(intent2type<eIntent_CamcorderPreviewStart>)
{
    MRESULT err;

    MY_LOG("[StateInit::sendIntent]<eIntent_CamcorderPreviewStart>");

    // Get parameters
    Param_T rParam;
    m_pHal3A->getParams(rParam);
    MINT32 i4SensorDev = m_pHal3A->getSensorDev();

    // AE init
    err = AeMgr::getInstance().camcorderPreviewInit(i4SensorDev, rParam);
    if (FAILED(err)) {
        MY_ERR("AebMgr::getInstance().camcorderPreviewInit() fail\n");
        return err;
    }

    // AF init
    err = AfMgr::getInstance().init();
    if (FAILED(err)) {
        MY_ERR("AfMgr::getInstance().init() fail\n");
        return err;
    }

    // AWB init
    err = AwbMgr::getInstance().camcorderPreviewInit(i4SensorDev, rParam);
    if (FAILED(err)) {
        MY_ERR("AwbMgr::getInstance().camcorderPreviewInit() fail\n");
        return err;
    }

#if 0
    // AAO DMA buffer init
    err = BufMgr::getInstance().init();
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().init() fail\n");
        return err;
    }
#endif

    // AAO DMA / state enable
    err = BufMgr::getInstance().DMAInit(camdma2type<ECamDMA_AAO>());
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().DMAInit(ECamDMA_AAO) fail\n");
        return err;
    }

    err = BufMgr::getInstance().AAStatEnable(MTRUE);
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().AAStatEnable(MTRUE) fail\n");
        return err;
    }

    // AFO DMA / state enable
    err = BufMgr::getInstance().DMAInit(camdma2type<ECamDMA_AFO>());
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().DMAInit(ECamDMA_AFO) fail\n");
        return err;
    }

    err = BufMgr::getInstance().AFStatEnable(MTRUE);
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().AFStatEnable(MTRUE) fail\n");
        return err;
    }

    // Reset frame count to -2
    resetFrameCount();

    // State transition: eState_Init --> eState_CamcorderPreview
    transitState(eState_Init, eState_CamcorderPreview);

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_AFUpdate
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateInit::
sendIntent(intent2type<eIntent_AFUpdate>)
{
    return  S_3A_OK;
}
