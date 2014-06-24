#define LOG_TAG "aaa_state_recording"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (0)
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
#include <CamDefs.h>
#include <ae_param.h>
#include <ae_mgr.h>
#include <flash_mgr.h>
#include <lsc_mgr.h>
#include "CameraProfile.h"  // For CPTLog*()/AutoCPTLog class.


using namespace NS3A;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateRecording
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
StateRecording::
StateRecording()
    : IState("StateRecording")
{
}


MRESULT StateRecording::exitPreview()
{
	MY_LOG("StateRecording::exitPreview line=%d",__LINE__);
	MRESULT err;

    // AE uninit
    AeMgr::getInstance().uninit();

    // AWB uninit
    AwbMgr::getInstance().uninit();

    // AF uninit
    AfMgr::getInstance().uninit();

    // AAO DMA / state disable again
    err = BufMgr::getInstance().AAStatEnable(MFALSE);
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().AAStatEnable(MFALSE) fail\n");
        return err;
    }

    err = BufMgr::getInstance().DMAUninit(camdma2type<ECamDMA_AAO>());
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().DMAunInit(ECamDMA_AAO) fail\n");
        return err;
    }

    // AFO DMA / state disable again
    err = BufMgr::getInstance().AFStatEnable(MFALSE);
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().AFStatEnable(MFALSE) fail\n");
        return err;
    }

    err = BufMgr::getInstance().DMAUninit(camdma2type<ECamDMA_AFO>());
    if (FAILED(err)) {
        MY_ERR("BufMgr::getInstance().DMAunInit(ECamDMA_AFO) fail\n");
        return err;
    }


    transitState(eState_Recording, eState_Init);
    return  S_3A_OK;
}


MRESULT
StateRecording::
sendIntent(intent2type<eIntent_CamcorderPreviewEnd>)
{
    MY_LOG("[StateRecording::sendIntent]<eIntent_CamcorderPreviewEnd> line=%d", __LINE__);
	exitPreview();
	FlashMgr::getInstance()->setAFLampOnOff(0);
    return  S_3A_OK;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_RecordingStart
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateRecording::
sendIntent(intent2type<eIntent_RecordingStart>)
{
    MY_LOG("[StateRecording::sendIntent]<eIntent_RecordingStart>");

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_RecordingEnd
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateRecording::
sendIntent(intent2type<eIntent_RecordingEnd>)
{
    MY_LOG("[StateRecording::sendIntent]<eIntent_RecordingEndd>");

    // State transition: eState_Recording --> eState_CamcorderPreview
    transitState(eState_Recording, eState_CamcorderPreview);

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_VsyncUpdate
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateRecording::
sendIntent(intent2type<eIntent_VsyncUpdate>)
{
    MRESULT err = S_3A_OK;
    BufInfo_T rBufInfo;

    MY_LOG("[StateRecording::sendIntent]<eIntent_VsyncUpdate>");

    // Update frame count
    updateFrameCount();

    // Dequeue AAO DMA buffer
    BufMgr::getInstance().dequeueHwBuf(ECamDMA_AAO, rBufInfo);

    //MTK_SWP_PROJECT_START
    // F858
    NSIspTuning::LscMgr::getInstance()->updateTSFinput(
            static_cast<NSIspTuning::LscMgr::LSCMGR_TSF_INPUT_SRC>(NSIspTuning::LscMgr::TSF_INPUT_VDO),
            AeMgr::getInstance().getLVvalue(), AwbMgr::getInstance().getAWBCCT(),
            reinterpret_cast<MVOID *>(rBufInfo.virtAddr));
    //MTK_SWP_PROJECT_END

    // AWB
    MINT32 i4SceneLv = AeMgr::getInstance().getLVvalue();
    CPTLog(Event_Pipe_3A_AWB, CPTFlagStart);    // Profiling Start.
    AwbMgr::getInstance().doPvAWB(getFrameCount(), AeMgr::getInstance().IsAEStable(), i4SceneLv, reinterpret_cast<MVOID *>(rBufInfo.virtAddr));
    CPTLog(Event_Pipe_3A_AWB, CPTFlagEnd);     // Profiling End.

    // AE
    AWB_OUTPUT_T _a_rAWBOutput;
	AwbMgr::getInstance().getAWBOutput(_a_rAWBOutput);
    CPTLog(Event_Pipe_3A_AE, CPTFlagStart);    // Profiling Start.
    AeMgr::getInstance().doPvAE(reinterpret_cast<MVOID *>(rBufInfo.virtAddr),reinterpret_cast<MVOID *>(&_a_rAWBOutput));
    CPTLog(Event_Pipe_3A_AE, CPTFlagEnd);     // Profiling End.

    // Enqueue AAO DMA buffer
    BufMgr::getInstance().enqueueHwBuf(ECamDMA_AAO, rBufInfo);

    // Update AAO DMA base address for next frame
    err = BufMgr::getInstance().updateDMABaseAddr(camdma2type<ECamDMA_AAO>(), BufMgr::getInstance().getNextHwBuf(ECamDMA_AAO));

    return  err;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_AFUpdate
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateRecording::
sendIntent(intent2type<eIntent_AFUpdate>)
{
    MY_LOG("[StateRecording::sendIntent]<eIntent_AFUpdate>");

    BufInfo_T rBufInfo;

    // Dequeue AFO DMA buffer
    BufMgr::getInstance().dequeueHwBuf(ECamDMA_AFO, rBufInfo);

    CPTLog(Event_Pipe_3A_Continue_AF, CPTFlagStart);    // Profiling Start.
    AfMgr::getInstance().doAF(reinterpret_cast<MVOID *>(rBufInfo.virtAddr));
    CPTLog(Event_Pipe_3A_Continue_AF, CPTFlagEnd);     // Profiling End.

    // Enqueue AFO DMA buffer
    BufMgr::getInstance().enqueueHwBuf(ECamDMA_AFO, rBufInfo);

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_AFStart
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateRecording::
sendIntent(intent2type<eIntent_AFStart>)
{
    MY_LOG("[StateRecording::sendIntent]<eIntent_AFStart>");

    // Init
    if(AeMgr::getInstance().IsDoAEInPreAF() == MTRUE)   {
        MY_LOG("Enter PreAF state");
        transitAFState(eAFState_PreAF);
    }
    else   {
        MY_LOG("Enter AF state");
        AfMgr::getInstance().triggerAF();
        transitAFState(eAFState_AF);
    }

    // State transition: eState_CameraPreview --> eState_AF
    //transitState(eState_CameraPreview, eState_AF);

    transitState(eState_Recording, eState_AF);



    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_AFEnd
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StateRecording::
sendIntent(intent2type<eIntent_AFEnd>)
{
    MY_LOG("[StateRecording::sendIntent]<eIntent_AFEnd>");

    return  S_3A_OK;
}

