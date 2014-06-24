/*
 * (C) Copyright 2011
 * MediaTek <www.mediatek.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "sec_platform.h"
#include "sec_region.h"
#include "sec.h"

/******************************************************************************
 * MODULE
 ******************************************************************************/
#define MOD                         "SEC_REGION"

/******************************************************************************
 * DEBUG
 ******************************************************************************/
#define SMSG                        dbg_print

/******************************************************************************
 *  EXTERNAL VARIABLES
 ******************************************************************************/

/******************************************************************************
 *  SECURITY REGION CHECK
 ******************************************************************************/
void sec_region_check (U32 addr, U32 len)
{
    U32 ret = SEC_OK;   
    U32 tmp = addr + len;

    /* check if it does access AHB/APB register */
    if ((IO_PHYS != (addr & REGION_MASK)) || (IO_PHYS != (tmp & REGION_MASK))) {
        SMSG("[%s] 0x%x Not AHB/APB Address\n", MOD, addr);   
        ASSERT(0);
    }

    if (len >= REGION_BANK) {
        SMSG("[%s] Overflow\n",MOD);
        ASSERT(0);
    }    

    /* check platform security region */
    if (SEC_OK != (ret = seclib_region_check(addr,len))) {
        SMSG("[%s] ERR '0x%x' ADDR: 0x%x, LEN: %d\n", MOD, ret, addr, len);
        ASSERT(0);
    }
}

/******************************************************************************
 *  DA REGION CHECK
 ******************************************************************************/
U32 da_region_check (U32 addr, U32 len)
{
    U32 ret = SEC_OK;

    if(DA_DOWNLOAD_LOC != addr)
    {
        ret = ERR_DA_INVALID_LOCATION;
        goto _exit;
    }

    if(DA_DOWNLOAD_MAX_SZ < len)
    {
        ret = ERR_DA_INVALID_LENGTH;
        goto _exit;        
    }

_exit:

    return ret;
}
