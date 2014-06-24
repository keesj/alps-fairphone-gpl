/* for storage operations */
#include "sec_platform.h"

/* for crypto operations */
#include "cust_sec_ctrl.h"
#include "sec_boot.h"
#include "sec_error.h"
#include "sec.h"
#include "KEY_IMAGE_AUTH.h"
#include "sec_secroimg.h"

/* to get current boot device type */
//#include "cust.h"

/**************************************************************************
*  MACRO
**************************************************************************/ 
#define MOD                             "LIB"

/******************************************************************************
 * DEBUG
 ******************************************************************************/
#define SEC_DEBUG                       (FALSE)
#define SMSG                            print
#if SEC_DEBUG
#define DMSG                            print
#else
#define DMSG 
#endif

/**************************************************************************
 *  GLOBAL VARIABLES
 **************************************************************************/


/**************************************************************************
 *  LOCAL VARIABLES
 **************************************************************************/

/**************************************************************************
 *  EXTERNAL VARIABLES
 **************************************************************************/
extern BOOL bDumpPartInfo;
extern AND_SECROIMG_T               *secroimg;

/**************************************************************************
 *  EXTERNAL FUNCTIONS
 **************************************************************************/

/**************************************************************************
 *  [SECURE BOOT CHECK]
 **************************************************************************/
U32 sec_boot_img_check(BOOL sw_sboot_support, unsigned int boot_chk_img, U8* img_name)
{
    bDumpPartInfo = TRUE;
    U32 ret = SEC_OK;
    
    if (TRUE == sw_sboot_support)
    {
        if (SW_SEC_BOOT_CHECK_IMAGE == boot_chk_img)
        {
            if (SEC_OK != (ret = seclib_image_check (img_name,TRUE)))
            {
                return ret;
            }
        }
    }
    else
    {
        if (SEC_OK != (ret = seclib_image_check (img_name,TRUE)))
        {
            return ret;
        }
    }
    
    return ret;
}


 
void sec_boot_check (void)
{
    //if(CFG_STORAGE_DEVICE == NAND)
    {
    
#if SEC_ENV_ENABLE

        U32 g_verify_time_begin = get_timer (0);;
        U32 g_verify_time_end;
        U32 ret = 0;
        BOOL sw_secure_boot_support = FALSE;
        
        /* --------------------- */
        /* init image auth key   */
        /* --------------------- */
        if (SEC_OK != img_auth_init()) 
        {
            SMSG("[%s] IMAGE Auth Key Init Fail\n",MOD);
            ret = ERR_IMG_INIT_KEY_FAIL;
            goto _fail;
        }

        if ((secroimg != NULL)&&(SW_SUPPORT_ENABLE == 
            (secroimg->m_andro.sw_sec_boot.flashtool_unlock_support)))
        {
            sw_secure_boot_support = TRUE;
        }
        else
        {
        if(FALSE == seclib_sec_boot_enabled(TRUE))
        {
            SMSG("[%s] Don't check\n",MOD);
            return ;
        }
        }

        if (SEC_OK != sec_boot_img_check(sw_secure_boot_support, 
                secroimg->m_andro.sw_sec_boot.boot_chk_2nd_loader, SBOOT_PART_UBOOT))
        {
            goto _fail;
        }

        
        if (SEC_OK != sec_boot_img_check(sw_secure_boot_support, 
                       secroimg->m_andro.sw_sec_boot.boot_chk_logo, SBOOT_PART_LOGO))
        {
            goto _fail;
        }
        
#if  VERIFY_PART_CUST
        if (SEC_OK != sec_boot_img_check(TRUE, SW_SEC_BOOT_CHECK_IMAGE, VERIFY_PART_CUST_NAME))
        {
            goto _fail;
        }
#endif

        /* calculate verification time */
        g_verify_time_end = get_timer (g_verify_time_begin);
        SMSG ("\n[%s] Consume (%d) ms\n", MOD, g_verify_time_end);
        return ;

_fail :
        SMSG ("[%s] Fail (0x%x)\n",MOD,ret);
        ASSERT(0);

_brom_recovery_check :
        SMSG ("[%s] Fail (0x%x)\n",MOD,ret);
        sec_util_brom_download_recovery_check(); 
        

#endif // SEC_ENV_ENABLE

    } // if(CFG_STORAGE_DEVICE == NAND)

}
