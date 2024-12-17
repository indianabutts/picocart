#ifndef MSX_GPIO_H
#define MSX_GPIO_H

#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>

#define C_PIO_D0 0

#define C_PIN_nREAD 20
#define C_PIN_nSLTSEL 21
#define C_PIN_nWRITE 22
#define C_POUT_nWAIT 26
#define C_POUT_nAOE 27
#define C_POUT_nDOE 28


#define C_GPIO_INIT_MASK 0x1C30FFFF
#define C_GPIO_AD_MASK 0x0000FFFF
#define C_GPIO_D_MASK 0x000000FF
#define C_GPIO_TXVR_MASK 0x18000000
#define C_GPIO_ADDR_IN_VALUE 0x10000000
#define C_GPIO_DATA_READ_VALUE 0x08000000
#define C_GPIO_DATA_WRITE_VALUE 0x08000000
#define C_GPIO_DIR_VALUE 0x1C000000
#define C_GPIO_SLTSEL_MASK 0x00200000


void core_gpio_init_pins();
void core_gpio_setup_ad_read();
void core_gpio_setup_data_read();
void core_gpio_setup_data_write();
void core_gpio_set_wait_signal(bool value);
uint8_t core_gpio_read_data();
uint16_t core_gpio_read_address();
void core_gpio_write_data(uint8_t data);

#endif
