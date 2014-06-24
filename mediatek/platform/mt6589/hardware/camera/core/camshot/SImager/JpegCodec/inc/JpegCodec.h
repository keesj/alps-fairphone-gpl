#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_JPEG_CODEC_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_JPEG_CODEC_H_
//

#include <drv/imem_drv.h>

/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Interface of Image Transform 
********************************************************************************/
class JpegCodec 
{
public:  ////    Constructor/Destructor.
    JpegCodec(); 
    virtual         ~JpegCodec() {}

public:     ////    Attributes 
    virtual MINT32      getLastErrorCode() const    { return mi4ErrorCode; }


public:     ////    Operations.
    /*
     *  Jpeg Codec , the functionality is used to encode jpeg 
     *
     *  Params:
     *      rSrcBufInfo
     *      [I] The image buffer info of the input image 
     *          
     *      rDstBufInfo
     *      [I] The image buffer info of the output image 
     *          
     *      rROI 
     *      [I] The crop of region 
     *
     *      u4Rotation 
     *      [I] The rotation 
     *
     *      u4Flip 
     *      [I] The flip operation 
     *
     *      u4Quality 
     *      [I] The Jpeg quality 1~100 
     *   
     *      u4IsSOI
     *      [I] Is include SOI
     *      
     *      u4EncSize
     *      [O] Jpeg output bitstream size 
     * 
     *  Return:
     *      MTRUE indicates success; MFALSE indicates failure, and an error code
     *      can be retrived by getLastErrorCode().
     */
    virtual  MBOOL    encode(
                          ImgBufInfo const rSrcBufInfo, 
                          ImgBufInfo const rDstBufInfo, 
                          Rect const rROI, 
                          MUINT32 const u4Rotation, 
                          MUINT32 const u4Flip, 
                          MUINT32 const u4Quality, 
                          MUINT32 const u4IsSOI, 
                          MUINT32 &u4EncSize
                      ); 
private:
    MINT32              mi4ErrorCode;
    MUINT32   mu4DumpFlag; 


private:
    MBOOL     isSupportedFormat(EImageFormat const eFmt); 
    MBOOL     checkIfNeedImgTransform(ImgBufInfo const rSrcBufInfo, ImgBufInfo const rDstBufInfo, Rect const rROI, MUINT32 const u4Rotation, MUINT32 const u4Flip);
    MBOOL     encode(ImgBufInfo const rSrcBufInfo, ImgBufInfo const rDstBufInfo, MUINT32 const u4Quality, MUINT32 const u4IsSOI, MUINT32 &u4EncSize);
    //
    MBOOL     allocMem(IMEM_BUF_INFO & rMemBuf); 
    MBOOL     deallocMem(IMEM_BUF_INFO & rMemBuf); 

};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_IIMAGE_TRANSFORM_H_

