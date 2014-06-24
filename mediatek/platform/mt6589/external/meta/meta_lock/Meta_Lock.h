/*******************************************************************************
 *
 * Filename:
 * ---------
 *   Meta_Lock.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *    header file of main function
 *
 * Author:
 * -------
 *   Ning Zhang (mtk80860) 08/17/2010
 *
 *******************************************************************************/


#ifndef __META_LOCK_H__
#define __META_LOCK_H__


#define META_LOCK_MAGIC_NUM		0x58D12AB4
#define END_BLOCK 23*128*1024
#define BLOCK_SIZE 128*1024
#define LOGO_PARTITION 10

#ifdef __cplusplus
extern "C"
{
#endif
    
    /********************************************************************************
    //FUNCTION:
    //		META_Lock_Init
    //DESCRIPTION:
    //		this function is called to initial the meta_Lock module.
    //
    //PARAMETERS:
    //		None
    //
    //RETURN VALUE:
    //		TRUE: is scuccess, otherwise is fail
    //
    //DEPENDENCY:
    //		None
    //
    //GLOBALS AFFECTED
    //		None
    ********************************************************************************/
//    bool 					META_Lock_Init(void);


    /********************************************************************************
    //FUNCTION:
    //		META_Lock_Deinit
    //DESCRIPTION:
    //		this function is called to de-initial the meta_Lock module.
    //
    //PARAMETERS:
    //		None
    //
    //RETURN VALUE:
    //		TRUE: is scuccess, otherwise is fail
    //
    //DEPENDENCY:
    //		META_Editor_Init must have been called
    //
    //GLOBALS AFFECTED
    //		None
    ********************************************************************************/
//    bool 					META_Lock_Deinit(void);

    /********************************************************************************
    //FUNCTION:
    //		META_Lock_OP
    //DESCRIPTION:
    //		this function is called to write a magic number into Nand Flash.
    //
    //PARAMETERS:
    //		req:
    //
    //RETURN VALUE:
    //		TRUE: is scuccess, otherwise is fail. 
    //
    //DEPENDENCY:
    //		META_Lock_Init must have been called
    //
    //GLOBALS AFFECTED
    ********************************************************************************/
    unsigned char					META_Lock_OP(void);
    
    
    static int META_Lock_WriteFlash(unsigned int iMagicNum);

#ifdef __cplusplus
}
#endif
#endif
