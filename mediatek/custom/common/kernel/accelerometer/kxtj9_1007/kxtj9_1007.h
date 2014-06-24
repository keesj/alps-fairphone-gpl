/* linux/drivers/hwmon/kxtj9_1007.c
 *
 * (C) Copyright 2008 
 * MediaTek <www.mediatek.com>
 *
 * KXTJ9_1007 driver for MT8389
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA  KXTIK
 */
#ifndef KXTJ9_1007_H
#define KXTJ9_1007_H
	 
#include <linux/ioctl.h>
	 
#define KXTJ9_1007_I2C_SLAVE_ADDR		0x1E
	 
 /* KXTJ9_1007 Register Map  (Please refer to KXTJ9_1007 Specifications) */
#define KXTJ9_1007_REG_DEVID			0x0F
#define	KXTJ9_1007_REG_BW_RATE			0x21
#define KXTJ9_1007_REG_POWER_CTL		0x1B
#define KXTJ9_1007_REG_CTL_REG3		0x1D
#define KXTJ9_1007_DCST_RESP			0x0C
#define KXTJ9_1007_REG_DATA_FORMAT		0x1B
#define KXTJ9_1007_REG_DATA_RESOLUTION		0x1B
#define KXTJ9_1007_RANGE_DATA_RESOLUTION_MASK	0x40
#define KXTJ9_1007_REG_DATAX0			0x06	 
#define KXTJ9_1007_FIXED_DEVID			0x09	 
#define KXTJ9_1007_BW_200HZ				0x05
#define KXTJ9_1007_BW_100HZ				0x04
#define KXTJ9_1007_BW_50HZ				0x03	 
#define KXTJ9_1007_MEASURE_MODE		0x80		 
#define KXTJ9_1007_RANGE_MASK		0x18
#define KXTJ9_1007_RANGE_2G			0x00
#define KXTJ9_1007_RANGE_4G			0x08
#define KXTJ9_1007_RANGE_8G			0x10
#define KXTJ9_1007_REG_INT_ENABLE	0x1E

#define KXTJ9_1007_SELF_TEST           0x10
	 	 
	 
#define KXTJ9_1007_SUCCESS						0
#define KXTJ9_1007_ERR_I2C						-1
#define KXTJ9_1007_ERR_STATUS					-3
#define KXTJ9_1007_ERR_SETUP_FAILURE				-4
#define KXTJ9_1007_ERR_GETGSENSORDATA			-5
#define KXTJ9_1007_ERR_IDENTIFICATION			-6
	 
	 
	 
#define KXTJ9_1007_BUFSIZE				256
	 
#endif

