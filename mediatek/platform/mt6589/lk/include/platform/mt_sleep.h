#include <platform/mt_pmic.h>
#include <platform/mt_reg_base.h>
#include <platform/mt_typedefs.h>

extern void sc_mod_init(void);
extern void sc_mod_exit(void);

extern void mtk_sleep(u32 timeout, kal_bool en_deep_idle);