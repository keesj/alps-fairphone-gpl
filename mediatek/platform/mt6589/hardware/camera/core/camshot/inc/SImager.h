#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_SIMAGER_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_SIMAGER_H_
//
//
#include <common/CamDefs.h>

//
using namespace NSCamHW; 
//

/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
*
********************************************************************************/
class SImager
{
protected:
    struct TargetImgConfig : public ImgInfo
    {
        MUINT32 u4Flip; 
        Rect rROI; 
        MUINT32 u4Rotation; 
        MUINT32 u4IsSOI; 
        MUINT32 u4Quality; 
        MUINT32 u4Stride[3]; 

        TargetImgConfig(
        )
            : u4Flip(0)
            , rROI()
            , u4Rotation(0)
            , u4IsSOI(0)
            , u4Quality(0)
        {
            u4Stride[0] = u4Stride[1] = u4Stride[2] = 0; 
        }

        TargetImgConfig(
            MUINT32 _u4Flip, 
            Rect    _rROI,
            MUINT32 _u4Rotation, 
            MUINT32 _u4Quality, 
            MUINT32 _u4Stride[3]
        )
            : u4Flip(_u4Flip) 
            , rROI(_rROI.x, _rROI.y, _rROI.w, _rROI.h)
            , u4Rotation(_u4Rotation) 
            , u4Quality(_u4Quality)
        {
            u4Stride[0] = _u4Stride[0]; 
            u4Stride[1] = _u4Stride[1]; 
            u4Stride[2] = _u4Stride[2]; 
        }
    
    }; 

public:     ////    Constructor/Destructor.
    SImager(ImgBufInfo const & rImgBufInfo );
    virtual ~SImager() {}; 

public:     ////    Instantiation.

public:      //// attributes
    virtual MUINT32  getJpegSize() {return mu4JpegSize; }; 
public:     ////    Callback. 
    virtual MVOID    setCallback(SImagerNotifyCallback_t notify_cb, MVOID* user); 

public:     ////    Operations.
    virtual MBOOL    execute(MUINT32 u4TimeoutMs = 0xFFFFFFFF); 
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

public:     ////    Attributes 
    virtual MINT32      getLastErrorCode() const    { return mi4ErrorCode; }

private:   ////
    MINT32              mi4ErrorCode;
    MVOID*              mpCbUser;           //  Callback user.
    SImagerNotifyCallback_t    mNotifyCb;      //  notify callback function pointer.    
private:   //// 
    MUINT32     mu4JpegSize; 
    ImgBufInfo mSrcImgBufInfo; 
    TargetImgConfig mTargetImgInfo; 
    BufInfo mTargetBufInfo; 
    MUINT32     mu4StrideAlign[3]; 

private:     ////
    MBOOL    isSupportedSrcFormat(EImageFormat const eFmt); 
    //
    MBOOL    encode(
                  ImgBufInfo const rSrcBufInfo, 
                  ImgBufInfo const rDstBufInfo, 
                  Rect const rROI, 
                  MUINT32 const u4Rotation, 
                  MUINT32 const u4Flip, 
                  MUINT32 const u4Quality, 
                  MUINT32 const u4IsSOI, 
                  MUINT32 &u4EncSize
              ); 
    // 
    MBOOL    imgTransform(
                 ImgBufInfo const rSrcBufInfo, 
                 ImgBufInfo const rDstBufInfo, 
                 Rect const rROI, 
                 MUINT32 const u4Rotation, 
                 MUINT32 u4Flip,
                 MUINT32 const u4TimeoutInMs
             ); 
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_SIMAGER_H_

