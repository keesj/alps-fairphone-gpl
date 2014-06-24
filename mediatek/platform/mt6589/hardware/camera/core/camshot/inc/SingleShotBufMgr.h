#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_ISHOTBUF_MANAGER_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_ISHOTBUF_MANAGER_H_
//
#include <common/CamTypes.h>

#include <camshot/_buffers.h>

/******************************************************************************
 *
 ******************************************************************************/


namespace NSCamShot {
/******************************************************************************
 *
 ******************************************************************************/


/******************************************************************************
 *  Single Shot Buffer Manager 
 ******************************************************************************/
class SingleShotBufMgr
{
public:     ////
    //
    SingleShotBufMgr();     
    ~SingleShotBufMgr();

public:     ////                Attributes.
    //
    BayerImgBufInfo     getBayerRawBufInfo() const;
    YuvImgBufInfo       getYuvRawBufInfo()   const;
    JpegImgBufInfo      getJpegBufInfo()     const; 
    //
};


/******************************************************************************
 *
 ******************************************************************************/
}; // namespace NSCamShot
#endif  //_MTK_CAMERA_CORE_CAMSHOT_INC_ISHOTBUF_MANAGER_H_

