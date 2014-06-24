#ifndef _ISP_TUNING_MGR_H_
#define _ISP_TUNING_MGR_H_

namespace NSIspTuning
{

class IParamctrl;

/*******************************************************************************
*
*******************************************************************************/
class IspTuningMgr
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Ctor/Dtor.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
    //  Copy constructor is disallowed.
    IspTuningMgr(IspTuningMgr const&);
    //  Copy-assignment operator is disallowed.
    IspTuningMgr& operator=(IspTuningMgr const&);

public:  ////
    IspTuningMgr();
    ~IspTuningMgr();
    static IspTuningMgr& getInstance();
    MBOOL init(MINT32 i4SensorDev);
    MBOOL uninit();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public: // Attributes
    MBOOL setIspProfile(MINT32 const i4IspProfile);
    MINT32 getIspProfile() {return m_i4IspProfile;}
    MBOOL setSceneMode(MUINT32 const u4Scene);
    MBOOL setEffect(MUINT32 const u4Effect);
    MBOOL setOperMode(MINT32 const i4OperMode);
	MINT32 getOperMode();
	MBOOL setDynamicBypass(MBOOL const fgEnable);
	MBOOL setDynamicCCM(MBOOL bdynamic_ccm);
	MINT32 getDynamicBypass();
	MINT32 getDynamicCCM();
    MBOOL setSensorMode(MINT32 const i4SensorMode);
	MINT32 getSensorMode();
    MBOOL setZoomRatio(MINT32 const i4ZoomRatio_x100);
    MBOOL setAWBInfo(AWB_INFO_T const &rAWBInfo);
    MBOOL setAEInfo(AE_INFO_T const &rAEInfo);
    MBOOL setAFInfo(AF_INFO_T const &rAFInfo);
    MBOOL setFlashInfo(FLASH_INFO_T const &rFlashInfo);
	MBOOL enableDynamicTuning(MBOOL const fgEnable);
    MBOOL setIndex_Shading(MINT32 const i4IDX);
    MBOOL getIndex_Shading(MVOID*const pCmdArg);
	MBOOL setPureOBCInfo(const ISP_NVRAM_OBC_T *pOBCInfo);



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public: // ISP End-User-Defined Tuning Index.
    MBOOL setIspUserIdx_Edge(MUINT32 const u4Index);
    MBOOL setIspUserIdx_Hue(MUINT32 const u4Index);
    MBOOL setIspUserIdx_Sat(MUINT32 const u4Index);
    MBOOL setIspUserIdx_Bright(MUINT32 const u4Index);
    MBOOL setIspUserIdx_Contrast(MUINT32 const u4Index);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public: // Operations.
    MBOOL validate(MBOOL const fgForce = MFALSE);
    MBOOL validatePerFrame(MBOOL const fgForce = MFALSE);
    MBOOL getDebugInfo(NSIspExifDebug::IspExifDebugInfo_T& rIspExifDebugInfo);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Data member
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
    IParamctrl* m_pParamctrl_Main;
    IParamctrl* m_pParamctrl_Sub;
    IParamctrl* m_pParamctrl_Main2;
    MINT32      m_i4SensorDev;
    MBOOL       m_bDebugEnable;
    MINT32      m_i4IspProfile;

};

};  //  namespace NSIspTuning
#endif // _ISP_TUNING_MGR_H_

