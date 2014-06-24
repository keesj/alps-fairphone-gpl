#define LOG_TAG "campipe/pipeimp"
//
/*******************************************************************************
*
********************************************************************************/
#include <inc/common/CamLog.h>
#define MY_LOGV(fmt, arg...)    CAM_LOGV("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGD(fmt, arg...)    CAM_LOGD("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGI(fmt, arg...)    CAM_LOGI("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGW(fmt, arg...)    CAM_LOGW("[%s] "fmt, __FUNCTION__, ##arg)
#define MY_LOGE(fmt, arg...)    CAM_LOGE("[%s] "fmt, __FUNCTION__, ##arg)
//
#include <common/CamTypes.h>
#include <common/hw/hwstddef.h>
//
#include "./inc/PipeImp.h"
//


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {

////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
*
********************************************************************************/
PipeImp::
PipeImp(
    char const*const szPipeName,
    EPipeID const ePipeID,
    ESWScenarioID const eSWScenarioID,
    EScenarioFmt const eScenarioFmt
)
    : mszPipeName(szPipeName)
    , mePipeID(ePipeID)
    //
    , mi4ErrorCode(0)
    //
    , mpCbUser(NULL)
    , mi4NotifyMsgSet(0)
    , mNotifyCb(NULL)
    , mi4DataMsgSet(0)
    , mDataCb(NULL)
    //
    , meSWScenarioID(eSWScenarioID)
    , meScenarioFmt(eScenarioFmt)
    //
{
}

/*******************************************************************************
*
********************************************************************************/
MVOID
PipeImp::
setCallbacks(PipeNotifyCallback_t notify_cb, PipeDataCallback_t data_cb, MVOID* user)
{
    MY_LOGV("(notify_cb, data_cb, user)=(%p, %p, %p)", notify_cb, data_cb, user);
    mpCbUser = user;
    mNotifyCb = notify_cb;
    mDataCb = data_cb;
}


/*******************************************************************************
*
********************************************************************************/
MBOOL
PipeImp::
onNotifyCallback(PipeNotifyInfo const& msg) const
{
    MBOOL   ret = MTRUE;
    //
    if  ( mNotifyCb )
    {
        mNotifyCb(mpCbUser, msg);
        ret = MTRUE;
    }
    else
    {
        MY_LOGW("Notify Callback is NULL");
        ret = MFALSE;
    }
    return  ret;
}


/*******************************************************************************
*
********************************************************************************/
MBOOL
PipeImp::
onDataCallback(PipeDataInfo const& msg) const
{
    MBOOL   ret = MTRUE;
    //
    if  ( mDataCb )
    {
        mDataCb(mpCbUser, msg);
        ret = MTRUE;
    }
    else
    {
        MY_LOGW("Data Callback is NULL");
        ret = MFALSE;
    }
    return  ret;
}


/*******************************************************************************
* 
********************************************************************************/
MVOID 
PipeImp::
dumpPipeProperty(vector<PortProperty> const &vInPorts, vector<PortProperty> const &vOutPorts)
{
    //
    MY_LOGD("PipeProperty In Ports:"); 
    for (MUINT32 i = 0 ; i < vInPorts.size(); i++) 
    {
        MY_LOGD("(type, index, inout, format, rotate, flip): (%d, %d, %d, 0x%x, %d, %d)", 
                               vInPorts.at(i).type, vInPorts.at(i).index, vInPorts.at(i).inout, 
                               vInPorts.at(i).u4SupportFmt,vInPorts.at(i).fgIsSupportRotate,vInPorts.at(i).fgIsSupportFlip);                                                        
    }
    //
    MY_LOGD("PipeProperty Out Ports:"); 
    for (MUINT32 i = 0 ; i < vOutPorts.size(); i++) 
    {
        MY_LOGD("(type, index, inout, format, rotate, flip): (%d, %d, %d, 0x%x, %d, %d)", 
                               vOutPorts.at(i).type, vOutPorts.at(i).index, vOutPorts.at(i).inout, 
                               vOutPorts.at(i).u4SupportFmt,vOutPorts.at(i).fgIsSupportRotate,vOutPorts.at(i).fgIsSupportFlip);                                                        
    }
}



////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe


