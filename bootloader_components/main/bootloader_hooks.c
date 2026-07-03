#include "sdkconfig.h"
#include "hal/clk_gate_ll.h"
#include "bootloader_hooks.h"

void bootloader_hooks_include(void)
{
}

void bootloader_before_init(void)
{
#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S3
    periph_ll_reset(PERIPH_PWM0_MODULE);
    periph_ll_reset(PERIPH_PWM1_MODULE);
#endif

    periph_ll_reset(PERIPH_RMT_MODULE);
    periph_ll_reset(PERIPH_LEDC_MODULE);
}
