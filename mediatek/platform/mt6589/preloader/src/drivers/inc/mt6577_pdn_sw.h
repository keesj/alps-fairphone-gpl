#ifndef PDN_SW_H
#define PDN_SW_H

// PDNCONA
// PDNSETA
// PDNCLRa

 //APMCUSYS_PDN_CLR0
typedef enum
{
    PDN_PERI_DMA = 0,
    PDN_PERI_USB = 1,
    PDN_PERI_SEJ = 2,
    PDN_PERI_I2C3 = 3,
    PDN_PERI_GPT = 4,
    PDN_PERI_KP = 5,
    PDN_PERI_GPIO = 6,
    PDN_PERI_UART1 = 7,
    PDN_PERI_UART2 = 8,
    PDN_PERI_UART3 = 9,
    PDN_PERI_SIM = 10,
    PDN_PERI_PWM = 11,
    PDN_PERI_PWM1 = 12,
    PDN_PERI_PWM2 = 13,
    PDN_PERI_PWM3 = 14,
    PDN_PERI_MSDC = 15,
    PDN_PERI_SWDBG = 16,
    PDN_PERI_NFI = 17,
    PDN_PERI_I2C2 = 18,
    PDN_PERI_IRDA = 19,
    PDN_PERI_I2C = 21,
//    PDN_PERI_TOUC     =       21,
    PDN_PERI_SIM2 = 22,
    PDN_PERI_MSDC2 = 23,
    PDN_PERI_ADC = 26,
    PDN_PERI_TP = 27,
    PDN_PERI_XGPT = 28,
    PDN_PERI_UART4 = 29,
    PDN_PERI_MSDC3 = 30,
    PDN_PERI_ONEWIRE = 31
} PDNCONA_MODE, APMCUSYS_PDNCONA0_MODE;
#if 0
typedef enum
{
    PDN_PERI_DMA = 0,
    PDN_PERI_USB = 1,
    PDN_PERI_RESERVED0 = 2,
    PDN_PERI_SPI = 3,
    PDN_PERI_GPT = 4,
    PDN_PERI_UART0 = 5,
    PDN_PERI_UART1 = 6,
    PDN_PERI_UART2 = 7,
    PDN_PERI_UART3 = 8,
    PDN_PERI_UART4 = 9,
    PDN_PERI_PWM = 10,
    PDN_PERI_PWM0CLK = 11,
    PDN_PERI_PWM1CLK = 12,
    PDN_PERI_PWM2CLK = 13,
    PDN_PERI_MSDC0 = 14,
    PDN_PERI_MSDC1 = 15,
    PDN_PERI_MSDC2 = 16,
    PDN_PERI_NFI = 17,
    PDN_PERI_IRDA = 18,
    PDN_PERI_I2C = 19,
    PDN_PERI_AUXADC = 20,
    PDN_PERI_TOUCH = 21,
    PDN_PERI_SYSROM = 22,
    PDN_PERI_KEYPAD = 23
} PDNCONA_MODE;
#endif
// PDNCONB
// PDNSETB
// PDNCLRB
typedef enum
{
    PDN_MM_GMC = 0,
    PDN_MM_G2D = 1,
    PDN_MM_GCMQ = 2,
    PDN_MM_RESERVED0 = 3,
    PDN_MM_IMAGEDMA = 4,
    PDN_MM_IMAGEPROCESSOR = 5,
    PDN_MM_JPEG = 6,
    PDN_MM_DCT = 7,
    PDN_MM_ISP = 8,
    PDN_MM_PRZ = 9,
    PDN_MM_CRZ = 10,
    PDN_MM_DRZ = 11,
    PDN_MM_SPI = 12,
    PDN_MM_ASM = 13,
    PDN_MM_I2S = 14,
    PDN_MM_RESIZE_LB = 15,
    PDN_MM_LCD = 16,
    PDN_MM_DPI = 17,
    PDN_MM_VFE = 18,
    PDN_MM_AFE = 19,
    PDN_MM_BLS = 20
} PDNCONB_MODE;

/*******************************************************************************
 * Function declaration
 *******************************************************************************/

extern void PDN_Power_CONA_DOWN (PDNCONA_MODE mode, BOOL enable);


#endif
