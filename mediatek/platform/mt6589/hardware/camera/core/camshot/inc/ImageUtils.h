#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_IMAGE_UTILS_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_IMAGE_UTILS_H_
//
//
#include <common/CamDefs.h>
#include <common/hw/hwstddef.h>
#include <common/camutils/HwMisc.h>

using namespace NSCamHW; 
/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////
//
MBOOL querySensorResolution(MUINT32 const u4DeviceID, MUINT32 const u4Scenario, MUINT32 &u4Width, MUINT32 &u4Height);  
EImageFormat  querySensorFmt(MUINT32 const u4DeviceID, MUINT32 const u4Scenario, MUINT32 const u4BitDepth); 
//
MBOOL     querySensorInfo(MUINT32 const u4DeviceID, MUINT32 const u4Scenario, MUINT32 const u4BitDepth, EImageFormat &eFmt,  MUINT32 &u4Width, MUINT32 &u4Height, MUINT32 & u4RawPixelID);
//
EImageFormat  mapBayerFormat(MUINT32 const u4BitDepth); 
//
MUINT32    queryImgBufSize(EImageFormat const eFmt, MUINT32 const u4Width, MUINT32 const u4Height); 
//
MUINT32    queryImgStride(EImageFormat const eFmt,  MUINT32 const u4Width, MUINT32 const u4PlaneIndex); 
//
MUINT32    queryRawStride(MUINT32 const imgFmt, MUINT32 const imgWidth);
//

////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_IJPEG_CODEC_H_

