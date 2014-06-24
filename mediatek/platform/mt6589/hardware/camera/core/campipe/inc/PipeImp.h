#ifndef _MTK_CAMERA_CORE_CAMPIPE_INC_PIPEIMP_H_
#define _MTK_CAMERA_CORE_CAMPIPE_INC_PIPEIMP_H_

//
#include <vector>
//
using namespace std;

//
#include <cutils/atomic.h>
//
//
#include <inc/campipe/_scenario.h>
#include <inc/campipe/_identity.h>
#include <inc/campipe/_callbacks.h>
#include <inc/campipe/_ports.h>
#include <inc/campipe/_buffer.h>
//


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
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
                        ESWScenarioID const eSWScenarioID, 
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

protected:
    MVOID dumpPipeProperty(vector<PortProperty>const &vInPorts, vector<PortProperty>const &vOutPorts); 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Scenario.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    //
    ESWScenarioID const   meSWScenarioID;
    EScenarioFmt const  meScenarioFmt;

public:     ////    Operations.
    inline  MINT32  getScenarioID()     const { return meSWScenarioID; }
    inline  EScenarioFmt getScenarioFmt()    const { return meScenarioFmt; } 


};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_CORE_CAMPIPE_INC_PIPEIMP_H_

