#define LOG_TAG "CAMDRV_HWUTILS"
//
#include <utils/Errors.h>
#include <cutils/log.h>
#include <sys/mman.h>
#include "m4u_lib.h"
#include <linux/cache.h>
//
#include "hwutils.h"
////////////////////////////////////////////////////////////////////////////////////
// test add for only flush cache without create instance of imem_drv
//-----------------------------------------------------------------------------
MINT32 globalcacheFlushAll(void)
{
    MTKM4UDrv*  _mpM4UDrv=NULL;
	///////////////////////////////////////////////
	///declare m4u driver
	_mpM4UDrv = new MTKM4UDrv();
	///////////////////////////////////////////////
	///do cache flush all
    _mpM4UDrv->m4u_cache_flush_all(M4U_CLNTMOD_IMG);
	///////////////////////////////////////////////
	///delete m4u driver pointer
	if(_mpM4UDrv)
    {
       delete _mpM4UDrv;
    }
    return 0;
}
//-----------------------------------------------------------------------------

