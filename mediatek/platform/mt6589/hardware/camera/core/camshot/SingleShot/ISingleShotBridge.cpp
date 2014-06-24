#define LOG_TAG "CamShot/SingleShot"
//
#include <utils/threads.h>
//
#include <inc/common/CamLog.h>
#include <inc/common/CamTypes.h>
#define MY_LOGV(fmt, arg...)    CAM_LOGV("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGD(fmt, arg...)    CAM_LOGD("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGI(fmt, arg...)    CAM_LOGI("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGW(fmt, arg...)    CAM_LOGW("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGE(fmt, arg...)    CAM_LOGE("[%s] "fmt, __FUNCTION__, ##arg)
//
#include <common/CamDefs.h>
#include <common/hw/hwstddef.h>
//
#include <campipe/_ports.h>
//
#include <camshot/_callbacks.h>
#include <camshot/_params.h>

#include <camshot/ICamShot.h>
#include <camshot/ISingleShot.h>
//
#include <drv/imem_drv.h>
//
#include "../inc/CamShotImp.h"
#include "../inc/SingleShot.h"
//
using namespace android;


/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* 
********************************************************************************/
class ISingleShotBridge : public ISingleShot
{
    friend  class   ISingleShot;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    
    mutable android::Mutex      mLock;
    android::Mutex&             getLockRef()    { return mLock; }
    MUINT32                     mu4InitRefCount;

protected:  ////    Implementor.
    SingleShot*const            mpSingleShotImp;
    inline  SingleShot const*   getImp() const  { return mpSingleShotImp; }
    inline  SingleShot*         getImp()        { return mpSingleShotImp; }

protected:  ////    Constructor/Destructor.
                    ISingleShotBridge(SingleShot*const pSingleShot);
                    ~ISingleShotBridge();

private:    ////    Disallowed.
                    ISingleShotBridge(ISingleShotBridge const& obj);
    ISingleShotBridge&  operator=(ISingleShotBridge const& obj);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Instantiation.
    virtual MVOID   destroyInstance();
    virtual MBOOL   init();
    virtual MBOOL   uninit();

public:     ////    Attributes.
    virtual char const* getCamShotName() const;
    virtual EShotMode     getShotMode() const; 
    virtual MINT32      getLastErrorCode() const;

public:     ////    Callbacks.
    virtual MVOID   setCallbacks(CamShotNotifyCallback_t notify_cb, CamShotDataCallback_t data_cb, MVOID* user);
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
    virtual MBOOL   start(SensorParam const & rSensorParam, MUINT32 u4ShotCount=0xFFFFFFFF);
    virtual MBOOL   startAsync(SensorParam const & rSensorParam) ;   
    virtual MBOOL   startOne(SensorParam const & rSensorParam); 
    virtual MBOOL   startOne(ImgBufInfo const & rImgBufInfo); 
    virtual MBOOL   startOne(SensorParam const & rSensorParam,ImgBufInfo const & rImgBufInfo);
    virtual MBOOL   stop();


public:     ////    Settings.
    virtual MBOOL   setShotParam(ShotParam const & rParam); 
    virtual MBOOL   setJpegParam(JpegParam const & rParam); 

public:     ////    buffer setting. 
    virtual MBOOL   registerImgBufInfo(ECamShotImgBufType const eBufType, ImgBufInfo const &rImgBuf); 

public:     ////    Old style commnad.
    virtual MBOOL   sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3);

};


/*******************************************************************************
* 
********************************************************************************/
ISingleShot*
ISingleShot::
createInstance(EShotMode const eShotMode, char const*const szCamShotName)
{
    SingleShot* pSingleShotImp = new SingleShot(eShotMode, "SingleShot");
    if  ( ! pSingleShotImp )
    {
        MY_LOGE("[ISingleShot] fail to new SingleShot");
        return  NULL;
    }
    //
    ISingleShotBridge*  pISingleShot = new ISingleShotBridge(pSingleShotImp);
    if  ( ! pISingleShot )
    {
        MY_LOGE("[ISingleShot] fail to new ISingleShotBridge");
        delete  pSingleShotImp;
        return  NULL;
    }
    //
    return  pISingleShot;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISingleShotBridge::
destroyInstance()
{
    delete  mpSingleShotImp;  //  Firstly, delete the implementor here instead of destructor.
    delete  this;       //  Finally, delete myself.
}


/*******************************************************************************
* 
********************************************************************************/
ISingleShotBridge::
ISingleShotBridge(SingleShot*const pSingleShot)
    : ISingleShot()
    , mLock()
    , mu4InitRefCount(0)
    , mpSingleShotImp(pSingleShot)
{
}


/*******************************************************************************
* 
********************************************************************************/
ISingleShotBridge::
~ISingleShotBridge()
{
}


/*******************************************************************************
* 
********************************************************************************/
char const*
ISingleShotBridge::
getCamShotName() const
{
    return  getImp()->getCamShotName();
}


/*******************************************************************************
* 
********************************************************************************/
EShotMode
ISingleShotBridge::
getShotMode() const
{
    return  getImp()->getShotMode();
}


/*******************************************************************************
* 
********************************************************************************/
MINT32
ISingleShotBridge::
getLastErrorCode() const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->getLastErrorCode();
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
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
ISingleShotBridge::
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
ISingleShotBridge::
setCallbacks(CamShotNotifyCallback_t notify_cb, CamShotDataCallback_t data_cb, MVOID* user)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setCallbacks(notify_cb, data_cb, user);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
isNotifyMsgEnabled(MINT32 const i4MsgTypes) const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->isNotifyMsgEnabled(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISingleShotBridge::
enableNotifyMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enableNotifyMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISingleShotBridge::
disableNotifyMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->disableNotifyMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
isDataMsgEnabled(MINT32 const i4MsgTypes) const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->isDataMsgEnabled(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISingleShotBridge::
enableDataMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enableDataMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISingleShotBridge::
disableDataMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->disableDataMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
start(SensorParam const & rSensorParam, MUINT32 u4ShotCount)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->start(rSensorParam);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
startAsync(SensorParam const & rSensorParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startAsync(rSensorParam);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
startOne(SensorParam const & rSensorParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startOne(rSensorParam);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
startOne(ImgBufInfo const & rImgBufInfo)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startOne(rImgBufInfo);
}

/*******************************************************************************
*
********************************************************************************/
MBOOL
ISingleShotBridge::
startOne(SensorParam const & rSensorParam, ImgBufInfo const & rImgBufInfo)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startOne(rSensorParam, rImgBufInfo);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
stop()
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->stop();
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
setShotParam(ShotParam const & rParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setShotParam(rParam);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISingleShotBridge::
setJpegParam(JpegParam const & rParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setJpegParam(rParam);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL   
ISingleShotBridge::
registerImgBufInfo(ECamShotImgBufType const eBufType, ImgBufInfo const &rImgBuf)
{
    Mutex::Autolock _lock(mLock); 
    return  getImp()->registerImgBufInfo(eBufType, rImgBuf); 
}



/*******************************************************************************
* 
********************************************************************************/
MBOOL   
ISingleShotBridge::
sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->sendCommand(cmd, arg1, arg2, arg3);
} 


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot

