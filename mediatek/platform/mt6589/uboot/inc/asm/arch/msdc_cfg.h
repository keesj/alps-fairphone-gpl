#ifndef _MSDC_CFG_H_
#define _MSDC_CFG_H_

/*--------------------------------------------------------------------------*/
/* Common Definition                                                        */
/*--------------------------------------------------------------------------*/
#include <config.h>
#ifdef CFG_MT6589_FPGA
#define FPGA_PLATFORM
#endif

#define MMC_DEBUG               (0)
#define MSDC_DEBUG              (0)

#define MSDC_USE_REG_OPS_DUMP   (0)
#ifdef FPGA_PLATFORM
#define MSDC_USE_DMA_MODE       (1)
#else
#define MSDC_USE_DMA_MODE       (1)
#endif

//#define MSDC0_BASE              (0xC1220000)
//#define MSDC1_BASE              (0xC1230000)
//#define MSDC2_BASE              (0xC1250000)
//#define MSDC3_BASE              (0xC1240000)

//#define FEATURE_MMC_SDIO
//#define FEATURE_MMC_UHS1
//#define FEATURE_MMC_BOOT_MODE
//#define FEATURE_MMC_WR_TUNING
#define FEATURE_MMC_RD_TUNING
#define FEATURE_MMC_CM_TUNING

#if MSDC_DEBUG
#define MSG_DEBUG
#endif

#endif /* end of _MSDC_CFG_H_ */

