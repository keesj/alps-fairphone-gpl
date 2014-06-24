#ifndef RES_MGR_DRV_H
#define RES_MGR_DRV_H
//-----------------------------------------------------------------------------
typedef enum
{
    RES_MGR_DRV_SCEN_SW_NONE,
    RES_MGR_DRV_SCEN_SW_CAM_IDLE,
    RES_MGR_DRV_SCEN_SW_CAM_PRV,
    RES_MGR_DRV_SCEN_SW_CAM_CAP,
    RES_MGR_DRV_SCEN_SW_VIDEO_PRV,
    RES_MGR_DRV_SCEN_SW_VIDEO_REC,
    RES_MGR_DRV_SCEN_SW_VIDEO_VSS,
    RES_MGR_DRV_SCEN_SW_ZSD,
    RES_MGR_DRV_SCEN_SW_N3D,
}RES_MGR_DRV_SCEN_SW_ENUM;
//
typedef enum
{
    RES_MGR_DRV_SCEN_HW_NONE,
    RES_MGR_DRV_SCEN_HW_IC,
    RES_MGR_DRV_SCEN_HW_VR,
    RES_MGR_DRV_SCEN_HW_ZSD,
    RES_MGR_DRV_SCEN_HW_IP,
    RES_MGR_DRV_SCEN_HW_N3D,
    RES_MGR_DRV_SCEN_HW_VSS
}RES_MGR_DRV_SCEN_HW_ENUM;
//
typedef enum
{
    RES_MGR_DRV_DEV_CAM,
    RES_MGR_DRV_DEV_ATV,
    RES_MGR_DRV_DEV_VT
}RES_MGR_DRV_DEV_ENUM;
//
typedef struct
{
    RES_MGR_DRV_SCEN_SW_ENUM    ScenSw;
    RES_MGR_DRV_SCEN_HW_ENUM    ScenHw;
    RES_MGR_DRV_DEV_ENUM        Dev;
}RES_MGR_DRV_MODE_STRUCT;
//-----------------------------------------------------------------------------
class ResMgrDrv
{
    protected:
        virtual ~ResMgrDrv() {};
    //
    public:
        static ResMgrDrv* CreateInstance(void);
        virtual MVOID   DestroyInstance(void) = 0;
        virtual MBOOL   Init(void) = 0;
        virtual MBOOL   Uninit(void) = 0;
        virtual MBOOL   GetMode(RES_MGR_DRV_MODE_STRUCT* pMode) = 0;
        virtual MBOOL   SetMode(RES_MGR_DRV_MODE_STRUCT* pMode) = 0;
};
//-----------------------------------------------------------------------------
#endif


