#define LOG_TAG "CamShot/JpegCodec"
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
#include "../../inc/IJpegCodec.h"
#include "./inc/JpegCodec.h"
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
class IJpegCodecBridge : public IJpegCodec
{
    friend  class   IJpegCodec;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    
    mutable android::Mutex      mLock;
    android::Mutex&             getLockRef()    { return mLock; }
    MUINT32                     mu4InitRefCount;

protected:  ////    Implementor.
    JpegCodec*const            mpJpegCodecImp;
    inline  JpegCodec const*   getImp() const  { return mpJpegCodecImp; }
    inline  JpegCodec*         getImp()        { return mpJpegCodecImp; }

protected:  ////    Constructor/Destructor.
                    IJpegCodecBridge(JpegCodec*const pJpegCodec);
                    ~IJpegCodecBridge();

private:    ////    Disallowed.
                    IJpegCodecBridge(IJpegCodecBridge const& obj);
    IJpegCodecBridge&  operator=(IJpegCodecBridge const& obj);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Instantiation.
    virtual MVOID   destroyInstance();

public:     ////    Attributes.
    virtual MINT32      getLastErrorCode() const;

   //
public:     ////    Operations.
    virtual MBOOL    encode(
                          ImgBufInfo const rSrcBufInfo, 
                          ImgBufInfo const rDstBufInfo, 
                          Rect const rROI, 
                          MUINT32 const u4Rotation, 
                          MUINT32 const u4Flip, 
                          MUINT32 const u4Quality, 
                          MUINT32 const u4IsSOI, 
                          MUINT32 &u4EncSize
                      ); 
};


/*******************************************************************************
* 
********************************************************************************/
IJpegCodec*
IJpegCodec::
createInstance()
{
    JpegCodec* pJpegCodecImp = new JpegCodec();
    if  ( ! pJpegCodecImp )
    {
        MY_LOGE("[IJpegCodec] fail to new JpegCodec");
        return  NULL;
    }
    //
    IJpegCodecBridge*  pIJpegCodec = new IJpegCodecBridge(pJpegCodecImp);
    if  ( ! pIJpegCodec )
    {
        MY_LOGE("[IJpegCodec] fail to new IJpegCodecBridge");
        delete  pJpegCodecImp;
        return  NULL;
    }
    //
    return  pIJpegCodec;
    return NULL;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID
IJpegCodecBridge::
destroyInstance()
{
    delete  mpJpegCodecImp;  //  Firstly, delete the implementor here instead of destructor.
    delete  this;       //  Finally, delete myself.
}


/*******************************************************************************
* 
********************************************************************************/
IJpegCodecBridge::
IJpegCodecBridge(JpegCodec*const pJpegCodec)
    : IJpegCodec()
    , mLock()
    , mu4InitRefCount(0)
    , mpJpegCodecImp(pJpegCodec)
{
}


/*******************************************************************************
* 
********************************************************************************/
IJpegCodecBridge::
~IJpegCodecBridge()
{
}

/*******************************************************************************
* 
********************************************************************************/
MINT32
IJpegCodecBridge::
getLastErrorCode() const
{
    Mutex::Autolock _lock(mLock);
    return  getImp()->getLastErrorCode();
}



/*******************************************************************************
* 
********************************************************************************/
MBOOL
IJpegCodecBridge::
encode(
    ImgBufInfo const rSrcBufInfo, 
    ImgBufInfo const rDstBufInfo, 
    Rect const rROI, 
    MUINT32 const u4Rotation, 
    MUINT32 const u4Flip, 
    MUINT32 const u4Quality, 
    MUINT32 const u4IsSOI, 
    MUINT32 &u4EncSize
)
{
    Mutex::Autolock _lock(mLock);
    return getImp()->encode(rSrcBufInfo, rDstBufInfo, rROI, u4Rotation, u4Flip, u4Quality, u4IsSOI, u4EncSize); 
}


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot

