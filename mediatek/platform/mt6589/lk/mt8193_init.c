#include <platform/mt8193.h>
#include <platform/mt_typedefs.h>
#include <platform/mt_i2c.h>


#ifdef MT8193_DISABLE_EXT_CLK_BUF
#define MT8193_DISABLE_DCXO 1
#else
#define MT8193_DISABLE_DCXO 0
#endif


#if MT8193_DISABLE_DCXO

/* Turn off BT clock buffer */
void mt8193_dxco_bt_disable(void)
{
    printf("mt8193_dxco_bt_disable()\n");

    u32 u4Tmp = 0;

    /* set bt clock buffer manual mode */
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG4);
	u4Tmp &= (~DCXO_ANACFG4_BT_MAN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG4, u4Tmp);

    /* disable dcxo ldo2 at manual mode */
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG2);
	u4Tmp &= (~DCXO_ANACFG2_LDO2_MAN_EN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG2, u4Tmp);

	/* disable dcxo ldo2*/
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG2);
	u4Tmp &= (~DCXO_ANACFG2_LDO2_EN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG2, u4Tmp);



	
}

/* Turn off ext1 clock buffer */
void mt8193_dxco_ext1_disable(void)
{
    printf("mt8193_dxco_ext1_disable()\n");

    u32 u4Tmp = 0;

    /* set ext1 clock buffer manual mode */
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG4);
	u4Tmp &= (~DCXO_ANACFG4_EXT1_MAN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG4, u4Tmp);

    /* disable dcxo ldo3 at manual mode */
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG2);
	u4Tmp &= (~DCXO_ANACFG2_LDO3_MAN_EN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG2, u4Tmp);

	/* disable dcxo ldo3*/
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG2);
	u4Tmp &= (~DCXO_ANACFG2_LDO3_EN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG2, u4Tmp);
}

/* Turn off ext2 clock buffer */
void mt8193_dxco_ext2_disable(void)
{
    printf("mt8193_dxco_ext2_disable()\n");

    u32 u4Tmp = 0;

    /* set ext2 clock buffer manual mode */
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG4);
	u4Tmp &= (~DCXO_ANACFG4_EXT2_MAN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG4, u4Tmp);

    /* disable dcxo ldo4 at manual mode */
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG2);
	u4Tmp &= (~DCXO_ANACFG2_LDO4_MAN_EN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG2, u4Tmp);

	/* disable dcxo ldo4*/
    u4Tmp = CKGEN_READ32(REG_RW_DCXO_ANACFG2);
	u4Tmp &= (~DCXO_ANACFG2_LDO4_EN);
	CKGEN_WRITE32(REG_RW_DCXO_ANACFG2, u4Tmp);
}

#endif


int mt8193_io_init(void)
{
    printf("lk mt8193_io_init() enter\n");

    u32 u4Tmp = 0;

    /* Modify some pad multi function as function 1*/
 
    u4Tmp = CKGEN_READ32(REG_RW_PMUX1);
    u4Tmp |= (1<<PMUX1_PAD_G0_FUNC);
    u4Tmp |= (1<<PMUX1_PAD_B5_FUNC);
    u4Tmp |= (1<<PMUX1_PAD_B4_FUNC);
    CKGEN_WRITE32(REG_RW_PMUX1, u4Tmp);

    u4Tmp = CKGEN_READ32(REG_RW_PMUX2);
    u4Tmp |= (1<<PMUX2_PAD_B3_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_B2_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_B1_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_B0_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_DE_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_VCLK_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_HSYNC_FUNC);
    u4Tmp |= (1<<PMUX2_PAD_VSYNC_FUNC);
    CKGEN_WRITE32(REG_RW_PMUX2, u4Tmp);
    

    printf("lk mt8193_io_init() exit\n");

    return 0;
}


int mt8193_init(void)
{
	  printf("uboot mt8193_init() enter\n");
	  
    mt8193_io_init();
    
#if MT8193_DISABLE_DCXO
    /* disable external clock buffer for power consumption issue except wifi only platform */
    mt8193_dxco_bt_disable();
    mt8193_dxco_ext1_disable();
    mt8193_dxco_ext2_disable();
        
#endif
      
	  printf("uboot mt8193_init() exit\n");
	  
    return (0);
}

