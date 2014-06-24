#define LOG_TAG "campipe/sample"
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
#include <common/CamTypes.h>
#include <common/hw/hwstddef.h>
//
#include "../inc/PipeImp.h"
#include "../inc/SamplePipe.h"
//


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* 
********************************************************************************/
SamplePipe::
SamplePipe(
    char const*const szPipeName, 
    EPipeID const ePipeID, 
    ESWScenarioID const eSWScenarioID, 
    EScenarioFmt const eScenarioFmt
)
    : PipeImp(szPipeName, ePipeID, eSWScenarioID, eScenarioFmt)
{
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SamplePipe::
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
SamplePipe::
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
SamplePipe::
start()
{
    FUNCTION_LOG_START

    FUNCTION_LOG_END

    return  MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SamplePipe::
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
SamplePipe::
enqueBuf(PortID const ePortID, QBufInfo const& rQBufInfo)
{
    MY_LOGD("+ tid(%d) PortID:(type, index, inout)=(%d, %d, %d)",  gettid(), ePortID.type, ePortID.index, ePortID.inout);
    MY_LOGD("QBufInfo:(user, reserved, num)=(%x, %d, %d)", rQBufInfo.u4User, rQBufInfo.u4Reserved, rQBufInfo.vBufInfo.size());
    return  MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SamplePipe::
dequeBuf(PortID const ePortID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs /*= 0xFFFFFFFF*/)
{
    MY_LOGD("+ tid(%d) PortID:(type, index, inout, timeout)=(%d, %d, %d, %d)", gettid(), ePortID.type, ePortID.index, ePortID.inout, u4TimeoutMs);
    return  MTRUE;
}


/*******************************************************************************
* 
********************************************************************************/
MBOOL
SamplePipe::
configPipe(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts)
{
    MY_LOGD("+ %d in / %d out", vInPorts.size(), vOutPorts.size());
    return  MTRUE;
}

/*******************************************************************************
* 
********************************************************************************/
MBOOL
SamplePipe::
queryPipeProperty(vector<PortProperty> &vInPorts, vector<PortProperty> &vOutPorts)
{
    MY_LOGD("+ %d in / %d out", vInPorts.size(), vOutPorts.size());
    return  MTRUE;
}



/*******************************************************************************
* 
********************************************************************************/
MBOOL
SamplePipe::
sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3)
{
   return MTRUE; 
}

////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe

