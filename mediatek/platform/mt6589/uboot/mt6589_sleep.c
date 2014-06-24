#if 0
#include <asm/arch/mt6589_irq.h>
#endif 
#include <asm/arch/mt6589_sleep.h>

//#define HAVE_SLEEP_MODE

#if 0
static void sc_go_to_sleep(u32 timeout, kal_bool en_deep_idle)
{
    struct mtk_irq_mask mask;

    __asm__ __volatile__("cpsid i @ arch_local_irq_disable" : : : "memory", "cc"); // set i bit to disable interrupt

    mt6589_irq_mask_all(&mask); // mask all interrupts

    gpt_irq_ack();

    mt6589_irq_unmask(MT6589_GPT_IRQ_ID);

    gpt_one_shot_irq(timeout);

    __asm__ __volatile__("dsb" : : : "memory");
    __asm__ __volatile__("wfi"); // enter wfi

    gpt_irq_ack();
    mt6589_irq_ack(MT6575_GPT_IRQ_ID);

    mt6589_irq_mask_restore(&mask); // restore all interrupts

    __asm__ __volatile__("cpsie i @ arch_local_irq_enable" : : : "memory", "cc"); // clear i bit to enable interrupt
}
#endif 

void mtk_sleep(u32 timeout, kal_bool en_deep_idle)
{
    printf("enter mtk_sleep, timeout = %d\n", timeout);

#ifndef HAVE_SLEEP_MODE
    gpt_busy_wait_ms(timeout);
#else
    sc_go_to_sleep(timeout, en_deep_idle);
#endif

    return 0;
}

void power_saving_init(void) {}

void sc_mod_init(void)
{
    #if 0
    mt6589_init_irq();

    gpt_irq_init();

    power_saving_init();
    #endif

    printf("[BATTERY] sc_hw_init : Done\r\n");
}

void sc_mod_exit(void) {}