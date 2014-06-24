#ifndef __DPI_REG_H__
#define __DPI_REG_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned EN         : 1;
	unsigned rsv_1      : 31;
}DPI_REG_EN, *PDPI_REG_EN;

typedef struct
{
    unsigned DPI_OEN_OFF    : 1;
    unsigned DPI_BG_EN      : 1;
	unsigned INTL_EN		: 1;
	unsigned TDFP_EN		: 1;
	unsigned CLPF_EN		: 1;
	unsigned YUV422_EN		: 1;
	unsigned YCMUX_EN		: 1;
	unsigned CSC_EN			: 1;
	unsigned EMBSYNC_EN		: 1;
	unsigned rsv_9          : 7;
    unsigned INRBSWAP		: 1;
	unsigned rsv_17         :15;
} DPI_REG_CNTL, *PDPI_REG_CNTL;


typedef struct
{
    unsigned VSYNC          : 1;
    unsigned rsv_1          : 31;
} DPI_REG_INTERRUPT, *PDPI_REG_INTERRUPT;


typedef struct
{
    UINT16 WIDTH;
    UINT16 HEIGHT;
} DPI_REG_SIZE, *PDPI_REG_SIZE;


typedef struct
{
    unsigned DIVISOR  : 5;
    unsigned rsv_5    : 3;
    unsigned DUTY     : 5;
    unsigned rsv_13   : 18;
    unsigned POLARITY : 1;
} DPI_REG_CLKCNTL, *PDPI_REG_CLKCNTL;

typedef struct
{
    unsigned DP_START      : 1;
    unsigned TGEN_START    : 1;
    unsigned OUT_EN        : 1;
    unsigned rsv_3         : 29;
} DPI_REG_STATUS, *PDPI_REG_STATUS;


typedef struct
{
	unsigned OFIX_EN         : 1;
    unsigned rsv_1           : 30;
	unsigned DPI_OEN_ON          : 1;
} DPI_REG_TMODE, *PDPI_REG_TMODE;

typedef struct
{
    unsigned HPW       : 8;
    unsigned HBP       : 8;
    unsigned HFP       : 8;
    unsigned HSYNC_POL : 1;
    unsigned DE_POL    : 1;
    unsigned rsv_26    : 6;
} DPI_REG_TGEN_HCNTL, *PDPI_REG_TGEN_HCNTL;

typedef struct
{
    unsigned HBP       : 12;
	unsigned rsv_12    : 4;
    unsigned HFP       : 12;
    unsigned rsv_28    : 4;
} DPI_REG_TGEN_HPORCH, *PDPI_REG_TGEN_HPORCH;

typedef struct
{
    unsigned VPW_LODD  : 8;
	unsigned VPW_HALF_LODD  : 1;
    unsigned rsv_9    : 23;
} DPI_REG_TGEN_VWIDTH_LODD, *PDPI_REG_TGEN_VWIDTH_LODD;

typedef struct
{
    unsigned VBP_LODD  : 8;
	unsigned VBP_HALF_LODD  : 1;
    unsigned rsv_9    : 7;
    unsigned VFP_LODD  : 8;
	unsigned VFP_HALF_LODD  : 1;
    unsigned rsv_25    : 7;
} DPI_REG_TGEN_VPORCH_LODD, *PDPI_REG_TGEN_VPORCH_LODD;

typedef struct
{
    unsigned VPW       : 8;
    unsigned VBP       : 8;
    unsigned VFP       : 8;
    unsigned VSYNC_POL : 1;
    unsigned rsv_25    : 7;
} DPI_REG_TGEN_VCNTL, *PDPI_REG_TGEN_VCNTL;

typedef struct
{
    unsigned BG_RIGHT  : 11;
	unsigned rsv_11    : 5;
    unsigned BG_LEFT   : 11;
    unsigned rsv_27    : 5;
} DPI_REG_BG_HCNTL, *PDPI_REG_BG_HCNTL;


typedef struct
{
    unsigned BG_BOT   : 10;
	unsigned rsv_10   : 6;
    unsigned BG_TOP   : 10;
    unsigned rsv_26   : 6;
} DPI_REG_BG_VCNTL, *PDPI_REG_BG_VCNTL;


typedef struct
{
    unsigned BG_B     : 8;
	unsigned BG_G     : 8;
    unsigned BG_R     : 8;
    unsigned rsv_24   : 8;
} DPI_REG_BG_COLOR, *PDPI_REG_BG_COLOR;


typedef struct
{
    DPI_REG_EN        DPI_EN;           // 0000
    UINT32   		  DPI_RST;			//0004
    DPI_REG_INTERRUPT INT_ENABLE;       // 0008
    DPI_REG_INTERRUPT INT_STATUS;       // 000C
    DPI_REG_CNTL      CNTL;             // 0010

	DPI_REG_CLKCNTL   CLK_CNTL; 		// 0014

    DPI_REG_SIZE      SIZE;             // 0018

	UINT32            TGEN_HWIDTH;      // 001C
    DPI_REG_TGEN_HPORCH TGEN_HPORCH;    // 0020

	DPI_REG_TGEN_VWIDTH_LODD TGEN_VWIDTH_LODD;	// 0024
    DPI_REG_TGEN_VPORCH_LODD TGEN_VPORCH_LODD;	// 0028

	UINT32 			   rsv_002C[9];
	
    DPI_REG_BG_HCNTL   BG_HCNTL;        // 0050  
    DPI_REG_BG_VCNTL   BG_VCNTL;        // 0054  
    DPI_REG_BG_COLOR   BG_COLOR;        // 0058  
} volatile DPI_REGS, *PDPI_REGS;

#ifndef BUILD_UBOOT
STATIC_ASSERT(0x0018 == offsetof(DPI_REGS, SIZE));
STATIC_ASSERT(0x0058 == offsetof(DPI_REGS, BG_COLOR));
#endif
#ifdef __cplusplus
}
#endif

#endif // __DPI_REG_H__

