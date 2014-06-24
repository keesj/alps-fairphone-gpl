#ifndef _MTK_CAMERA_DEVICE_INC_DEFAULTCAMDEVICE_H_
#define _MTK_CAMERA_DEVICE_INC_DEFAULTCAMDEVICE_H_
//
//
#if '1'==MTKCAM_HAVE_SENSOR_HAL
    #include <drv/sensor_hal.h>
#endif
//
#if '1'==MTKCAM_HAVE_3A_HAL
    #include <common/CamTypes.h>
    #include <featureio/aaa_hal_base.h>
#endif


namespace android {
namespace NSCamDevice {


/******************************************************************************
*   Default Camera Device
*******************************************************************************/
class DefaultCamDevice : public CamDevice
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ICamDevice Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////

    virtual status_t                setParameters(const char* params);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Operations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Instantiation.

                                    ~DefaultCamDevice();
                                    DefaultCamDevice(
                                        String8 const&          rDevName, 
                                        int32_t const           i4OpenId
                                    );

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:  ////                    [Template method] Operations.
    /**
     * Initialize the device resources owned by this object.
     */
    virtual bool                    onInit();

    /**
     * Uninitialize the device resources owned by this object. Note that this is
     * *not* done in the destructor.
     */
    virtual bool                    onUninit();

    /**
     * [Template method] Called by startPreview().
     */
    virtual bool                    onStartPreview();

    /**
     * [Template method] Called by stopPreview().
     */
    virtual void                    onStopPreview();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Data Members.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////
    //
#if '1'==MTKCAM_HAVE_SENSOR_HAL
    SensorHal*                      mpSensorHal;
#endif
    //
#if '1'==MTKCAM_HAVE_3A_HAL
    NS3A::Hal3ABase*                mp3AHal;
#endif
    //
};


};  // NSCamDevice
};  // namespace android
#endif  //_MTK_CAMERA_DEVICE_INC_DEFAULTCAMDEVICE_H_
