#define LOG_TAG "campipe/Cdp"
//
#include <utils/threads.h>
//
#include <inc/common/CamLog.h>
#define MY_LOGV(fmt, arg...)    CAM_LOGV("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGD(fmt, arg...)    CAM_LOGD("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGI(fmt, arg...)    CAM_LOGI("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGW(fmt, arg...)    CAM_LOGW("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGE(fmt, arg...)    CAM_LOGE("[%s] "fmt, __FUNCTION__, ##arg)
//
#include <common/CamTypes.h>
#include <common/hw/hwstddef.h>
//
#include <campipe/IPipe.h>
#include <campipe/ICdpPipe.h>
//
#include "../inc/PipeImp.h"
#include "../inc/CdpPipe.h"
//
using namespace android;


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* 
********************************************************************************/
class ICdpPipeBridge : public ICdpPipe
{
    friend  class   ICdpPipe;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    
    mutable android::Mutex      mLock;
    android::Mutex&             getLockRef()    { return mLock; }
    MUINT32                     mu4InitRefCount;

protected:  ////    Implementor.
    CdpPipe*const            mpPipeImp;
    inline  CdpPipe const*   getImp() const  { return mpPipeImp; }
    inline  CdpPipe*         getImp()        { return mpPipeImp; }

protected:  ////    Constructor/Destructor.
                    ICdpPipeBridge(CdpPipe*const pCdpPipe);
                    ~ICdpPipeBridge();

private:    ////    Disallowed.
                    ICdpPipeBridge(ICdpPipeBridge const& obj);
    ICdpPipeBridge&  operator=(ICdpPipeBridge const& obj);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Instantiation.
    virtual MVOID   destroyInstance();
    virtual MBOOL   init();
    virtual MBOOL   uninit();

public:     ////    Attributes.
    virtual char const* getPipeName() const;
    virtual EPipeID     getPipeId() const;
    virtual MINT32      getLastErrorCode() const;

public:     ////    Callbacks.
    virtual MVOID   setCallbacks(PipeNotifyCallback_t notify_cb, PipeDataCallback_t data_cb, MVOID* user);
    //
    //  notify callback
    virtual MBOOL   isNotifyMsgEnabled(MINT32 const i4MsgTypes) const;
    virtual MVOID   enableNotifyMsg(MINT32 const i4MsgTypes);
    virtual MVOID   disableNotifyMsg(MINT32 const i4MsgTypes);
    //
    //  data callback
    virtual MBOOL   isDataMsgEnabled(MINT32 const i4MsgTypes) const;
    virtual MVOID   enableDataMsg(MINT32 const i4MsgTypes);
    virtual MVOID   disableDataMsg(MINT32 const i4MsgTypes);

public:     ////    Operations.
    virtual MBOOL   start();
    virtual MBOOL   stop();

public:     ////    Buffer Quening.
    virtual MBOOL   enqueBuf(PortID const ePortID, QBufInfo const& rQBufInfo);
    virtual MBOOL   dequeBuf(PortID const ePortID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs = 0xFFFFFFFF);    

public:     ////    Settings.
    virtual MBOOL   configPipe(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts);
    virtual MBOOL   sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3); 
public:     ////    info 
    virtual MBOOL   queryPipeProperty(vector<PortProperty > &vInPorts, vector<PortProperty > &vOutPorts); 
    

};


/*******************************************************************************
* 
********************************************************************************/
ICdpPipe*
ICdpPipe::
createInstance(ESWScenarioID const eSWScenarioID, EScenarioFmt const eScenarioFmt)
{
    CdpPipe* pPipeImp = new CdpPipe("CdpPipe", ICdpPipe::ePipeID, eSWScenarioID, eScenarioFmt);
    if  ( ! pPipeImp )
    {
        MY_LOGE("[ICdpPipe] fail to new CdpPipe");
        return  NULL;
    }
    //
    ICdpPipeBridge*  pIPipe = new ICdpPipeBridge(pPipeImp);
    if  ( ! pIPipe )
    {
        MY_LOGE("[ICdpPipe] fail to new ICdpPipeBridge");
        delete  pPipeImp;
        return  NULL;
    }
    //
    return  pIPipe;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ICdpPipeBridge::
destroyInstance()
{
    delete  mpPipeImp;  //  Firstly, delete the implementor here instead of destructor.
    delete  this;       //  Finally, delete myself.
}


/*******************************************************************************
* 
********************************************************************************/
ICdpPipeBridge::
ICdpPipeBridge(CdpPipe*const pCdpPipe)
    : ICdpPipe()
    , mLock()
    , mu4InitRefCount(0)
    , mpPipeImp(pCdpPipe)
{
}


/*******************************************************************************
* 
********************************************************************************/
ICdpPipeBridge::
~ICdpPipeBridge()
{
}


/*******************************************************************************
* 
********************************************************************************/
char const*
ICdpPipeBridge::
getPipeName() const
{
    return  getImp()->getPipeName();
}


/*******************************************************************************
* 
********************************************************************************/
EPipeID
ICdpPipeBridge::
getPipeId() const
{
    return  getImp()->getPipeId();
}

/*******************************************************************************
* 
********************************************************************************/
MINT32
ICdpPipeBridge::
getLastErrorCode() const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->getLastErrorCode();
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
init()
{
    MBOOL   ret = MTRUE;
    Mutex::Autolock _lock(mLock);

    if  ( 0 != mu4InitRefCount )
    {
        mu4InitRefCount++;
    }
    else if ( (ret = getImp()->init()) )
    {
        mu4InitRefCount = 1;
    }
    MY_LOGD("- mu4InitRefCount(%d), ret(%d)", mu4InitRefCount, ret);
    return  ret;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
uninit()
{
    MBOOL   ret = MTRUE;
    Mutex::Autolock _lock(mLock);

    if  ( 0 < mu4InitRefCount )
    {
        mu4InitRefCount--;
        if  ( 0 == mu4InitRefCount )
        {
            ret = getImp()->uninit();
        }
    }
    MY_LOGD("- mu4InitRefCount(%d), ret(%d)", mu4InitRefCount, ret);
    return  ret;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ICdpPipeBridge::
setCallbacks(PipeNotifyCallback_t notify_cb, PipeDataCallback_t data_cb, MVOID* user)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setCallbacks(notify_cb, data_cb, user);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
isNotifyMsgEnabled(MINT32 const i4MsgTypes) const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->isNotifyMsgEnabled(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ICdpPipeBridge::
enableNotifyMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enableNotifyMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ICdpPipeBridge::
disableNotifyMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->disableNotifyMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
isDataMsgEnabled(MINT32 const i4MsgTypes) const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->isDataMsgEnabled(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ICdpPipeBridge::
enableDataMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enableDataMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ICdpPipeBridge::
disableDataMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->disableDataMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
start()
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->start();
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
stop()
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->stop();
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
configPipe(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->configPipe(vInPorts, vOutPorts);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL   
ICdpPipeBridge::
sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->sendCommand(cmd, arg1, arg2, arg3);
} 

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
queryPipeProperty(vector<PortProperty > &vInPorts, vector<PortProperty > &vOutPorts)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->queryPipeProperty(vInPorts, vOutPorts);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
enqueBuf(PortID const ePortID, QBufInfo const& rQBufInfo)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enqueBuf(ePortID, rQBufInfo);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ICdpPipeBridge::
dequeBuf(PortID const ePortID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs /*= 0xFFFFFFFF*/)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->dequeBuf(ePortID, rQBufInfo, u4TimeoutMs);
}

////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe

