 //#define DEV_APC_DEBUG
 
/*=======================================================================*/
/* HEADER FILES                                                          */
/*=======================================================================*/
#include "platform.h"
#include "device_apc.h"

#define _DEBUG_
 
/* Debug message event */
#define DBG_EVT_NONE        0x00000000      /* No event */
#define DBG_EVT_ERR         0x00000001      /* ERR related event */
#define DBG_EVT_DOM         0x00000002      /* DOM related event */

#define DBG_EVT_ALL         0xffffffff

#define DBG_EVT_MASK       (DBG_EVT_DOM )

#ifdef _DEBUG_
#define MSG(evt, fmt, args...) \
    do {    \
    if ((DBG_EVT_##evt) & DBG_EVT_MASK) { \
    print(fmt, ##args); \
    } \
    } while(0)

#define MSG_FUNC_ENTRY(f)   MSG(FUC, "<FUN_ENT>: %s\n", __FUNCTION__)
#else
#define MSG(evt, fmt, args...) do{}while(0)
#define MSG_FUNC_ENTRY(f)      do{}while(0)
#endif

void device_APC_dom_setup(void)
{
    MSG(DOM, "\nDevice APC domain init setup:\n\n");
    reg_write32(DEVAPC3_APC_CON, 0x0);
#ifdef DBG_PRELOADER
    MSG(DOM, "Domain Setup (0x%x)\n", reg_read32(DEVAPC3_MAS_DOM));
#endif

    reg_set_field(DEVAPC3_MAS_DOM, MD1_AHB_0, DOMAIN_MD1);
    reg_set_field(DEVAPC3_MAS_DOM, MD1_AXI_1, DOMAIN_MD1);
    reg_set_field(DEVAPC3_MAS_DOM, MD1_AXI_2, DOMAIN_MD1);
    reg_set_field(DEVAPC3_MAS_DOM, MD2_AHB_0, DOMAIN_MD2);
    reg_set_field(DEVAPC3_MAS_DOM, MD2_AXI_1, DOMAIN_MD2);
    reg_set_field(DEVAPC3_MAS_DOM, MD2_AXI_2, DOMAIN_MD2);

    /*Setup MM masters to domain 3 via SMI*/
    reg_write32(0x1000E5C0, 0x66666666);
    reg_write32(0x1000E5C4, 0x66666666);
    reg_write32(0x1000E5C8, 0x66666666);
    reg_write32(0x1000E5CC, 0x66666666);
    reg_write32(0x1000E5D0, 0x66666666);
    reg_write32(0x1000E5D4, 0x66666666);
    reg_write32(0x1000E5D8, 0x66666666);

#ifdef DBG_PRELOADER
    MSG(DOM, "Device APC domain after setup:\n");
    MSG(DOM, "Domain Setup (0x%x)\n", reg_read32(DEVAPC3_MAS_DOM));
#endif
}
