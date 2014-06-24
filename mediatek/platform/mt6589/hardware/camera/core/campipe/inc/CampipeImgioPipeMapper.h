#ifndef _MTK_CAMERA_CORE_CAMPIPE_INC_CAMPIPE_IMGIOPIPE_MAPPER_H_
#define _MTK_CAMERA_CORE_CAMPIPE_INC_CAMPIPE_IMGIOPIPE_MAPPER_H_

// imageio/ispio, for mapper 
#include <inc/imageio/ispio_pipe_scenario.h>
#include <inc/imageio/ispio_stddef.h>

/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {

NSImageio::NSIspio::EScenarioID mapScenarioID(NSCamPipe::ESWScenarioID const eSWScenarioID, NSCamPipe::EPipeID ePipeID); 
NSImageio::NSIspio::EScenarioFmt mapScenarioFmt(NSCamPipe::EScenarioFmt const eScenarioFmt); 
NSImageio::NSIspio::ERawPxlID mapRawPixelID(MUINT32 const u4PixelID); 
void mapBufInfo(NSCamHW::BufInfo &rCamPipeBufInfo, NSImageio::NSIspio::BufInfo const &rBufInfo);
EImageFormat mapRawFormat(MUINT32 u4BitDepth); 
EImageFormat mapYUVFormat(MUINT32 u4ColorOrder); 

};    //namespace NSCamPipe


#endif //_MTK_CAMERA_CORE_CAMPIPE_INC_CAMPIPE_IMGIOPIPE_MAPPER_H_
