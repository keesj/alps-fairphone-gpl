#define LOG_TAG "CamShot/Sample"
//
#include <inc/common/CamLog.h>
#define MY_LOGV(fmt, arg...)    CAM_LOGV("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGD(fmt, arg...)    CAM_LOGD("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGI(fmt, arg...)    CAM_LOGI("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGW(fmt, arg...)    CAM_LOGW("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGE(fmt, arg...)    CAM_LOGE("[%s] "fmt, __FUNCTION__, ##arg)
#define FUNCTION_LOG_START      MY_LOGD("+");
#define FUNCTION_LOG_END        MY_LOGD("-");

//
//
#include <common/CamTypes.h>
#include <common/CamDefs.h>
//
#include <common/hw/hwstddef.h>
//
#include <campipe/_ports.h>
//
#include <camshot/_params.h>
#include <camshot/_callbacks.h>


//
#include "../inc/SingleShotImp.h"
#include "../inc/SampleSingleShot.h"
//


/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* 
********************************************************************************/
SampleSingleShot::
SampleSingleShot(
    EShotMode const eShotMode,
    char const*const szCamShotName
)
    : SingleShotImp(eShotMode, szCamShotName)
{
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
init()
{
    FUNCTION_LOG_START;


        
    FUNCTION_LOG_END;
    //
    return MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
uninit()
{
     FUNCTION_LOG_START;



     FUNCTION_LOG_END;
     //
     return MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
start(SensorParam const & rSensorParam)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
startAsync(SensorParam const & rSensorParam)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
startOne(SensorParam const & rSensorParam)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
startOne(ImgBufInfo const & rImgBufInfo)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
stop()
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
setShotParam(ShotParam const & rParam)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
setJpegParam(JpegParam const & rParam)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL   
SampleSingleShot::
registerImgBufInfo(ECamShotImgBufType const eBufType, ImgBufInfo const &rImgBuf)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
SampleSingleShot::
sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3)
{
     FUNCTION_LOG_START;

     FUNCTION_LOG_END;
     //
     return MTRUE;
}

////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot

