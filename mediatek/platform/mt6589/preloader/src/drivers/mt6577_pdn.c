#include "typedefs.h"
#include "platform.h"
#include "mt6577_pdn_hw.h"
#include "mt6577_pdn_sw.h"


kal_bool PDN_Get_Peri_Status (PDNCONA_MODE mode)
{
    if (DRV_Reg32 (APMCUSYS_PDN_CON0) & (1 << mode))
        return KAL_TRUE;        // this module is POWER DOWN
    else
        return KAL_FALSE;       // this module is POWER UP
}

void PDN_Power_CONA_DOWN (PDNCONA_MODE module, BOOL enable)
{
    return;
}

void PDN_Power_CONB_DOWN (PDNCONB_MODE module, kal_bool enable)
{
    return;
}
