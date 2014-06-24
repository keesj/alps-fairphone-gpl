#include <platform/mt_sleep.h>

void mtk_sleep(u32 timeout, kal_bool en_deep_idle)
{
    printf("enter mtk_sleep, timeout = %d\n", timeout);

    gpt_busy_wait_ms(timeout);

    return 0;
}

void sc_mod_init(void)
{
    printf("[BATTERY] sc_mod_init : done\n");
}

void sc_mod_exit(void)
{
    printf("[BATTERY] sc_mod_exit : done\n");
}