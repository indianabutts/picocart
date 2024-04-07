#ifndef MSX_GPIO_H
#define MSX_GPIO_H

#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>

#define C_PIN_nSLTSEL 2
#define C_PIN_nCS1 3
#define C_PIN_nCS2 4
#define C_PIN_nCS12 5
#define C_PIN_nREAD 6
#define C_PIN_nWRITE 7
#define C_PIN_CLK 26

#define C_PIO_D0 12

#define C_POUT_nAHOE 20
#define C_POUT_nALOE 21
#define C_POUT_nDOE 22
#define C_POUT_nDOUT 27
#define C_POUT_nWAIT 28

#define C_GPIO_INIT_MASK                                                       \
  (1 << C_PIN_nSLTSEL | 1 << C_PIN_nCS1 | 1 << C_PIN_nCS2 | 1 << C_PIN_nCS12 |   \
   1 << C_PIN_nREAD | 1 << C_PIN_nWRITE | 1 << C_PIN_CLK | 1 << C_POUT_nAHOE | \
   1 << C_POUT_nALOE | 1 << C_POUT_nDOE | 1 << C_POUT_nDOUT |                  \
   1 << C_POUT_nWAIT)

#define C_GPIO_AD_MASK	0xFF << C_PIO_D0

#define C_GPIO_DIR_MASK                                                        \
  0 | (1 << C_POUT_nAHOE | 1 << C_POUT_nALOE | 1 << C_POUT_nDOE |              \
       1 << C_POUT_nDOUT | 1 << C_POUT_nWAIT)

#define C_GPIO_ADR_OE_MASK (1 << C_POUT_nALOE | 1 << C_POUT_nAHOE | 1 << C_POUT_nDOE | 1 << C_POUT_nDOUT)

#define C_GPIO_ALOE_VALUE 0xFFFF & (0 << C_POUT_nALOE)
#define C_GPIO_AHOE_VALUE 0xFFFF & (0 << C_POUT_nAHOE)
#define C_GPIO_DATA_OUT 0xFFFF & (0 << C_POUT_nDOE & 0 << C_POUT_nDOUT)
#define C_GPIO_DATA_IN 0xFFFF  &  0 << C_POUT_nDOE



typedef enum {
  CS1 = C_PIN_nCS1,
  CS2 = C_PIN_nCS2,
  CS12 = C_PIN_nCS12,
  READ = C_PIN_nREAD
} core_gpio_rom_sel_t;

void core_gpio_init_pins();
void core_gpio_set_ad_dir(bool output);
void core_gpio_set_wait_signal(bool value);
void core_gpio_setup_cs_irq(core_gpio_rom_sel_t select_signal, gpio_irq_callback_t callback);
uint8_t core_gpio_read_data();
uint16_t core_gpio_read_address();
void core_gpio_write_data(uint8_t data);

#endif
