#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_IIMAGE_TRANSFORM_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_IIMAGE_TRANSFORM_H_
//
//

#include <common/hw/hwstddef.h>

using namespace NSCamHW; 
/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Interface of Image Transform 
********************************************************************************/
class IImageTransform
{
protected:  ////    Constructor/Destructor.
    virtual         ~IImageTransform() {}

public:     ////    Attributes 
    virtual MINT32      getLastErrorCode() const = 0;

public:     ////    Instantiation.
    static IImageTransform* createInstance();
    virtual MVOID   destroyInstance() = 0;

public:     ////    Operations.
    /*
     *  Image transform , the functionality is such as bitblt function 
     *
     *  Params:
     *      rSrcBufInfo
     *      [I] The image buffer info of the input image 
     *          
     *
     *      rDstBufInfo
     *      [I] The image buffer info of the output image 
     *          
     *      rROI 
     *      [I] The crop of region of the input image 
     *   
     *      u4Rotation
     *      [I] The rotation operation 
     *      
     *      u4Flip
     *      [I] The flip operation
     * 
     *      u4TimeOutInMs
     *      [I] The time out of the operation
     *
     *  Return:
     *      MTRUE indicates success; MFALSE indicates failure, and an error code
     *      can be retrived by getLastErrorCode().
     */
    virtual  MBOOL    execute(ImgBufInfo const rSrcBufInfo, ImgBufInfo const rDstBufInfo, Rect const rROI, MUINT32 const u4Rotation, MUINT32 const u4Flip, MUINT32 const u4TimeOutInMs) = 0; 

};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_IIMAGE_TRANSFORM_H_

