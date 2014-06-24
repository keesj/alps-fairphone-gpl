#define LOG_TAG "CamShot/SImager"
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
#include <camshot/_callbacks.h>
#include <camshot/ISImager.h>
//
#include "../inc/SImager.h"
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
class ISImagerBridge : public ISImager
{
    friend  class   ISImager;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    
    mutable android::Mutex      mLock;
    android::Mutex&             getLockRef()    { return mLock; }
    MUINT32                     mu4InitRefCount;

protected:  ////    Implementor.
    SImager*const            mpSImagerImp;
    inline  SImager const*   getImp() const  { return mpSImagerImp; }
    inline  SImager*         getImp()        { return mpSImagerImp; }

protected:  ////    Constructor/Destructor.
                    ISImagerBridge(SImager*const pSImager);
                    ~ISImagerBridge();

private:    ////    Disallowed.
                    ISImagerBridge(ISImagerBridge const& obj);
    ISImagerBridge&  operator=(ISImagerBridge const& obj);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Instantiation.
    virtual MVOID   destroyInstance();

public:     ////    Attributes.
    virtual MINT32      getLastErrorCode() const;
    virtual MUINT32     getJpegSize() ; 

public:     ////    Callbacks.
    virtual MVOID   setCallback(SImagerNotifyCallback_t notify_cb, MVOID* user); 
    //
public:     ////    Operations.
    virtual MBOOL    execute(MUINT32 const u4TimeoutMs = 0xFFFFFFFF); 
    virtual MBOOL    executeAsync(); 
    virtual MBOOL    cancel(); 

public:     ////    Settings.
    virtual MBOOL   setTargetBufInfo(BufInfo const &rBufInfo); 
    virtual MBOOL   setFormat(EImageFormat const eFormat); 
    virtual MBOOL   setFlip(MUINT32 const u4Flip); 
    virtual MBOOL   setROI(Rect const rROI); 
    virtual MBOOL   setResize(MUINT32 const u4Width, MUINT32 const u4Height); 
    virtual MBOOL   setRotation(MUINT32 const u4Ratation); 
    virtual MBOOL   setEncodeParam(MUINT32 const &u4IsSOI, MUINT32 const &u4Quality); 
    virtual MBOOL   setStrideAlign(MUINT32 const u4StrideAlign[3]); 

};


/*******************************************************************************
* 
********************************************************************************/
ISImager*
ISImager::
createInstance(ImgBufInfo const & rImgBufInfo)
{
    SImager* pSImagerImp = new SImager(rImgBufInfo);
    if  ( ! pSImagerImp )
    {
        MY_LOGE("[ISImager] fail to new SImager");
        return  NULL;
    }
    //
    ISImagerBridge*  pISImager = new ISImagerBridge(pSImagerImp);
    if  ( ! pISImager )
    {
        MY_LOGE("[ISImager] fail to new ISImagerBridge");
        delete  pSImagerImp;
        return  NULL;
    }
    //
    return  pISImager;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISImagerBridge::
destroyInstance()
{
    delete  mpSImagerImp;  //  Firstly, delete the implementor here instead of destructor.
    delete  this;       //  Finally, delete myself.
}


/*******************************************************************************
* 
********************************************************************************/
ISImagerBridge::
ISImagerBridge(SImager*const pSImager)
    : ISImager()
    , mLock()
    , mu4InitRefCount(0)
    , mpSImagerImp(pSImager)
{
}


/*******************************************************************************
* 
********************************************************************************/
ISImagerBridge::
~ISImagerBridge()
{
}

/*******************************************************************************
* 
********************************************************************************/
MINT32
ISImagerBridge::
getLastErrorCode() const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->getLastErrorCode();
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
ISImagerBridge::
setCallback(SImagerNotifyCallback_t notify_cb, MVOID* user)
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->setCallback(notify_cb, user);
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
execute(MUINT32 const u4TimeoutMs)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->execute(u4TimeoutMs); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
executeAsync()
{
    Mutex::Autolock _lock(mLock);
    return getImp()->executeAsync(); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
cancel()
{
    Mutex::Autolock _lock(mLock);
    return getImp()->cancel(); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setTargetBufInfo(BufInfo const &rBufInfo)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setTargetBufInfo(rBufInfo); 
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setFormat(EImageFormat const eFormat)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setFormat(eFormat); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setFlip(MUINT32 const u4Flip)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setFlip(u4Flip); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setROI(Rect const rROI)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setROI(rROI); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setResize(MUINT32 const u4Width, MUINT32 const u4Height)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setResize(u4Width, u4Height); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setRotation(MUINT32 const u4Ratation)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setRotation(u4Ratation); 
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL   
ISImagerBridge::
setStrideAlign(MUINT32 const u4StrideAlign[3])
{
    Mutex::Autolock _lock(mLock); 
    return getImp()->setStrideAlign(u4StrideAlign); 
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
ISImagerBridge::
setEncodeParam(MUINT32 const &u4IsSOI, MUINT32 const &u4Quality)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->setEncodeParam(u4IsSOI, u4Quality); 
}

/*******************************************************************************
* 
********************************************************************************/
MUINT32
ISImagerBridge::
getJpegSize()  
{
    Mutex::Autolock _lock(mLock); 
    return getImp()->getJpegSize(); 
}


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot

