//
#include <inc/common/CamTypes.h>

//
#include <vector>
using namespace std;

//
#include <campipe/_scenario.h>
#include <campipe/_identity.h>
#include <inc/common/hw/hwstddef.h>


// imageio/ispio, for mapper 
#include <inc/imageio/ispio_pipe_scenario.h>
#include <inc/imageio/ispio_stddef.h>
//
#include <kd_imgsensor_define.h>

namespace NSCamPipe {
/*******************************************************************************
* 
********************************************************************************/
NSImageio::NSIspio::EScenarioID 
mapScenarioID(NSCamPipe::ESWScenarioID const eSWScenarioID, NSCamPipe::EPipeID ePipeID)
{   
   if (NSCamPipe::ePipeID_1x2_Sensor_Tg_Isp_Mem == ePipeID) //camio 
   { 
       switch (eSWScenarioID) 
       {
            case NSCamPipe::eSWScenarioID_CAPTURE_NORMAL:       // Normal capture   
            case NSCamPipe::eSWScenarioID_CAPTURE_ZSD:          // ZSD capture 
                return NSImageio::NSIspio::eScenarioID_ZSD; 
            break; 
            case NSCamPipe::eSWScenarioID_MTK_PREVIEW:           // MTK preview 
            case NSCamPipe::eSWScenarioID_DEFAULT_PREVIEW:
            case NSCamPipe::eSWScenarioID_VIDEO:
            case NSCamPipe::eSWScenarioID_VSS:
            default:
                return NSImageio::NSIspio::eScenarioID_VSS;
            break; 
       }    
   }
   else if (NSCamPipe::ePipeID_1x2_Mem_Isp_Cdp_Mem == ePipeID)  //postproc
   {
       switch (eSWScenarioID) 
       {    //
            case NSCamPipe::eSWScenarioID_CAPTURE_NORMAL:       // Normal capture   
            case NSCamPipe::eSWScenarioID_CAPTURE_ZSD:          // ZSD capture 
                return NSImageio::NSIspio::eScenarioID_IP; 
            break; 
            case NSCamPipe::eSWScenarioID_MTK_PREVIEW:          // MTK preview 
            case NSCamPipe::eSWScenarioID_DEFAULT_PREVIEW:
            case NSCamPipe::eSWScenarioID_VIDEO:
            case NSCamPipe::eSWScenarioID_VSS:
            default:
                return NSImageio::NSIspio::eScenarioID_VSS;
            break; 
       } 
   }
   else if (NSCamPipe::ePipeID_1x2_Mem_Cdp_Mem == ePipeID)   // Cdp 
   {
       switch (eSWScenarioID) 
       {
            case NSCamPipe::eSWScenarioID_CAPTURE_NORMAL:       // Normal capture   
            case NSCamPipe::eSWScenarioID_CAPTURE_ZSD:          // ZSD capture 
                return NSImageio::NSIspio::eScenarioID_ZSD; 
            break; 
            case NSCamPipe::eSWScenarioID_PLAYBACK:
                return NSImageio::NSIspio::eScenarioID_IP;
            break; 
            case NSCamPipe::eSWScenarioID_MTK_PREVIEW:           // MTK preview 
            case NSCamPipe::eSWScenarioID_DEFAULT_PREVIEW:
            case NSCamPipe::eSWScenarioID_VIDEO:
            case NSCamPipe::eSWScenarioID_VSS:
            default:
                return NSImageio::NSIspio::eScenarioID_VSS;
            break; 
       }         
   }
   return NSImageio::NSIspio::eScenarioID_VSS; 
}

/*******************************************************************************
* 
********************************************************************************/
NSImageio::NSIspio::EScenarioFmt 
mapScenarioFmt(NSCamPipe::EScenarioFmt const eScenioFmt)
{
    switch (eScenioFmt) 
    {
        case NSCamPipe::eScenarioFmt_RAW:
            return NSImageio::NSIspio::eScenarioFmt_RAW; 
        break; 
        case NSCamPipe::eScenarioFmt_YUV:
            return NSImageio::NSIspio::eScenarioFmt_YUV;
        break; 
        case NSCamPipe::eScenarioFmt_RGB:
            return NSImageio::NSIspio::eScenarioFmt_RGB;
        break; 
        case NSCamPipe::eScenarioFmt_JPG:
            return NSImageio::NSIspio::eScenarioFmt_JPG;
        break;      
        default:
            return NSImageio::NSIspio::eScenarioFmt_UNKNOWN;
        break; 
    }
    
}



/*******************************************************************************
* 
********************************************************************************/
NSImageio::NSIspio::ERawPxlID 
mapRawPixelID(MUINT32 const u4PixelID)
{
    switch(u4PixelID) 
    {
        case 0:
            return NSImageio::NSIspio::ERawPxlID_B; 
        break; 
        case 1:
            return NSImageio::NSIspio::ERawPxlID_Gb;
        break; 
        case 2: 
            return NSImageio::NSIspio::ERawPxlID_Gr;
        break; 
        case 3:
            return NSImageio::NSIspio::ERawPxlID_R;        
        break; 
        default:
            return NSImageio::NSIspio::ERawPxlID_Gb;
        break; 
    }


}

/*******************************************************************************
* 
********************************************************************************/
void mapBufInfo(NSCamHW::BufInfo &rCamPipeBufInfo, NSImageio::NSIspio::BufInfo const &rBufInfo)
{    
    rCamPipeBufInfo.u4BufSize = rBufInfo.u4BufSize;
    rCamPipeBufInfo.u4BufVA = rBufInfo.u4BufVA;
    rCamPipeBufInfo.u4BufPA = rBufInfo.u4BufPA;
    rCamPipeBufInfo.i4MemID = rBufInfo.memID;

#warning [TODO] i4TimeStamp_us, i4TimeStamp_sec
}



/*******************************************************************************
* 
********************************************************************************/
EImageFormat 
mapRawFormat(MUINT32 u4BitDepth)
{
    switch (u4BitDepth)
    {
        case 8:
            return eImgFmt_BAYER8; 
        break; 
        case 10:
            return eImgFmt_BAYER10; 
        break; 
        case 12:
            return eImgFmt_BAYER12; 
        break; 
        default:
            return eImgFmt_BAYER8; 
            break; 
    }
}

/*******************************************************************************
* 
********************************************************************************/
EImageFormat
mapYUVFormat(MUINT32 u4ColorOrder)
{
    switch (u4ColorOrder)
    {
        case SENSOR_OUTPUT_FORMAT_UYVY:
        case SENSOR_OUTPUT_FORMAT_CbYCrY:
            return eImgFmt_UYVY; 
        break; 
        case SENSOR_OUTPUT_FORMAT_VYUY:
        case SENSOR_OUTPUT_FORMAT_CrYCbY:
            return eImgFmt_VYUY; 
        break; 
        case SENSOR_OUTPUT_FORMAT_YUYV:
        case SENSOR_OUTPUT_FORMAT_YCbYCr:
            return eImgFmt_YUY2; 
        break; 
        case SENSOR_OUTPUT_FORMAT_YVYU:
        case SENSOR_OUTPUT_FORMAT_YCrYCb:
            return eImgFmt_YVYU; 
        break; 
        default:
            return eImgFmt_YUY2; 
        break; 
    }
}



}; 
