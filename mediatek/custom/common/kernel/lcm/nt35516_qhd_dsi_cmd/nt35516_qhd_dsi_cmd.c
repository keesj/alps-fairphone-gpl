/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC). 
*
*****************************************************************************/ 


#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/kernel.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
	#include <string.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (540)
#define FRAME_HEIGHT (960)
#define LCM_DSI_CMD_MODE

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

//static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0x00   // END OF REGISTERS MARKER


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------
#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)									lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)				lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg											lcm_util.dsi_read_reg()
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)     

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

struct LCM_setting_table {
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {
		
        unsigned cmd;
        cmd = table[i].cmd;
		
        switch (cmd) {
			
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;
				
            case REGFLAG_END_OF_TABLE :
                break;
				
            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
       	}
    }
	
}

static struct LCM_setting_table lcm_sleep_out_setting[] = {
    // Sleep Out
	{0x11, 1, {0x00}},
    {REGFLAG_DELAY, 120, {}},

    // Display ON
	{0x29, 1, {0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_sleep_in_setting[] = {
	// Display off sequence
	{0x28, 1, {0x00}},
	{REGFLAG_DELAY, 120, {}},

       // Sleep Mode On
	{0x10, 1, {0x00}},

	{REGFLAG_DELAY, 50, {}},
	{0x4F, 1, {0x01}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

#if defined(LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
#else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE;
#endif
	
		// DSI
		/* Command mode setting */
		params->dsi.LANE_NUM				= LCM_TWO_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		params->dsi.pll_select=1;	//0: MIPI_PLL; 1: LVDS_PLL   //mtk 20130508
		params->dsi.PLL_CLOCK = LCM_DSI_6589_PLL_CLOCK_221;		// fref=26MHz, fvco=fref*(fbk_div+1)*2/(div1_real*div2_real)		

											//if not config this para, must config other 7 or 3 paras to gen. PLL

}

static void init_lcm_registers(void)
{
	

unsigned int data_array[16];

	data_array[0]=0x00053902;
	data_array[1]=0x2555AAFF;
	data_array[2]=0x00000001;
	dsi_set_cmdq(&data_array, 3, 1);

data_array[0]=0x00243902;
	data_array[1]=0x4A0000F2;
	data_array[2]=0x0000A80A;
	data_array[3]=0x00000000;
	data_array[4]=0x00000000;
	data_array[5]=0x000B0000;
	data_array[6]=0x00000000;
	data_array[7]=0x00000000;
	data_array[8]=0x51014000;
	data_array[9]=0x01000100;

	dsi_set_cmdq(&data_array, 10, 1);	

	data_array[0]=0x00053902;
	data_array[1]=0x070302F3;
	data_array[2]=0x0DD18845;
	dsi_set_cmdq(&data_array, 3, 1);
	
	


	//*************Enable CMD2 Page0  *******************//

	data_array[0]=0x00063902;
	data_array[1]=0x52AA55F0;
	data_array[2]=0x00000008;
	dsi_set_cmdq(&data_array, 3, 1);	

   /* data_array[0]=0xCCB11500;//Data Type 
	dsi_set_cmdq(&data_array, 1, 1);

    data_array[0]=0x00043902;;//Data Type 
	data_array[1]=0x730373BB;
	dsi_set_cmdq(&data_array, 2, 1);

    //cabc control/////
    
	data_array[0] = 0x00511500;
	dsi_set_cmdq(&data_array, 1, 1);

	data_array[0] = 0x24531500;
	dsi_set_cmdq(&data_array, 1, 1);

	data_array[0] = 0x00551500;	// SET CABC UI MODE
	dsi_set_cmdq(&data_array, 1, 1);*/

	data_array[0]=0x00043902;
	data_array[1]=0x0000ECB1;

	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x020201B8;
	data_array[1]=0x00000002;
	dsi_set_cmdq(&data_array, 2, 1);


	data_array[0]=0x00073902;
	data_array[1]=0x0D0663C9;
	data_array[2]=0x0000171A;
	
	dsi_set_cmdq(&data_array, 3, 1);

//*************Enable CMD2 Page1  *******************//

	data_array[0]=0x00063902;
	data_array[1]=0x52AA55F0;
	data_array[2]=0x00000108;
	dsi_set_cmdq(&data_array, 3, 1);	

	data_array[0]=0x00043902;
	data_array[1]=0x050505B0;
	dsi_set_cmdq(&data_array, 2, 1);

data_array[0]=0x00043902;
	data_array[1]=0x050505B1;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x010101B2;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x0E0E0EB3;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x080808B4;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x444444B6;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x343434B7;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x101010B8;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x262626B9;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x343434BA;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x008000BC;
	dsi_set_cmdq(&data_array, 2, 1);

	data_array[0]=0x00043902;
	data_array[1]=0x008000BD;
	dsi_set_cmdq(&data_array, 2, 1);

	//data_array[0]=0x51BE1500;//Data Type 
	//dsi_set_cmdq(&data_array, 1, 1);

data_array[0]=0x00023902;
	data_array[1]=0x000075BE;
	dsi_set_cmdq(&data_array, 2, 1);

data_array[0]=0x00033902;
	data_array[1]=0x000004C0;
	dsi_set_cmdq(&data_array, 2, 1);

data_array[0]=0x00023902;
	data_array[1]=0x000000CA;
	dsi_set_cmdq(&data_array, 2, 1);
	//GAMMA SETTING start
data_array[0]=0x00053902;
	data_array[1]=0x0D100AD0;
	data_array[1]=0x0000000F;
	dsi_set_cmdq(&data_array, 3, 1);
	
	data_array[0]=0x00113902;
	data_array[1]=0x007000D1;
	data_array[2]=0x009F0080;
	data_array[3]=0x01D900BE;
	data_array[4]=0x01210107;
	data_array[5]=0x00000045;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x016601D2;
	data_array[2]=0x02C4019A;
	data_array[3]=0x02420208;
	data_array[4]=0x027B0244;
	data_array[5]=0x000000BC;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x03E702D3;
	data_array[2]=0x033C031B;
	data_array[3]=0x037E0366;
	data_array[4]=0x03B1039F;
	data_array[5]=0x000000CF;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x03F303D4;
	data_array[2]=0x000000FF;
	dsi_set_cmdq(&data_array, 3, 1);
	//GAMMA SETTING end

	//GAMMA SETTING start
	data_array[0]=0x00113902;
	data_array[1]=0x007000D5;
	data_array[2]=0x009F0080;
	data_array[3]=0x01D900BE;
	data_array[4]=0x01210107;
	data_array[5]=0x00000045;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x016601D6;
	data_array[2]=0x02C4019A;
	data_array[3]=0x02420208;
	data_array[4]=0x027B0244;
	data_array[5]=0x000000BC;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x03E702D7;
	data_array[2]=0x033C031B;
	data_array[3]=0x037E0366;
	data_array[4]=0x03B1039F;
	data_array[5]=0x000000CF;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x03F303D8;
	data_array[2]=0x000000FF;
	dsi_set_cmdq(&data_array, 3, 1);

	//GAMMA SETTING start
	
	data_array[0]=0x00113902;
	data_array[1]=0x007000D9;
	data_array[2]=0x009F0080;
	data_array[3]=0x01D900BE;
	data_array[4]=0x01210107;
	data_array[5]=0x00000045;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x016601DD;
	data_array[2]=0x02C4019A;
	data_array[3]=0x02420208;
	data_array[4]=0x027B0244;
	data_array[5]=0x000000BC;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x03E702DE;
	data_array[2]=0x033C031B;
	data_array[3]=0x037E0366;
	data_array[4]=0x03B1039F;
	data_array[5]=0x000000CF;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x03F303DF;
	data_array[2]=0x000000FF;
	dsi_set_cmdq(&data_array, 3, 1);

	//GAMMA SETTING start
	
	
	data_array[0]=0x00113902;
	data_array[1]=0x007000E0;
	data_array[2]=0x009F0080;
	data_array[3]=0x01D900BE;
	data_array[4]=0x01210107;
	data_array[5]=0x00000045;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x016601E1;
	data_array[2]=0x02C4019A;
	data_array[3]=0x02420208;
	data_array[4]=0x027B0244;
	data_array[5]=0x000000BC;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x03E702E2;
	data_array[2]=0x033C031B;
	data_array[3]=0x037E0366;
	data_array[4]=0x03B1039F;
	data_array[5]=0x000000CF;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x03F303E3;
	data_array[2]=0x000000FF;
	dsi_set_cmdq(&data_array, 3, 1);
	//GAMMA SETTING end

	//GAMMA SETTING start
	
	
	data_array[0]=0x00113902;
	data_array[1]=0x007000E4;
	data_array[2]=0x009F0080;
	data_array[3]=0x01D900BE;
	data_array[4]=0x01210107;
	data_array[5]=0x00000045;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x016601E5;
	data_array[2]=0x02C4019A;
	data_array[3]=0x02420208;
	data_array[4]=0x027B0244;
	data_array[5]=0x000000BC;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x03E702E6;
	data_array[2]=0x033C031B;
	data_array[3]=0x037E0366;
	data_array[4]=0x03B1039F;
	data_array[5]=0x000000CF;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x03F303E7;
	data_array[2]=0x000000FF;
	dsi_set_cmdq(&data_array, 3, 1);
	//GAMMA SETTING end

	//GAMMA SETTING start
	
	
	data_array[0]=0x00113902;
	data_array[1]=0x007000E8;
	data_array[2]=0x009F0080;
	data_array[3]=0x01D900BE;
	data_array[4]=0x01210107;
	data_array[5]=0x00000045;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x016601E9;
	data_array[2]=0x02C4019A;
	data_array[3]=0x02420208;
	data_array[4]=0x027B0244;
	data_array[5]=0x000000BC;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00113902;
	data_array[1]=0x03E702EA;
	data_array[2]=0x033C031B;
	data_array[3]=0x037E0366;
	data_array[4]=0x03B1039F;
	data_array[5]=0x000000CF;
	dsi_set_cmdq(&data_array, 6, 1);

	data_array[0]=0x00053902;
	data_array[1]=0x03F303EB;
	data_array[2]=0x000000FF;
	dsi_set_cmdq(&data_array, 3, 1);
	//GAMMA SETTING end
///////////////////////////////////////////////////////////////////////////
	//data_array[0] = 0x00351500;// TE ON
	//dsi_set_cmdq(&data_array, 1, 1);

	data_array[0]=0x773A1500;//Data Type 
	dsi_set_cmdq(&data_array, 1, 1);
	data_array[0]=0x00053902;
	data_array[1]=0x0200002A;
	data_array[2]=0x0000001B;
	dsi_set_cmdq(&data_array, 3, 1);
	data_array[0]=0x00053902;
	data_array[1]=0x0300002B;
	data_array[2]=0x000000BF;
	dsi_set_cmdq(&data_array, 3, 1);

	data_array[0] = 0x00110500;		// Sleep Out
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(120);

	data_array[0] = 0x00290500;		// Display On
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(40);

}

static unsigned int lcm_check_status(void)
{
	unsigned char buffer[2];
	int   array[4];
//	unsigned int i = 0;
	
	array[0] = 0x00013700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);
#if 0
	while(i < 10){
		read_reg_v2(0x0A, buffer, 1);
#ifdef BUILD_LK
		printf("Check LCM Status: 0x%08x\n", buffer[0]);
#else
		printk("Check LCM Status: 0x%08x\n", buffer[0]);
#endif
		if(buffer[0] != 0x9C)
			init_lcm_registers();
		else
			break;
		i++;
	}
#else
	read_reg_v2(0x0A, buffer, 1);
#ifdef BUILD_LK
	printf("Check LCM Status: 0x%08x\n", buffer[0]);
#else
	printk("Check LCM Status: 0x%08x\n", buffer[0]);
#endif
#endif
	return 0;
}

static void lcm_init(void)
{
   SET_RESET_PIN(0);
    MDELAY(10);    //20->10
	SET_RESET_PIN(1);
    MDELAY(10);     //20->10
	SET_RESET_PIN(0);
    MDELAY(50);     //20->50
    SET_RESET_PIN(1);
    MDELAY(30);     //20->30
    lcm_check_status();
    init_lcm_registers();
}


static void lcm_suspend(void)
{

unsigned int data_array[16];

   SET_RESET_PIN(0);
   MDELAY(20);
   SET_RESET_PIN(0);
   MDELAY(20);
   SET_RESET_PIN(1);
   MDELAY(20);

    data_array[0] = 0x00281502; // Display Off
    dsi_set_cmdq(data_array, 1, 1);
    MDELAY(40);     //ghong_dminchao  100->40
    data_array[0] = 0x00101502; // Display Off   add by ghong_dminchao  2013.04.26
    dsi_set_cmdq(data_array, 1, 1);
    MDELAY(120);        //ghong_dminchao  100->120



//rm by ghong_dminchao 2013.04.26
/*
	MDELAY(100);
//{0xFF, 4,  {0xAA, 0x55, 0x25, 0x01}},
    data_array[0]=0x00053902;
    data_array[1]=0x2555AAFF;
    data_array[2]=0x00000001;
    dsi_set_cmdq(&data_array, 3, 0);
//	{0xF3, 7,  {0x02, 0x00, 0x00, 0x45, 0x88, 0xD1, 0x0C}},
    data_array[0]=0x00083902;
    data_array[1]=0x000002F3;
    data_array[2]=0x0CD18845;
    dsi_set_cmdq(&data_array, 3, 0);
	
   //  {0xF4, 1,  {0x58}},
  data_array[0]=0x58F41502;
  dsi_set_cmdq(&data_array, 1, 0);

	//{0xF8, 4,  {0x08, 0x03, 0x00, 0x00}},
    data_array[0]=0x00053902;
    data_array[1]=0x000308F8;
    data_array[2]=0x00000000;
    dsi_set_cmdq(&data_array, 3, 0);

	//{0xFA, 20, {0x80, 0x80, 0x20, 0x6F, 0x00, 0x0F, 0x00, 0x00, 0xD0, 0x0F, 0x00, 0x00, 0x03, 0x21, 0x14, 0x20, 0xA0, 0x00, 0x00, 0x00}},
data_array[0]=0x00153902;
data_array[1]=0x208080FA;
data_array[2]=0x000F006F;
data_array[3]=0x000FD000;
data_array[4]=0x14210300;
data_array[5]=0x0000A020;
data_array[6]=0x00000000;
dsi_set_cmdq(&data_array, 7, 0);
//	{0xFC, 20, {0x00, 0x20, 0x25, 0x13, 0x17, 0x77, 0x00, 0x00, 0x11, 0x11, 0x0F, 0x03, 0x01, 0x55, 0x67, 0x09, 0x00, 0x00, 0x00, 0x05}}, // ORG
	//{0xFC, 23, {0x00, 0x20, 0x25, 0x0A, 0x17, 0x77, 0x00, 0x00, 0x11, 0x11, 0x0F, 0x03, 0x01, 0x55, 0x67, 0x09, 0x00, 0x00, 0x00, 0x05, 0x40, 0x00, 0x0F}}, // NEW
data_array[0]=0x00183902;
data_array[1]=0x252000FC;
data_array[2]=0x0077170A;
data_array[3]=0x0F111100;
data_array[4]=0x67550103;
data_array[5]=0x00000009;
data_array[6]=0x0F004005;
dsi_set_cmdq(&data_array, 7, 0);
//-------------------------------------
// CMD2, Page 0
//-------------------------------------
	//{0xF0, 5,  {0x55, 0xAA, 0x52, 0x08, 0x00}},
data_array[0]=0x00063902;
data_array[1]=0x52AA55F0;
data_array[2]=0x00000008;
dsi_set_cmdq(&data_array, 3, 0);
	//{0xBB, 3,  {0x11, 0x01, 0x11}},
data_array[0]=0x00043902;
data_array[1]=0x110111BB;
dsi_set_cmdq(&data_array, 2, 0);
//	{0xBD, 5,  {0x01, 0x41, 0x08, 0x40, 0x03}}, // ORG
	//{0xBD, 5,  {0x01, 0xFF, 0x08, 0x40, 0x03}}, // NEW
data_array[0]=0x00063902;
data_array[1]=0x08FF01BD;
data_array[2]=0x00000340;
dsi_set_cmdq(&data_array, 3, 0);
//-------------------------------------
// CMD2, Page 1
//------------------------------------
	//{0xF0, 5,  {0x55, 0xAA, 0x52, 0x08, 0x01}},
data_array[0]=0x00063902;
data_array[1]=0x52AA55F0;
data_array[2]=0x00000108;
dsi_set_cmdq(&data_array, 3, 0);

	//{0xB3, 1,  {0x00}}, // add
data_array[0]=0x00B31502;
dsi_set_cmdq(&data_array, 1, 0);
	//{0xB6, 1,  {0x11}},
data_array[0]=0x11B61502;
dsi_set_cmdq(&data_array, 1, 0);
	//{0xB7, 1,  {0x11}},
data_array[0]=0x11B71502;
dsi_set_cmdq(&data_array, 1, 0);
	//{0xB8, 1,  {0x11}},
data_array[0]=0x11B81502;
dsi_set_cmdq(&data_array, 2, 0);
//	{0xB9, 1,  {0x12}},
	//{0xBA, 1,  {0x11}},
   data_array[0]=0x11BA1502;
   dsi_set_cmdq(&data_array, 1, 0);
   MDELAY(120);
	//{REGFLAG_DELAY, 120, {}},

*/
}


static void lcm_resume(void)
{
	unsigned int data_array[16];
    
	SET_RESET_PIN(1);
        MDELAY(20);
	SET_RESET_PIN(0);
        MDELAY(20);
        SET_RESET_PIN(1);
        MDELAY(20);
        init_lcm_registers();     
	data_array[0]=0x00110500;
	dsi_set_cmdq(data_array, 1, 1);
	MDELAY(120);	   //150->120
	data_array[0]=0x00290500;
	dsi_set_cmdq(data_array, 1, 1);
        MDELAY(120);

}


static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(data_array, 3, 1);

	data_array[0]= 0x002c3909;
	dsi_set_cmdq(data_array, 1, 0);
}
static unsigned int lcm_compare_id(void)
{

	int   array[4];
	char  buffer[3];
	char  id0=0;
	char  id1=0;
	char  id2=0;


	SET_RESET_PIN(0);
	MDELAY(200);
	SET_RESET_PIN(1);
	MDELAY(200);
		
	array[0] = 0x00083700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0x04,buffer, 3);
	
	id0 = buffer[0]; //should be 0x00
	id1 = buffer[1];//should be 0x80
	id2 = buffer[2];//should be 0x00
	
	return 0;


}

#if 0
static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_LK
		char  buffer[3];
		int   array[4];
#if 0
        if(lcm_esd_test)
        {
            lcm_esd_test = FALSE;
            return TRUE;
        }
#endif
        /// please notice: the max return packet size is 1
        /// if you want to change it, you can refer to the following marked code
        /// but read_reg currently only support read no more than 4 bytes....
        /// if you need to read more, please let BinHan knows.
        /*
                unsigned int data_array[16];
                unsigned int max_return_size = 1;
                
                data_array[0]= 0x00003700 | (max_return_size << 16);    
                
                dsi_set_cmdq(&data_array, 1, 1);
        */
		array[0] = 0x00043700;// read id return two byte,version and id
		dsi_set_cmdq(array, 1, 1);

        read_reg_v2(0x3A, buffer, 1);
		if(buffer[0]==0x77)
        {
            return FALSE;
        }
        else
        {            
            return TRUE;
        }
#endif
}

static unsigned int lcm_esd_recover(void)
{
//    unsigned char para = 0;

	lcm_init();
	lcm_resume();

    return TRUE;
}
#endif
#if 0
static unsigned int lcm_check_status(void)
{
	unsigned char buffer[2];

	read_reg_v2(0x0A, buffer, 2);
#ifdef BUILD_LK
	printf("Check LCM Status: 0x%08x\n", buffer[0]);
#else
	printk("Check LCM Status: 0x%08x\n", buffer[0]);
#endif
	return 0;
}
#endif
LCM_DRIVER nt35516_qhd_dsi_cmd_lcm_drv = 
{
    .name			= "nt35516_qhd_dsi_cmd",
	.set_util_funcs = lcm_set_util_funcs,
	.compare_id     = lcm_compare_id,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
#if defined(LCM_DSI_CMD_MODE)
    .update         = lcm_update,
//    .esd_check      = lcm_esd_check,
//    .esd_recover    = lcm_esd_recover,
#endif
		.check_status = lcm_check_status

    };

