/******************************************************************************
*
* Filename:
* ---------
*     buffer.h
*/
#ifndef BUFFER_ADDR_H
#define BUFFER_ADDR_H

#include "platform.h"

#define SEC_SECRO_BUFFER_START      (SEC_REGION_ADDR)
#define SEC_SECRO_BUFFER_LENGTH     (0x100000)
#define SEC_WORKING_BUFFER_START    (SEC_REGION_ADDR + 0x100000)
#define SEC_WORKING_BUFFER_LENGTH   (0x100000)
#define SEC_UTIL_BUFFER_START       (SEC_REGION_ADDR + 0x200000)
#define SEC_UTIL_BUFFER_LENGTH      (0x200000)
/*SecLib.a use DRAM*/
#define SEC_LIB_HEAP_START          (SEC_REGION_ADDR + 0x400000)
#define SEC_LIB_HEAP_LENGTH         (0x100000)
/*For v3 verify check buffer */
#define SEC_IMG_BUFFER_START        (SEC_REGION_ADDR + 0x500000)
#define SEC_IMG_BUFFER_LENGTH       (0x100000)
#define SEC_CHUNK_BUFFER_START      (SEC_REGION_ADDR + 0x600000)
#define SEC_CHUNK_BUFFER_LENGTH     (0x200000)

/************************************/
/*preloader download DA use DRAM*/
#define DA_RAM_ADDR                 (CFG_DA_RAM_ADDR)
#define DA_RAM_LENGTH               (0x30000)
/*preloader validate DA use DRAM*/
#define DA_RAM_RELOCATE_ADDR        (CFG_DA_RAM_ADDR + DA_RAM_LENGTH)
#define DA_RAM_RELOCATE_LENGTH      (DA_RAM_LENGTH)

#endif



