#define LOG_TAG "MtkCam/CamDevice"
//
#include <CamDevice.h>
#include <DefaultCamDevice.h>
#include <drv/IResManager.h>
//
using namespace android;
using namespace NSCamDevice;


/******************************************************************************
*
*******************************************************************************/
#define MY_LOGV(fmt, arg...)        CAM_LOGV("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
#define MY_LOGD(fmt, arg...)        CAM_LOGD("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
#define MY_LOGI(fmt, arg...)        CAM_LOGI("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
#define MY_LOGW(fmt, arg...)        CAM_LOGW("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
#define MY_LOGE(fmt, arg...)        CAM_LOGE("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
#define MY_LOGA(fmt, arg...)        CAM_LOGA("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
#define MY_LOGF(fmt, arg...)        CAM_LOGF("(%d)(%s:%d)[%s] "fmt, ::gettid(), getDevName(), getOpenId(), __FUNCTION__, ##arg)
//
#define MY_LOGV_IF(cond, ...)       do { if ( (cond) ) { MY_LOGV(__VA_ARGS__); } }while(0)
#define MY_LOGD_IF(cond, ...)       do { if ( (cond) ) { MY_LOGD(__VA_ARGS__); } }while(0)
#define MY_LOGI_IF(cond, ...)       do { if ( (cond) ) { MY_LOGI(__VA_ARGS__); } }while(0)
#define MY_LOGW_IF(cond, ...)       do { if ( (cond) ) { MY_LOGW(__VA_ARGS__); } }while(0)
#define MY_LOGE_IF(cond, ...)       do { if ( (cond) ) { MY_LOGE(__VA_ARGS__); } }while(0)
#define MY_LOGA_IF(cond, ...)       do { if ( (cond) ) { MY_LOGA(__VA_ARGS__); } }while(0)
#define MY_LOGF_IF(cond, ...)       do { if ( (cond) ) { MY_LOGF(__VA_ARGS__); } }while(0)


/******************************************************************************
 *
 ******************************************************************************/
extern "C"
ICamDevice*
createCamDevice_Default(
    String8 const&          rDevName, 
    int32_t const           i4OpenId
)
{
    return new DefaultCamDevice(rDevName, i4OpenId);
}


/******************************************************************************
*
*******************************************************************************/
DefaultCamDevice::
DefaultCamDevice(
    String8 const&          rDevName, 
    int32_t const           i4OpenId
)
    : CamDevice(rDevName, i4OpenId)
    //
#if '1'==MTKCAM_HAVE_SENSOR_HAL
    , mpSensorHal(NULL)
#endif
    //
#if '1'==MTKCAM_HAVE_3A_HAL
    , mp3AHal(NULL)
#endif
    //
{
}


/******************************************************************************
*
*******************************************************************************/
DefaultCamDevice::
~DefaultCamDevice()
{
}


/******************************************************************************
*
*******************************************************************************/
bool
DefaultCamDevice::
onInit()
{
    MY_LOGD("+");
    AutoCPTLog cptlog(Event_Hal_DefaultCamDevice_init);
    CamProfile  profile(__FUNCTION__, "DefaultCamDevice");
    //
    bool    ret = false;
    int     err = 0;
    int const iHalSensorDevId = DevMetaInfo::queryHalSensorDev(getOpenId());
    //
    //--------------------------------------------------------------------------
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Resource +");
    IResManager* pResManager = IResManager::getInstance();
    //
    if  ( pResManager != NULL )
    {
        if(!(pResManager->open("DefaultCamDevice")))
        {
            MY_LOGE("pResManager->open fail");
            goto lbExit;
        }
    }
    //
    profile.print("Resource -");
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Resource -");
    //--------------------------------------------------------------------------
    //  (1) Open Sensor
#if '1'==MTKCAM_HAVE_SENSOR_HAL
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Sensor Hal +");
    MY_LOGD("SensorHal::createInstance(), iHalSensorDevId:%#x", iHalSensorDevId);
    mpSensorHal = SensorHal::createInstance();
    if  ( ! mpSensorHal ) {
        MY_LOGE("mpSensorHal == NULL");
        goto lbExit;
    }
    //
    err = mpSensorHal->sendCommand((halSensorDev_e)iHalSensorDevId, SENSOR_CMD_SET_SENSOR_DEV);
    if  ( err ) {
        mpSensorHal->destroyInstance();
        mpSensorHal = NULL;
        goto lbExit;
    }
    err = mpSensorHal->init();
    if  ( err ) {
        mpSensorHal->destroyInstance();
        mpSensorHal = NULL;
        goto lbExit;
    }
    profile.print("Sensor Hal -");
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Sensor Hal -");
#endif  //MTKCAM_HAVE_SENSOR_HAL
    //--------------------------------------------------------------------------
    //  (2) Open 3A
#if '1'==MTKCAM_HAVE_3A_HAL
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "3A Hal +");
    mp3AHal = NS3A::Hal3ABase::createInstance(iHalSensorDevId);
    if  ( ! mp3AHal ) {
        MY_LOGE("Hal3ABase::createInstance() fail");
        goto lbExit;
    }
    profile.print("3A Hal -");
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "3A Hal -");
#endif  //MTKCAM_HAVE_3A_HAL
    //--------------------------------------------------------------------------
    //  (3) Init Base.
    if  ( ! CamDevice::onInit() )
    {
        goto lbExit;
    }
    //
    //--------------------------------------------------------------------------
    //
    ret = true;
lbExit:
    profile.print("");
    MY_LOGD("- ret(%d)", ret);
    return  ret;
}


/******************************************************************************
*
*******************************************************************************/
bool
DefaultCamDevice::
onUninit()
{
    MY_LOGD("+");
    AutoCPTLog cptlog(Event_Hal_DefaultCamDevice_uninit);
    CamProfile  profile(__FUNCTION__, "DefaultCamDevice");
    //
    //--------------------------------------------------------------------------
    //  (1) Uninit Base
    CamDevice::onUninit();
    profile.print("CamDevice::onUninit() -");
    //--------------------------------------------------------------------------
    //  (2) Close 3A
#if '1'==MTKCAM_HAVE_3A_HAL
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "3A Hal +");
    if  ( mp3AHal )
    {
        mp3AHal->destroyInstance();
        mp3AHal = NULL;
    }
    profile.print("3A Hal -");
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "3A Hal -");
#endif  //MTKCAM_HAVE_3A_HAL
    //--------------------------------------------------------------------------
    //  (4) Close Sensor
#if '1'==MTKCAM_HAVE_SENSOR_HAL
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Sensor Hal +");
    if  ( mpSensorHal )
    {
        mpSensorHal->uninit();
        mpSensorHal->destroyInstance();
        mpSensorHal = NULL;
        MY_LOGD("SensorHal::destroyInstance()");
    }
    profile.print("Sensor Hal -");
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Sensor Hal -");
#endif  //MTKCAM_HAVE_SENSOR_HAL
    //--------------------------------------------------------------------------
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Resource +");
    IResManager* pResManager = IResManager::getInstance();
    //
    if  ( pResManager != NULL )
    {
        if(!(pResManager->close("DefaultCamDevice")))
        {
            MY_LOGE("pResManager->close fail");
        }
    }
    profile.print("Resource -");
    CPTLogStr(Event_Hal_DefaultCamDevice_init, CPTFlagSeparator, "Resource -");
    //--------------------------------------------------------------------------
    //
    profile.print("");
    MY_LOGD("-");
    return  true;
}


/******************************************************************************
* [Template method] Called by startPreview().
*******************************************************************************/
bool
DefaultCamDevice::
onStartPreview()
{
    bool ret = false;
    //
    //  (1) Update Hal App Mode.
    if  ( ! mpParamsMgr->updateHalAppMode() )
    {
        MY_LOGE("mpParamsMgr->updateHalAppMode() fail");
        goto lbExit;
    }

    //  (2) Initialize Camera Adapter.
    if  ( ! initCameraAdapter() )
    {
        MY_LOGE("NULL Camera Adapter");
        goto lbExit;
    }
    //
    ret = true;
lbExit:
    return ret;
}


/******************************************************************************
* [Template method] Called by stopPreview().
*******************************************************************************/
void
DefaultCamDevice::
onStopPreview()
{
    if  ( mpCamAdapter != 0 )
    {
        mpCamAdapter->cancelPicture();
        mpCamAdapter->uninit();
        mpCamAdapter.clear();
    }
}


/******************************************************************************
* Set the camera parameters. This returns BAD_VALUE if any parameter is
* invalid or not supported.
*******************************************************************************/
status_t
DefaultCamDevice::
setParameters(const char* params)
{
    status_t status = OK;
    //
    //  (1) Update params to mpParamsMgr.
    status = mpParamsMgr->setParameters(String8(params));
    if  ( OK != status ) {
        goto lbExit;
    }

    //  Here (1) succeeded.
    //  (2) If CamAdapter exists, apply mpParamsMgr to CamAdapter;
    //      otherwise it will be applied when CamAdapter is created.
    {
        sp<ICamAdapter> pCamAdapter = mpCamAdapter;
        if  ( pCamAdapter != 0 ) {
            status = pCamAdapter->setParameters();
        }
#if '1'==MTKCAM_HAVE_3A_HAL
        else if ( mp3AHal )
        {
            //  Flashlight may turn on/off in case that CamAdapter doesn't exist (i.e. never call startPreview)

            using namespace NS3A;
            Param_T param;
            //
            if  ( ! mp3AHal->getParams(param) ) {
                MY_LOGW("3A Hal::getParams() fail - err(%x)", mp3AHal->getErrorCode());
            }
            //
            String8 const s8FlashMode = mpParamsMgr->getStr(CameraParameters::KEY_FLASH_MODE);
            if  ( ! s8FlashMode.isEmpty() ) {
                param.u4StrobeMode = PARAMSMANAGER_MAP_INST(eMapFlashMode)->valueFor(s8FlashMode);
            }
            //
            if  ( ! mp3AHal->setParams(param) ) {
                MY_LOGW("3A Hal::setParams() fail - err(%x)", mp3AHal->getErrorCode());
            }
        }
        else
        {
            MY_LOGW("mp3AHal==NULL");
        }
#endif
    }

lbExit:
    return  status;
}

