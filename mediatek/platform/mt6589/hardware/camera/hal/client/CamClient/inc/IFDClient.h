#ifndef _MTK_HAL_CAMCLIENT_INC_IFDCLIENT_H_
#define _MTK_HAL_CAMCLIENT_INC_IFDCLIENT_H_
//


namespace android {
/******************************************************************************
 *
 ******************************************************************************/
class IParamsManager;


namespace NSCamClient {


/******************************************************************************
*   Face Detection Client Handler.
*******************************************************************************/
class IFDClient : public virtual RefBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Instantiation.
    //
    static sp<IFDClient>            createInstance(sp<IParamsManager> pParamsMgr);
    //
    virtual                         ~IFDClient() {}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////

    virtual bool                    init()                                  = 0;
    virtual bool                    uninit()                                = 0;

    virtual bool                    setImgBufProviderClient(
                                        sp<IImgBufProviderClient>const& rpClient
                                    )                                       = 0;

    /**
     *
     */
    virtual void                    setCallbacks(
                                        sp<CamMsgCbInfo> const& rpCamMsgCbInfo
                                    )                                       = 0;

    /**
     *
     */
    virtual status_t                sendCommand(int32_t cmd, int32_t arg1, int32_t arg2) = 0;
    virtual bool                    stopPreview()                           = 0;
    virtual bool                    takePicture()                           = 0;


    /**
     *
     */
    virtual void                    enableMsgType(int32_t msgType)          = 0;
    virtual void                    disableMsgType(int32_t msgType)         = 0;

};


}; // namespace NSCamClient
}; // namespace android
#endif  //_MTK_HAL_CAMCLIENT_INC_IFDCLIENT_H_

