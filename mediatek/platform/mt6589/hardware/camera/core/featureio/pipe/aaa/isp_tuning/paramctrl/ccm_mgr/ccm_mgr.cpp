#define LOG_TAG "ccm_mgr"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <aaa_types.h>
#include <aaa_log.h>
#include <camera_custom_nvram.h>
#include <isp_tuning.h>
#include <camera_feature.h>
#include <awb_param.h>
#include <ae_param.h>
#include <af_param.h>
#include <flash_param.h>
#include <isp_tuning_cam_info.h>
#include <isp_tuning_idx.h>
#include <isp_tuning_custom.h>
#include <isp_mgr.h>
#include <isp_mgr_helper.h>
#include <dynamic_ccm.h>
#include "ccm_mgr.h"

using namespace NSIspTuning;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <ESensorDev_T const eSensorDev>
class CcmMgrDev : public CcmMgr
{
public:
    static
    CcmMgr*
    getInstance(ISP_NVRAM_REGISTER_STRUCT& rIspNvramReg, ISP_NVRAM_CCM_POLY22_STRUCT& rISPCcmPoly22, IspTuningCustom* pIspTuningCustom)
    {
        static CcmMgrDev<eSensorDev> singleton(rIspNvramReg, rISPCcmPoly22, pIspTuningCustom);
        return &singleton;
    }
    virtual MVOID destroyInstance() {}

    CcmMgrDev(ISP_NVRAM_REGISTER_STRUCT& rIspNvramReg, ISP_NVRAM_CCM_POLY22_STRUCT& rISPCcmPoly22, IspTuningCustom* pIspTuningCustom)
        : CcmMgr(eSensorDev, rIspNvramReg, rISPCcmPoly22, pIspTuningCustom)
    {}

    virtual ~CcmMgrDev() {}

};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define INSTANTIATE(_dev_id) \
    case _dev_id: return  CcmMgrDev<_dev_id>::getInstance(rIspNvramReg, rISPCcmPoly22, pIspTuningCustom)

CcmMgr*
CcmMgr::
createInstance(ESensorDev_T const eSensorDev, ISP_NVRAM_REGISTER_STRUCT& rIspNvramReg, ISP_NVRAM_CCM_POLY22_STRUCT& rISPCcmPoly22, IspTuningCustom* pIspTuningCustom)
{
    switch  (eSensorDev)
    {
    INSTANTIATE(ESensorDev_Main);       //  Main Sensor
    INSTANTIATE(ESensorDev_MainSecond); //  Main Second Sensor
    INSTANTIATE(ESensorDev_Sub);        //  Sub Sensor
    default:
        break;
    }

    return  MNULL;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MVOID 
CcmMgr::
calculateCCM(AWB_INFO_T const& rAWBInfo)
{
    AWB_GAIN_T rD65 = rAWBInfo.rLightAWBGain.rD65;
    AWB_GAIN_T rTL84 = rAWBInfo.rLightAWBGain.rTL84;
    AWB_GAIN_T rCWF = rAWBInfo.rLightAWBGain.rCWF;
    AWB_GAIN_T rA = rAWBInfo.rLightAWBGain.rA;

    // refine light source AWB gain for multi-CCM
    m_pIspTuningCustom->refineLightSourceAWBGainforMultiCCM(rD65, rTL84, rCWF, rA);

    MultiCCM(rD65, rTL84, rCWF, rA, rAWBInfo.rCurrentAWBGain, m_rISPCcmPoly22, m_rCCMInput, m_rCCMOutput);
}


