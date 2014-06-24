/*****************************************************************************
 *
 * Filename:
 * ---------
 *   boot_mode.c
 *
 * Project:
 * --------
 *   YuSu 
 *
 * Description:
 * ------------
 *   This file implements MT6575 boot mode.
 *
 * Author:
 * -------
 *   CC Hwang (mtk00702)
 *   Hong-Rong Hsu (mtk02678)
 *
 ****************************************************************************/
#include <common.h>
#include <command.h>
#include <asm/arch/mt65xx.h>
#include <asm/arch/mt65xx_typedefs.h>
#include <asm/arch/boot_mode.h>
#include <asm/mach-types.h>
#include <asm/errno.h>
#include <asm/byteorder.h>



// global variable for specifying boot mode (default = NORMAL)
BOOTMODE g_boot_mode = NORMAL_BOOT;

BOOL meta_mode_check(void)
{	
	//printf(" > check meta mode to bypass power key\n");
	if(g_boot_mode == META_BOOT || g_boot_mode == ADVMETA_BOOT)
	{	
	  return TRUE;
	}
	else
	{	return FALSE;
	}
}


// check the boot mode : (1) meta mode or (2) recovery mode ...
void boot_mode_select(void)
{	
    #ifdef CFG_META_MODE
    if (meta_detection())
    {	
      return;
    }
    #endif   
    #ifdef CFG_FACTORY_MODE
    if (factory_detection())
    {	
      return;
    }
    #endif    
    #ifdef CFG_RECOVERY_MODE
    if(recovery_detection())
    {	
      //**************************************
  		//* CHECK IMAGE
  		//**************************************
  		if(DRV_Reg32(0x40002300)==0xE92D4800)
  		{	
  		  printf(" > do recovery_check\n");
  			//jump(0x40002300); 
  		}
  		else
  		{	
  		  printf(" > bypass recovery_check\n");
  		}
    	return;
    }
    #endif   
}

unsigned int get_chip_sw_ver_code(void)
{  
    return DRV_Reg32(APSW_VER);
}

CHIP_SW_VER mt_get_chip_sw_ver(void)
{
    return (CHIP_SW_VER)get_chip_sw_ver_code();
}
