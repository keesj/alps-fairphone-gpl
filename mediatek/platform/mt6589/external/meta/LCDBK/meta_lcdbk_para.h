/*******************************************************************************
 *
 * Filename:
 * ---------
 *   META_LCDBK_PARA.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *    header file of main function
 *
 * Author:
 * -------
 *   Hua Zhang(MBJ07046) 09/11/2008
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * Dec 15 2008 mbj07046
 * [DUMA00105307] check in PWM, headset, Backlight
 * 
 *
 *******************************************************************************/


#ifndef __META_LCDBK_PARA_H__
#define __META_LCDBK_PARA_H__

 

typedef struct  {
	//unsigned char		lcd_light_level;
	int		lcd_light_level;
}LCDLevel_REQ;

typedef struct  {
	BOOL 				status;
}LCDLevel_CNF;


/*implement this function in META_LCDBK.LIB  */
BOOL			Meta_LCDBK_Init();
LCDLevel_CNF	Meta_LCDBK_OP(LCDLevel_REQ dwBrightness);
BOOL			Meta_LCDBK_Deinit();




#endif

