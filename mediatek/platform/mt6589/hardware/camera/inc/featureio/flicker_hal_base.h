#ifndef _FLICKER_HAL_BASE_H_
#define _FLICKER_HAL_BASE_H_

#define HAL_FLICKER_AUTO_50HZ    50
#define HAL_FLICKER_AUTO_60HZ    60
#define HAL_FLICKER_AUTO_OFF       0

/*******************************************************************************
*
********************************************************************************/
enum FLKCmd_T {
	 FLKCmd_Update,
	 FLKCmd_GetDimenion,
	 FLKCmd_SetFLKMode,
	 FLKCmd_SetWindow,
	 FLKCmd_FlkEnable,
	 FLKCmd_FlkDISable,
	 FLKCmd_FlkPause,
	 FLKCmd_FlkResume,
	 FLKCmd_Uninit,

};


class FlickerHalBase {
public:
    static FlickerHalBase* createInstance();
    virtual MVOID      destroyInstance() = 0;

    virtual MINT32 createBuf()=0;
    virtual MVOID releaseBuf()=0;


    static FlickerHalBase* getInstance();
    virtual MINT32 open(MINT32 i4SensorDev)=0;
    virtual MVOID close()=0;


protected:
    virtual ~FlickerHalBase(){};

public:
    virtual MINT32  enableFlickerDetection(MBOOL bEnableFlicker) = 0;
    virtual MINT32 analyzeFlickerFrequency(MINT32 i4LMVcnt, MINT32 *i4LMV_x, MINT32 *i4LMV_y, MINT64 *i4vAFstat=NULL) = 0;
//    virtual MRESULT analyzeFlickerFrequency(MINT32 i4LMVcnt, MINT32 *i4LMV_x, MINT32 *i4LMV_y) = 0;
    virtual MINT32 setWindowInfo() = 0;
    virtual MINT32 getFlickerStatus(MINT32 *a_flickerStatus) = 0;
	virtual MBOOL sendCommand(FLKCmd_T eCmd,void* pi4Arg)=0;

};

#endif

