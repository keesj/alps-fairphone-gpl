/*******************************************************************************
 *
 * Filename:
 * ---------
 *   Meta_ADC_Para.h
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
 *   MTK80198(Chunlei Wang)
 *
 * 
 *
 *******************************************************************************/


#ifndef __META_AUXADC_PARA_H__
#define __META_AUXADC_PARA_H__

#include "FT_Public.h"
 
typedef struct{
	FT_H	    	header;  //module do not need care it
	unsigned char	dwChannel;	// channel 0-8
	unsigned short	dwCount;	// Detect number	
}AUXADC_REQ;

typedef struct{
	FT_H	    header;  //module do not need care it
	//DWORD			dwData;
	int			dwData;
	BOOL			ADCStatus;
	unsigned char	status;
}AUXADC_CNF;


/* please implement this function   */
BOOL 			Meta_AUXADC_Init(void);
void Meta_AUXADC_OP(AUXADC_REQ *req, char *peer_buff, unsigned short peer_len); 
BOOL 			Meta_AUXADC_Deinit(void);


#endif
