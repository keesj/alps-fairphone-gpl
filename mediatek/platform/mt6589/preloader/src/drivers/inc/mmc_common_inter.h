#ifndef __MMC_COMMON_INTER_H__
#define __MMC_COMMON_INTER_H__

#include "typedefs.h"
#include "platform.h"

extern u32 mmc_init_device (void);

#if CFG_LEGACY_USB_DOWNLOAD
extern u32 mmc_read_data (u8 * buf, u32 offset);
extern u32 mmc_write_data (u8 * buf, u32 offset);
extern bool mmc_erase_data (u32 offset, u32 offset_limit, u32 size);
extern void mmc_wait_ready (void);
extern u32 mmc_find_safe_block (u32 offset);

extern u32 mmc_chksum_per_file (u32 mmc_offset, u32 img_size);
extern u32 mmc_chksum_body (u32 chksm, char *buf, u32 pktsz);
#endif

#endif /* __MMC_COMMON_INTER_H__ */
