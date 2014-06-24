#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_IMAGE_TRANSFORM_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_IMAGE_TRANSFORM_H_
//

class ResMgrDrv; 
class PipeMgrDrv; 
/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Interface of Image Transform 
********************************************************************************/
class ImageTransform 
{
public:  ////    Constructor/Destructor.
    ImageTransform(); 
    virtual         ~ImageTransform() {}

public:     ////    Attributes 
    virtual MINT32      getLastErrorCode() const    { return mi4ErrorCode; }


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
     *  Return:
     *      MTRUE indicates success; MFALSE indicates failure, and an error code
     *      can be retrived by getLastErrorCode().
     */
    virtual  MBOOL    execute(ImgBufInfo const rSrcBufInfo, ImgBufInfo const rDstBufInfo, Rect const rROI, MUINT32 const u4Rotation, MUINT32 const u4Flip, MUINT32 const u4TimeOutInMs); 

private:
    MINT32              mi4ErrorCode;
    PipeMgrDrv   *mpPipeMgrDrv; 
    ResMgrDrv    *mpResMgrDrv; 
    //
    MBOOL        lock(MUINT32 const u4TimeOutInMs = 0xFFFFFFFF); 
    MBOOL        unlock(); 


};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_IIMAGE_TRANSFORM_H_

