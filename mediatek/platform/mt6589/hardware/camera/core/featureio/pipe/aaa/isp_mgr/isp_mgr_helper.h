#ifndef _ISP_MGR_HELPER_H_
#define _ISP_MGR_HELPER_H_


namespace NSIspTuning
{


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class T>
struct ISPType2Type;

#define BIND_ISP_TYPES(FROM_T, TO_T)\
    template <> struct ISPType2Type<FROM_T> { typedef TO_T type; }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BIND_ISP_TYPES(ISP_NVRAM_CTL_EN_T, ISP_MGR_CTL_EN_T);
BIND_ISP_TYPES(ISP_NVRAM_OBC_T, ISP_MGR_OBC_T);
BIND_ISP_TYPES(ISP_NVRAM_BPC_T, ISP_MGR_BNR_T);
BIND_ISP_TYPES(ISP_NVRAM_NR1_T, ISP_MGR_BNR_T);
BIND_ISP_TYPES(ISP_NVRAM_LSC_T, ISP_MGR_LSC_T);
BIND_ISP_TYPES(ISP_NVRAM_PGN_T, ISP_MGR_PGN_T);
BIND_ISP_TYPES(ISP_NVRAM_CFA_T, ISP_MGR_CFA_T);
BIND_ISP_TYPES(ISP_NVRAM_CCM_T, ISP_MGR_CCM_T);
BIND_ISP_TYPES(ISP_NVRAM_GGM_T, ISP_MGR_GGM_T);
BIND_ISP_TYPES(ISP_NVRAM_G2C_T, ISP_MGR_G2C_T);
BIND_ISP_TYPES(ISP_NVRAM_ANR_T, ISP_MGR_NBC_T);
BIND_ISP_TYPES(ISP_NVRAM_CCR_T, ISP_MGR_NBC_T);
BIND_ISP_TYPES(ISP_NVRAM_PCA_T, ISP_MGR_PCA_T);
BIND_ISP_TYPES(ISP_NVRAM_EE_T, ISP_MGR_SEEE_T);
BIND_ISP_TYPES(ISP_NVRAM_SE_T, ISP_MGR_SEEE_T);
BIND_ISP_TYPES(ISP_NVRAM_NR3D_T, ISP_MGR_NR3D_T);
BIND_ISP_TYPES(ISP_NVRAM_MFB_T, ISP_MGR_MFB_T);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ISP_XXX_T>
MVOID
getIspHWBuf(ESensorDev_T const eSensorDev, ISP_XXX_T& rParam)
{
    typedef typename ISPType2Type<ISP_XXX_T>::type ISP_MGR_T;
    ISP_MGR_T::getInstance(eSensorDev).get(rParam);
}


template <class ISP_XXX_T>
MVOID
putIspHWBuf(ESensorDev_T const eSensorDev, ISP_XXX_T const& rParam)
{
    typedef typename ISPType2Type<ISP_XXX_T>::type ISP_MGR_T;
    ISP_MGR_T::getInstance(eSensorDev).put(rParam);
}

template <class ISP_XXX_T>
MVOID
getIspReg(ESensorDev_T const eSensorDev, ISP_XXX_T& rParam)
{
    typedef typename ISPType2Type<ISP_XXX_T>::type ISP_MGR_T;
    ISP_MGR_T::getInstance(eSensorDev).reset();
    ISP_MGR_T::getInstance(eSensorDev).get(rParam);
}

#define prepareIspHWBuf putIspHWBuf

#if 0

//  Specialization: EFFECT EDGE -> REG: DM + EDGE + EE
template <>
MVOID
getIspHWBuf<ISP_EFFECT_EDGE_T>(ISP_EFFECT_EDGE_T& rParam);


//  Specialization: EFFECT EDGE -> REG: DM + EDGE + EE
template <>
MVOID
putIspHWBuf<ISP_EFFECT_EDGE_T>(ISP_EFFECT_EDGE_T const& rParam);


/*******************************************************************************
*
*******************************************************************************/
inline
MVOID
prepareIspHWBuf_enableShading(MBOOL const fgEnable)
{
    ISP_MGR_SHADING_T::getInstance().setEnableShading(fgEnable);
}


inline
MVOID
prepareIspHWBuf_enableNR1_DP(MBOOL const fgEnable)
{
    ISP_MGR_NR1_T::getInstance().setEnableDP(fgEnable);
}


inline
MVOID
prepareIspHWBuf_enableNR1_CT(MBOOL const fgEnable)
{
    ISP_MGR_NR1_T::getInstance().setEnableCT(fgEnable);
}


inline
MVOID
prepareIspHWBuf_enableNR1_NR(MBOOL const fgEnable)
{
    ISP_MGR_NR1_T::getInstance().setEnableNR(fgEnable);
}


inline
MVOID
prepareIspHWBuf_enableGamma(MBOOL const fgEnable)
{
    ISP_MGR_EE_T::getInstance().setEnableGamma(fgEnable);
}


/*******************************************************************************
*
*******************************************************************************/
#endif

};  //  NSIspTuning
#endif // _ISP_MGR_HELPER_H_

