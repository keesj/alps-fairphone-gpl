#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_IJPEG_CODEC_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_IJPEG_CODEC_H_
//
//
#include <common/CamDefs.h>
#include <common/hw/hwstddef.h>

using namespace NSCamHW; 
/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Interface of Jpeg Codec
********************************************************************************/
class IJpegCodec
{
protected:  ////    Constructor/Destructor.
    virtual         ~IJpegCodec() {}

public:     ////    Attributes 
    virtual MINT32      getLastErrorCode() const = 0;

public:     ////    Instantiation.
    static IJpegCodec* createInstance();
    virtual MVOID   destroyInstance() = 0;

public:     ////    Operations.
    /*
     *  Jpeg Codec , the functionality is used to encode jpeg 
     *
     *  Params:
     *      rSrcBufInfo
     *      [I] The image buffer info of the input image 
     *          
     *
     *      rDstBufInfo
     *      [I] The image buffer info of the output image 
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
                      ) = 0; 

};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_IJPEG_CODEC_H_

