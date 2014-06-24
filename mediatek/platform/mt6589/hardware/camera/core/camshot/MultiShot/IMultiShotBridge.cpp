#define LOG_TAG "CamShot/MultiShot"
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
#include <camshot/IMultiShot.h>
//
#include <drv/imem_drv.h>
//
#include "../inc/CamShotImp.h"
#include "../inc/MultiShot.h"
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
class IMultiShotBridge : public IMultiShot
{
    friend  class   IMultiShot;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    
    mutable android::Mutex      mLock;
    android::Mutex&             getLockRef()    { return mLock; }
    MUINT32                     mu4InitRefCount;

protected:  ////    Implementor.
    MultiShot*            mpMultiShotImp;
    inline  MultiShot const*   getImp() const  { return mpMultiShotImp; }
    inline  MultiShot*         getImp()        { return mpMultiShotImp; }

protected:  ////    Constructor/Destructor.
                    IMultiShotBridge(MultiShot*const pMultiShot);
                    ~IMultiShotBridge();

private:    ////    Disallowed.
                    IMultiShotBridge(IMultiShotBridge const& obj);
    IMultiShotBridge&  operator=(IMultiShotBridge const& obj);

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
    virtual MBOOL   startOne(SensorParam const & rSensorParam, ImgBufInfo const & rImgBufInfo);
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
IMultiShot*
IMultiShot::
createInstance(EShotMode const eShotMode, char const*const szCamShotName, SHOT_TYPE eShotType)
{
    MultiShot* pMultiShotImp;
    if(SHOT_CC == eShotType)
    {
        MY_LOGD("create MultiShotCc");
        pMultiShotImp = new MultiShotCc(eShotMode, "MultiShotCc");
    }
    else
    {
        MY_LOGD("create MultiShotNcc");
        pMultiShotImp = new MultiShotNcc(eShotMode, "MultiShotNcc");
    }
    
    if  ( ! pMultiShotImp )
    {
        MY_LOGE("[IMultiShot] fail to new MultiShot");
        return  NULL;
    }
    //
    IMultiShotBridge*  pIMultiShot = new IMultiShotBridge(pMultiShotImp);
    if  ( ! pIMultiShot )
    {
        MY_LOGE("[IMultiShot] fail to new IMultiShotBridge");
        delete  pMultiShotImp;
        return  NULL;
    }
    //
    return  pIMultiShot;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IMultiShotBridge::
destroyInstance()
{
    delete  mpMultiShotImp;  //  Firstly, delete the implementor here instead of destructor.
    delete  this;       //  Finally, delete myself.
}


/*******************************************************************************
* 
********************************************************************************/
IMultiShotBridge::
IMultiShotBridge(MultiShot*const pMultiShot)
    : IMultiShot()
    , mLock()
    , mu4InitRefCount(0)
    , mpMultiShotImp(pMultiShot)
{
}


/*******************************************************************************
* 
********************************************************************************/
IMultiShotBridge::
~IMultiShotBridge()
{
}


/*******************************************************************************
* 
********************************************************************************/
char const*
IMultiShotBridge::
getCamShotName() const
{
    return  getImp()->getCamShotName();
}


/*******************************************************************************
* 
********************************************************************************/
EShotMode
IMultiShotBridge::
getShotMode() const
{
    return  getImp()->getShotMode();
}


/*******************************************************************************
* 
********************************************************************************/
MINT32
IMultiShotBridge::
getLastErrorCode() const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->getLastErrorCode();
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
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
IMultiShotBridge::
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
IMultiShotBridge::
setCallbacks(CamShotNotifyCallback_t notify_cb, CamShotDataCallback_t data_cb, MVOID* user)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setCallbacks(notify_cb, data_cb, user);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
isNotifyMsgEnabled(MINT32 const i4MsgTypes) const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->isNotifyMsgEnabled(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IMultiShotBridge::
enableNotifyMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enableNotifyMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IMultiShotBridge::
disableNotifyMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->disableNotifyMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
isDataMsgEnabled(MINT32 const i4MsgTypes) const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->isDataMsgEnabled(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IMultiShotBridge::
enableDataMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->enableDataMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IMultiShotBridge::
disableDataMsg(MINT32 const i4MsgTypes)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->disableDataMsg(i4MsgTypes);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
start(SensorParam const & rSensorParam, MUINT32 u4ShotCount)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->start(rSensorParam, u4ShotCount);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
startAsync(SensorParam const & rSensorParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startAsync(rSensorParam);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
startOne(SensorParam const & rSensorParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startOne(rSensorParam);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
startOne(ImgBufInfo const & rImgBufInfo)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->startOne(rImgBufInfo);
}
/*******************************************************************************
*
********************************************************************************/
MBOOL
IMultiShotBridge::
startOne(SensorParam const & rSensorParam, ImgBufInfo const & rImgBufInfo)
{
    Mutex::Autolock _lock(mLock);
    return  MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
stop()
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->stop();
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
setShotParam(ShotParam const & rParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setShotParam(rParam);
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
IMultiShotBridge::
setJpegParam(JpegParam const & rParam)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setJpegParam(rParam);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL   
IMultiShotBridge::
registerImgBufInfo(ECamShotImgBufType const eBufType, ImgBufInfo const &rImgBuf)
{
    Mutex::Autolock _lock(mLock); 
    return  getImp()->registerImgBufInfo(eBufType, rImgBuf); 
}



/*******************************************************************************
* 
********************************************************************************/
MBOOL   
IMultiShotBridge::
sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->sendCommand(cmd, arg1, arg2, arg3);
} 


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot

