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


#define C_GPIO_INIT_MASK                                         \
    (1 << C_PIN_nSLTSEL | 1 << C_PIN_nWRITE | 1 << C_POUT_nAOE |	\
     1 << C_POUT_nDOE | 1 << C_POUT_nDOUT |				     \
     1 << C_POUT_nWAIT)

#define C_GPIO_AD_MASK	0xFFFF

#define C_GPIO_DIR_MASK                                   \
  0 | (1 << C_POUT_nAOE | 1 << C_POUT_nDOE |              \
       1 << C_POUT_nDOUT | 1 << C_POUT_nWAIT)

#define C_GPIO_ADR_OE_MASK (1 << C_POUT_nAOE | 1 << C_POUT_nDOE | 1 << C_POUT_nDOUT)


void core_gpio_init_pins();
void core_gpio_setup_ad_read();
void core_gpio_setup_data_read();
void core_gpio_setup_data_write();
void core_gpio_set_wait_signal(bool value);
uint8_t core_gpio_read_data();
uint16_t core_gpio_read_address();
void core_gpio_write_data(uint8_t data);

#endif
