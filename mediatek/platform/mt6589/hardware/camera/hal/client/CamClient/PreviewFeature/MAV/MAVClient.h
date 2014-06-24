#ifndef _MTK_HAL_CAMCLIENT_MAVCLIENT_H_
#define _MTK_HAL_CAMCLIENT_MAVCLIENT_H_
//
#include <CamUtils.h>
#include <system/camera.h>
#include <drv/imem_drv.h>
#include <pthread.h>
#include <semaphore.h>
#include <cutils/properties.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include "CamTypes.h"
#include "3DF_hal_base.h"
#include "inc/IFeatureClient.h"

using namespace android;
using namespace MtkCamUtils;

//
namespace android {
namespace NSCamClient {

/******************************************************************************
 *  Preview Client Handler.
 ******************************************************************************/
class MAVClient : public IFeatureClient
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Instantiation.
    //
    MAVClient(int ShotNum);
    virtual    ~MAVClient();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////
    virtual bool      init(int bufwidth,int bufheight);
    virtual bool      uninit();
    virtual MINT32    mHalCamFeatureProc(MVOID * bufadr, int32_t& mvX, int32_t& mvY, int32_t& dir, MBOOL& isShot);
    virtual bool      stopFeature(int cancel);
    virtual MVOID     setImgCallback(ImgDataCallback_t data_cb);
    virtual MINT32    mHalCamFeatureCompress();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  MAVClient.Scenario function
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:
    virtual MINT32    ISShot(MVOID * bufadr, MVOID *arg1, MBOOL &shot);
    virtual MINT32    CreateMotionSrc(MVOID * srcbufadr, int ImgWidth, int ImgHeight, MVOID * dstbufadr);   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  MAVClinet function
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:    
    virtual MINT32    mHalCamFeatureMerge();
    virtual MINT32    mHalCamFeatureAddImg();    
    virtual MBOOL     allocMem(IMEM_BUF_INFO &memBuf);
    virtual MBOOL     deallocMem(IMEM_BUF_INFO &memBuf);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Thread
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:     
    static MVOID*     MAVthreadFunc(void *arg); 
    pthread_t         MAVFuncThread;
    sem_t             MAVSemThread;
    sem_t             MAVmergeDone;
    MBOOL             mCancel;
    MBOOL             mStop;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Image Buffer
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected: 
    IMemDrv*          mpIMemDrv;  
    IMEM_BUF_INFO     mpframeBuffer[MAV_PIPE_MAX_IMAGE_NUM];
    IMEM_BUF_INFO     mpMotionBuffer;
    IMEM_BUF_INFO     mpMAVMotionBuffer;
    IMEM_BUF_INFO     mpWarpBuffer;
    IMEM_BUF_INFO     mpMAVWorkingBuf;
    int               mMAVFrameWidth;
    int               mMAVFrameHeight;
    int               mMAVFrameSize;
    ImgDataCallback_t mDataCb;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Parameter
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
private:	        
    int32_t 	        MAVnum;
    hal3DFBase* 	    mpMAVObj;
    int32_t 	        mMAVFrameIdx;
    int32_t			    mMAVaddImgIdx; 
    int32_t 		    mJPGFrameAddr;
    MavPipeResultInfo   mpMAVResult;
    uint8_t  	      	SaveFileName[64];
    mutable Mutex       mLock;
    mutable Mutex 	    mLockUninit;
		  
};
}; // namespace NSCamClient
}; // namespace android
#endif  //_MTK_HAL_CAMCLIENT_PREVIEW_PREVIEWCLIENT_H_

