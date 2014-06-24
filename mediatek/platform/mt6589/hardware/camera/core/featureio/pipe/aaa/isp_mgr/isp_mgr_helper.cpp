#define LOG_TAG "isp_mgr_helper"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <aaa_types.h>
#include <aaa_log.h>
#include <camera_custom_nvram.h>
#include <awb_param.h>
#include <ae_param.h>
#include <isp_mgr.h>
#include "isp_mgr_helper.h"

namespace NSIspTuning
{


#if 0

/*******************************************************************************
* prepareIspHWBuf Function Template Specialization
*******************************************************************************/
//  Specialization: EFFECT EDGE -> REG: DM + EDGE + EE
template <>
MVOID
prepareIspHWBuf(ISP_EFFECT_EDGE_T const& rParam)
{
    ISP_MGR_DM_T::getInstance().put(rParam);
    ISP_MGR_EDGE_T::getInstance().put(rParam);
    ISP_MGR_EE_T::getInstance().put(rParam);
}


//  Specialization: EFFECT EDGE -> REG: DM + EDGE + EE
template <>
MVOID
getIspHWBuf(ISP_EFFECT_EDGE_T& rParam)
{
    ISP_MGR_DM_T::getInstance().get(rParam);
    ISP_MGR_EDGE_T::getInstance().get(rParam);
    ISP_MGR_EE_T::getInstance().get(rParam);
}
#endif

/*******************************************************************************
*
*******************************************************************************/
};  //  NSIspTuning

