#define LOG_TAG "pca_mgr"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <aaa_types.h>
#include <aaa_log.h>
#include <camera_custom_nvram.h>
#include <awb_param.h>
#include <ae_param.h>
#include <isp_tuning.h>
#include <isp_mgr.h>
#include <isp_mgr_helper.h>
#include "pca_mgr.h"

using namespace NSIspTuning;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <ESensorDev_T const eSensorDev>
class PcaMgrDev : public PcaMgr
{
public:
    static
    PcaMgr*
    getInstance(ISP_NVRAM_PCA_STRUCT& rIspPca)
    {
        static PcaMgrDev<eSensorDev> singleton(rIspPca);
        return &singleton;
    }
    virtual MVOID destroyInstance() {}

    PcaMgrDev(ISP_NVRAM_PCA_STRUCT& rIspPca)
        : PcaMgr(eSensorDev, rIspPca)
    {}

    virtual ~PcaMgrDev() {}

};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define INSTANTIATE(_dev_id) \
    case _dev_id: return  PcaMgrDev<_dev_id>::getInstance(rIspPca)

PcaMgr*
PcaMgr::
createInstance(ESensorDev_T const eSensorDev, ISP_NVRAM_PCA_STRUCT& rIspPca)
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

