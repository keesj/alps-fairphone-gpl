#ifndef PLL_H
#define PLL_H

#define AP_PLL_CON0         (0x10209000)
#define AP_PLL_CON1         (0x10209004)
#define AP_PLL_CON2         (0x10209008)
#define AP_PLL_CON3         (0x1020900C)
#define PLL_HP_CON0         (0x10209014)
#define PLL_TEST_CON0       (0x10209054)
#define PLL_TEST_CON1       (0x10209058)
#define ARMPLL_CON0         (0x10209200)
#define ARMPLL_CON1         (0x10209204)
#define ARMPLL_CON2         (0x10209208)
#define ARMPLL_PWR_CON0     (0x10209218)
#define MAINPLL_CON0        (0x1020921C)
#define MAINPLL_CON1        (0x10209220)
#define MAINPLL_CON2        (0x10209224)
#define MAINPLL_PWR_CON0    (0x10209234)
#define UNIVPLL_CON0        (0x10209238)
#define MMPLL_CON0          (0x10209240)
#define ISPPLL_CON0         (0x10209248)
#define MSDCPLL_CON0        (0x10209250)
#define MSDCPLL_CON1        (0x10209254)
#define MSDCPLL_CON2        (0x10209258)
#define MSDCPLL_PWR_CON0    (0x10209268)
#define TVDPLL_CON0         (0x1020926C)
#define TVDPLL_CON1         (0x10209270)
#define TVDPLL_CON2         (0x10209274)
#define TVDPLL_CON3         (0x10209278)
#define TVDPLL_PWR_CON0     (0x10209284)
#define LVDSPLL_CON0        (0x10209288)
#define LVDSPLL_CON1        (0x1020928C)
#define LVDSPLL_CON2        (0x10209290)
#define LVDSPLL_CON3        (0x10209294)
#define LVDSPLL_PWR_CON0    (0x102092A0)
#define AP_AUXADC_CON0      (0x10209400)
#define AP_AUXADC_CON1      (0x10209404)
#define TS_CON0             (0x10209600)
#define TS_CON1             (0x10209604)
#define AP_BB_CON0          (0x10209800)
#define AP_ABIST_MON_CON0   (0x10209E00)
#define AP_ABIST_MON_CON1   (0x10209E04)
#define AP_ABIST_MON_CON2   (0x10209E08)
#define AP_ABIST_MON_CON3   (0x10209E0C)

#define CLK_MODE            (0x10000100)
#define DCM_CFG	            (0x10000104)
#define CLK_CFG_0           (0x10000140)
#define CLK_CFG_1           (0x10000144)
#define CLK_CFG_2           (0x10000148)
#define CLK_CFG_3           (0x1000014C)
#define CLK_CFG_4           (0x10000150)
#define CLK_CFG_5           (0x10000154)
#define CLK_CFG_6           (0x10000158)
#define CLK_CFG_7           (0x1000015C)
#define CLK_MISC_CFG_2      (0x10000160)
#define CLK_CFG_8           (0x10000164)

#define TOP_CKMUXSEL        (0x10001000)
#define TOP_CKDIV1          (0x10001008)
#define TOP_DCMCTL          (0x10001010)

#define INFRA_PDN_SET       (0x10001040)
#define INFRA_PDN_CLR       (0x10001044)
#define INFRA_PDN_STA       (0x10001048)

#define PERI_PDN0_SET       (0x10003008)
#define PERI_PDN0_CLR       (0x10003010)
#define PERI_PDN0_STA       (0x10003018)

#define PERI_PDN1_SET       (0x1000300C)
#define PERI_PDN1_CLR       (0x10003014)
#define PERI_PDN1_STA       (0x1000301C)

//#define DRAMC_ASYNC

//#define BYPASS_MEMPLL1

//#define MEMPLL_CLK_150

//#define MEMPLL_CLK_250

//#define MEMPLL_CLK_266

//#define MEMPLL_CLK_400

//#define MEMPLL_CLK_500

#define MEMPLL_CLK_533

//#define MEMPLL_CLK_586

#define DDRPHY_3PLL_MODE

#endif