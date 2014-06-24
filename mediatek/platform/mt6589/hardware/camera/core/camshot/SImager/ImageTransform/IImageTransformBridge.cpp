#define LOG_TAG "CamShot/ImageTranform"
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
#include "../../inc/IImageTransform.h"
#include "./inc/ImageTransform.h"
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
class IImageTransformBridge : public IImageTransform
{
    friend  class   IImageTransform;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    
    mutable android::Mutex      mLock;
    android::Mutex&             getLockRef()    { return mLock; }
    MUINT32                     mu4InitRefCount;

protected:  ////    Implementor.
    ImageTransform*const            mpImageTransformImp;
    inline  ImageTransform const*   getImp() const  { return mpImageTransformImp; }
    inline  ImageTransform*         getImp()        { return mpImageTransformImp; }

protected:  ////    Constructor/Destructor.
                    IImageTransformBridge(ImageTransform*const pImageTransform);
                    ~IImageTransformBridge();

private:    ////    Disallowed.
                    IImageTransformBridge(IImageTransformBridge const& obj);
    IImageTransformBridge&  operator=(IImageTransformBridge const& obj);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Instantiation.
    virtual MVOID   destroyInstance();

public:     ////    Attributes.
    virtual MINT32      getLastErrorCode() const;


   //
public:     ////    Operations.
    virtual  MBOOL    execute(ImgBufInfo const rSrcBufInfo, ImgBufInfo const rDstBufInfo, Rect const rROI, MUINT32 const u4Rotation, MUINT32 const u4Flip, MUINT32 const u4TimeOutInMs); 

};


/*******************************************************************************
* 
********************************************************************************/
IImageTransform*
IImageTransform::
createInstance()
{
    ImageTransform* pImageTransformImp = new ImageTransform();
    if  ( ! pImageTransformImp )
    {
        MY_LOGE("[IImageTransform] fail to new ImageTransform");
        return  NULL;
    }
    //
    IImageTransformBridge*  pIImageTransform = new IImageTransformBridge(pImageTransformImp);
    if  ( ! pIImageTransform )
    {
        MY_LOGE("[IImageTransform] fail to new IImageTransformBridge");
        delete  pImageTransformImp;
        return  NULL;
    }
    //
    return  pIImageTransform;
    return NULL;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IImageTransformBridge::
destroyInstance()
{
    delete  mpImageTransformImp;  //  Firstly, delete the implementor here instead of destructor.
    delete  this;       //  Finally, delete myself.
}


/*******************************************************************************
* 
********************************************************************************/
IImageTransformBridge::
IImageTransformBridge(ImageTransform*const pImageTransform)
    : IImageTransform()
    , mLock()
    , mu4InitRefCount(0)
    , mpImageTransformImp(pImageTransform)
{
}


/*******************************************************************************
* 
********************************************************************************/
IImageTransformBridge::
~IImageTransformBridge()
{
}

/*******************************************************************************
* 
********************************************************************************/
MINT32
IImageTransformBridge::
getLastErrorCode() const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->getLastErrorCode();
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
IImageTransformBridge::
execute(ImgBufInfo const rSrcBufInfo, ImgBufInfo const rDstBufInfo, Rect const rROI, MUINT32 const u4Rotation, MUINT32 const u4Flip, MUINT32 const u4TimeOutInMs)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->execute(rSrcBufInfo, rDstBufInfo, rROI, u4Rotation, u4Flip, u4TimeOutInMs); 
}


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot

