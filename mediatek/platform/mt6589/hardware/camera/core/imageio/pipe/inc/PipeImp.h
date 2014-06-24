#ifndef _ISPIO_PIPE_IMP_H_
#define _ISPIO_PIPE_IMP_H_
//
#include <vector>
//
using namespace std;
//
#include <cutils/atomic.h>
//
//
#include <inc/common/CamTypes.h>
//
#include <inc/imageio/ispio_pipe_scenario.h>
#include <inc/imageio/ispio_pipe_identity.h>
#include <inc/imageio/ispio_pipe_callbacks.h>
//
#include <inc/imageio/ispio_pipe_ports.h>
#include <inc/imageio/ispio_pipe_buffer.h>
//
#include "cam_path.h"

/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
********************************************************************************/
class PipeImp
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Attributes.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    char const*const    mszPipeName;
    EPipeID const       mePipeID;
    MINT32              mi4ErrorCode;

public:     ////    Operations.
    virtual char const* getPipeName() const         { return mszPipeName; }
    virtual EPipeID     getPipeId() const           { return mePipeID; }
    virtual MINT32      getLastErrorCode() const    { return mi4ErrorCode; }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Instantiation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Constructor/Destructor.
                    PipeImp(
                        char const*const szPipeName,
                        EPipeID const ePipeID,
                        EScenarioID const eScenarioID,
                        EScenarioFmt const eScenarioFmt
                    );
    virtual         ~PipeImp()  {}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Callbacks.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    //
    MVOID*          mpCbUser;           //  Callback user.
    //
    //  notify callback
    volatile MINT32         mi4NotifyMsgSet;//  bitset of notify message types.
    PipeNotifyCallback_t    mNotifyCb;      //  notify callback function pointer.
    //
    //  data callback
    volatile MINT32         mi4DataMsgSet;  //  bitset of data message types.
    PipeDataCallback_t      mDataCb;        //  data callback function pointer.

protected:  ////    Helpers.
    virtual MBOOL   onNotifyCallback(PipeNotifyInfo const& msg) const;
    virtual MBOOL   onDataCallback(PipeDataInfo const& msg) const;

public:     ////    Operations.
    //
    virtual MVOID   setCallbacks(PipeNotifyCallback_t notify_cb, PipeDataCallback_t data_cb, MVOID* user);
    //
    //  notify callback
    inline MBOOL    isNotifyMsgEnabled(MINT32 const i4MsgTypes) const   { return (i4MsgTypes & mi4NotifyMsgSet); }
    inline MVOID    enableNotifyMsg(MINT32 const i4MsgTypes)            { ::android_atomic_or(i4MsgTypes, &mi4NotifyMsgSet); }
    inline MVOID    disableNotifyMsg(MINT32 const i4MsgTypes)           { ::android_atomic_and(~i4MsgTypes, &mi4NotifyMsgSet); }
    //
    //  data callback
    inline MBOOL    isDataMsgEnabled(MINT32 const i4MsgTypes) const     { return (i4MsgTypes & mi4DataMsgSet); }
    inline MVOID    enableDataMsg(MINT32 const i4MsgTypes)              { ::android_atomic_or(i4MsgTypes, &mi4DataMsgSet); }
    inline MVOID    disableDataMsg(MINT32 const i4MsgTypes)             { ::android_atomic_and(~i4MsgTypes, &mi4DataMsgSet); }

public:
    //
    MBOOL    configCdpOutPort(PortInfo const* oImgInfo,CdpRotDMACfg &a_rotDma);
    //
    MBOOL    configDmaPort(PortInfo const* portInfo,IspDMACfg &a_dma,MUINT32 pixel_Byte,MUINT32 swap, MUINT32 isBypassOffset,EIMAGE_STRIDE planeNum);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Scenario.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    //
    EScenarioID const   meScenarioID;
    EScenarioFmt const  meScenarioFmt;

public:     ////    Operations.
    inline  MINT32  getScenarioID()     const { return meScenarioID; }
    inline  MINT32  getScenarioSubmode()const { return mapScenarioFormatToSubmode(meScenarioID, meScenarioFmt); }
    static  MINT32  mapScenarioFormatToSubmode(EScenarioID const eScenarioID, EScenarioFmt const eScenarioFmt);
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_PIPE_IMP_H_

