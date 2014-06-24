#include "typedefs.h"
#include "mtk_timer.h"


/* register address */
#define RST_CTL0                    (0xc0009010)
#define PWR_CTL1                    (0xc0009024)
#define PWR_MON                     (0xc00090a8)
#define BOOTROM_BOOT_ADDR           (0xc0002030)
#define SCU_CPU_PWR_STATUS          (0xc000a008)


void power_off_cpu1(void)
{
    /* 1.1 Polling PWR_MON[13] = 1 to make sure CPU1 is in WFI */
    while (!(DRV_Reg32(PWR_MON) & (1U << 13)));
    
    /* 1.2 turn off neon1 */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x00000400);
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x00000100);
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x00000200);
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) & 0xfffff7ff);
    
    /* 2. Set PWR_CTL1[14] = 1 */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x00004000);
    
    /* 3. Set PWR_CTL1[12] = 1 */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x00001000);
    
    /* 4. Set PWR_CTL1[13] = 1 */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x00002000);
    
    /* 5. Set PWR_CTL1[4] = 0 for dormant mode, or set PWR_CTL1[3:0]=4¡¦b1111 for shutdown mode (shutdown mode now) */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x0000000f);
    //dsb();
    mdelay(2); //delay 2ms
    
    /* 6.1 Set PWR_CTL1[15] = 0 */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) & 0xffff7fff);
    
    /* 6.2 Set PWR_CTL1[25:24] = 2¡¦b10 for dormant mode or set 2¡¦b11 for shutdown mode (shutdown mode now) */
    DRV_WriteReg32(PWR_CTL1, DRV_Reg32(PWR_CTL1) | 0x03000000);
    
    /* 6.3 Set CPU1 power status register in SCU to dormant mode or shut-down mode (shutdown mode now) */
    DRV_WriteReg32(SCU_CPU_PWR_STATUS, DRV_Reg32(SCU_CPU_PWR_STATUS) | 0x00000300);
    //dsb();
}


