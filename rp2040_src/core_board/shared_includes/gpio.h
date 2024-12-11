#ifndef MSX_GPIO_H
#define MSX_GPIO_H

#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>

#define C_PIO_D0 0

#define C_PIN_nWRITE 20
#define C_PIN_nSLTSEL 21

#define C_POUT_nDOUT 22

#define C_POUT_nWAIT 26
#define C_POUT_nAOE 27
#define C_POUT_nDOE 28


#define C_GPIO_INIT_MASK                                                       \
    (1 << C_PIN_nSLTSEL | 1 << C_PIN_nWRITE | 1 << C_POUT_nAOE |	\
     1 << C_POUT_nDOE | 1 << C_POUT_nDOUT |				\
     1 << C_POUT_nWAIT)

#define C_GPIO_AD_MASK	0xFFFF << C_PIO_D0

#define C_GPIO_DIR_MASK                                                        \
  0 | (1 << C_POUT_nAOE | 1 << C_POUT_nDOE |              \
       1 << C_POUT_nDOUT | 1 << C_POUT_nWAIT)

#define C_GPIO_ADR_OE_MASK (1 << C_POUT_nAOE | 1 << C_POUT_nDOE | 1 << C_POUT_nDOUT)

#define C_GPIO_DATA_OUT 0xFFFF & (0 << C_POUT_nDOE & 0 << C_POUT_nDOUT)
#define C_GPIO_DATA_IN 0xFFFF  &  0 << C_POUT_nDOE


void core_gpio_init_pins();
void core_gpio_set_ad_dir(bool output);
void core_gpio_set_wait_signal(bool value);
void core_gpio_setup_cs_irq(gpio_irq_callback_t callback);
uint8_t core_gpio_read_data();
uint16_t core_gpio_read_address();
void core_gpio_write_data(uint8_t data);

#endif
