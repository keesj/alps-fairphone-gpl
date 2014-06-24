#ifndef _TPILE_DRV_IMP_H_
#define _TPILE_DRV_IMP_H_
//-----------------------------------------------------------------------------

#include "tpipe_config.h"
#include "tpipe_drv.h"
#include "imem_drv.h"

//-----------------------------------------------------------------------------
using namespace android;
//-----------------------------------------------------------------------------


/**************************************************************************
 *                      D E F I N E S / M A C R O S                       *
 **************************************************************************/
    // reg_4004
#define TPIPE_CTL_EN1_TG1_BIT  (0)
#define TPIPE_CTL_EN1_TG2_BIT  (1)
#define TPIPE_CTL_EN1_BIN_BIT  (2)
#define TPIPE_CTL_EN1_OB_BIT   (3)
#define TPIPE_CTL_EN1_LSC_BIT  (5)  //
#define TPIPE_CTL_EN1_BNR_BIT  (7)  //
#define TPIPE_CTL_EN1_HRZ_BIT  (9)
#define TPIPE_CTL_EN1_PGN_BIT  (11)
#define TPIPE_CTL_EN1_PAK_BIT  (12)
#define TPIPE_CTL_EN1_PAK2_BIT (13)
#define TPIPE_CTL_EN1_SGG_BIT  (15)
#define TPIPE_CTL_EN1_AF_BIT   (16)
#define TPIPE_CTL_EN1_FLK_BIT  (17)
#define TPIPE_CTL_EN1_AA_BIT   (18)
#define TPIPE_CTL_EN1_LCS_BIT  (19)
#define TPIPE_CTL_EN1_UNP_BIT  (20) //
#define TPIPE_CTL_EN1_CFA_BIT  (21) //
#define TPIPE_CTL_EN1_CCL_BIT  (22)
#define TPIPE_CTL_EN1_G2G_BIT  (23)
#define TPIPE_CTL_EN1_DGM_BIT  (24)
#define TPIPE_CTL_EN1_LCE_BIT  (25) //
#define TPIPE_CTL_EN1_GGM_BIT  (26)
#define TPIPE_CTL_EN1_C02_BIT  (27) //
#define TPIPE_CTL_EN1_MFB_BIT  (28) //
#define TPIPE_CTL_EN1_C24_BIT  (29) //
#define TPIPE_CTL_EN1_CAM_BIT  (30)
#define TPIPE_CTL_EN1_BIN2_BIT (31)

    // reg_4008
#define TPIPE_CTL_EN2_G2C_BIT     (0)
#define TPIPE_CTL_EN2_C42_BIT     (1)   //
#define TPIPE_CTL_EN2_NBC_BIT     (2)   //
#define TPIPE_CTL_EN2_PCA_BIT     (3)
#define TPIPE_CTL_EN2_SEEE_BIT    (4)   //
#define TPIPE_CTL_EN2_NR3D_BIT    (5)   //
#define TPIPE_CTL_EN2_CQ0C_BIT    (14)
#define TPIPE_CTL_EN2_CQ0B_BIT    (15)
#define TPIPE_CTL_EN2_EIS_BIT     (16)
#define TPIPE_CTL_EN2_CDRZ_BIT    (17)  //
#define TPIPE_CTL_EN2_CURZ_BIT    (18)  //
#define TPIPE_CTL_EN2_PRZ_BIT     (21)  //
#define TPIPE_CTL_EN2_UV_CRSA_BIT (23)
#define TPIPE_CTL_EN2_FE_BIT      (24)
#define TPIPE_CTL_EN2_GDMA_BIT    (25)
#define TPIPE_CTL_EN2_FMT_BIT     (26)
#define TPIPE_CTL_EN2_CQ1_BIT     (27)
#define TPIPE_CTL_EN2_CQ2_BIT     (28)
#define TPIPE_CTL_EN2_CQ3_BIT     (29)
#define TPIPE_CTL_EN2_G2G2_BIT    (30)  //
#define TPIPE_CTL_EN2_CQ0_BIT     (31)

    // reg_400C
#define TPIPE_CTL_DMA_IMGO_BIT  (0)
#define TPIPE_CTL_DMA_LSCI_BIT  (1)
#define TPIPE_CTL_DMA_ESFKO_BIT (3)
#define TPIPE_CTL_DMA_AAO_BIT   (5)
#define TPIPE_CTL_DMA_LCSO_BIT  (6)
#define TPIPE_CTL_DMA_IMGI_BIT  (7)
#define TPIPE_CTL_DMA_IMGCI_BIT (8)
#define TPIPE_CTL_DMA_IMG2O_BIT (10)
#define TPIPE_CTL_DMA_FLKI_BIT  (11)
#define TPIPE_CTL_DMA_LCEI_BIT  (12)
#define TPIPE_CTL_DMA_VIPI_BIT  (13)
#define TPIPE_CTL_DMA_VIP2I_BIT (14)
#define TPIPE_CTL_DMA_VIDO_BIT  (19)
#define TPIPE_CTL_DMA_DISPO_BIT (21)
//
#define TPIPE_CTL_BIT_EN1(_val_,_bit_)      ((_val_)<<TPIPE_CTL_EN1_##_bit_##_BIT)
#define TPIPE_CTL_BIT_EN2(_val_,_bit_)      ((_val_)<<TPIPE_CTL_EN2_##_bit_##_BIT)
#define TPIPE_CTL_BIT_DMA(_val_,_bit_)      ((_val_)<<TPIPE_CTL_DMA_##_bit_##_BIT)
//
#define TPIPE_DBG_BUFFER_NUM    (3)

/**************************************************************************
 *     E N U M / S T R U C T / T Y P E D E F    D E C L A R A T I O N     *
 **************************************************************************/


/**************************************************************************
 *                 E X T E R N A L    R E F E R E N C E S                 *
 **************************************************************************/

/**************************************************************************
 *        P U B L I C    F U N C T I O N    D E C L A R A T I O N         *
 **************************************************************************/

/**************************************************************************
 *                   C L A S S    D E C L A R A T I O N                   *
 **************************************************************************/
class TpipeDrvImp : public TpipeDrv
{

    public:

    protected:
        TpipeDrvImp();
        ~TpipeDrvImp();
    //
    public:
        static TpipeDrv*  getInstance(void);
        virtual void    destroyInstance(void);
        virtual MBOOL   init(void);
        virtual MBOOL   uninit(void);
        virtual MBOOL   configTdriPara(TdriDrvCfg* pTdriInfo);
        virtual MBOOL   runDbgTpipeMain(void);
        MBOOL   runTpipeMain(TdriDrvCfg* pTdriInfo);
        MBOOL   updateFeatureIO(TdriDrvCfg *pDst, TdriDrvCfg* pSrc, int partUpdateFlag);
        MBOOL   updateImageIO(TdriDrvCfg *pDst, TdriDrvCfg* pSrc);

    //
    private:
        mutable Mutex       mLock;
        volatile MINT32     mInitCount;
        ISP_TPIPE_CONFIG_STRUCT *pConfigTpipeStruct;    // for tpipe algorithm
        ISP_TPIPE_CONFIG_STRUCT *pDbgTpipeStruct[TPIPE_DBG_BUFFER_NUM];    // for tpipe debug
        TdriDrvCfg *pKeepTdriInfo[TPIPE_DRV_CQ_NUM];    // tpipe data will be saved here
        MINT32 dbgBufIdx;
        MINT32 fdDbgTpipeStruct[TPIPE_DBG_BUFFER_NUM];
        MINT32 fdConfigTpipeStruct;
        MINT32 fdConfigTdriInfo;
        MINT32 fdKeepTpipeInfo;
        MINT32 tpipeAlgoStructSize;
        MINT32 tpipeInfoStructSize;
        IMemDrv*        m_pImemDrv;
        IMEM_BUF_INFO   m_tileDataInfo;
        IMEM_BUF_INFO   m_WBInfo;
        IMEM_BUF_INFO   m_KeepTpipeInfo[TPIPE_DRV_CQ_NUM];
        IMEM_BUF_INFO   m_DbgTpipeInfo[TPIPE_DBG_BUFFER_NUM];

};

//-----------------------------------------------------------------------------
#endif  // _TPILE_DRV_IMP_H_

