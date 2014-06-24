#ifndef _MTK_CAMERA_INC_CAMSHOT_BUFFERS_H_
#define _MTK_CAMERA_INC_CAMSHOT_BUFFERS_H_

using namespace NSCamHW; 

/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////

/**  
 * @struct BayerImgBufInfo
 * @brief This structure is bayer image buffer info
 *
 */
struct BayerImgBufInfo: public ImgBufInfo
{
public:    //// fields.
    /**
      * @var u4PixelOrder 
      * The pixel oreder, 0:BGbGrR 1:GbBRGr 2:GrRBGb 3:RGrGbB 
      */    
    MUINT32 u4PixelOrder; 
    /**
      * @var u4BitDepth 
      * The bitdepth of the pixel, 8, 10, 12
      */        
    MUINT32 u4BitDepth; 
    /**
      * @var fgIsPacked 
      * Is the pixel packed 
      */        
    MBOOL   fgIsPacked; 
    
public:    //// constructors.
    BayerImgBufInfo(
    )
        : ImgBufInfo()
        , u4PixelOrder(0)
        , u4BitDepth(0)
        , fgIsPacked(0) 
    {   
    }
    //
    BayerImgBufInfo(
        ImgBufInfo const _ImgBufInfo, 
        MUINT32    const _u4PixelOrder, 
        MUINT32    const _u4BitDepth, 
        MBOOL      const _fgIsPacked
    )
        : ImgBufInfo(_ImgBufInfo)
        , u4PixelOrder(_u4PixelOrder)
        , u4BitDepth(_u4BitDepth)
        , fgIsPacked(_fgIsPacked)
    {
    }
};  

////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_INC_CAMSHOT_BUFFERS_H_

