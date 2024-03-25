#ifndef MSX_DEBUG_GPIO_H
#define MSX_DEBUG_GPIO_H

#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>

#define D_UART_TX 0
#define D_UART_RX 1
#define D_AD0 2
#define D_AL_PULSE  10
#define D_AH_PULSE  11
#define D_UNCONNECTED_1  12
#define D_UNCONNECTED_2  13
#define D_UNCONNECTED_3  14
#define D_UNCONNECTED_4  15
#define D_nDOUT  16
#define D_nDOE  17
#define D_nWAIT  18
#define D_nCS1  19
#define D_nCS2  20
#define D_nWRITE  21
#define D_nREAD  22
#define D_SDA  26
#define D_SCL  27
#define D_nSLTSEL  28


#define D_GPIO_INIT_MASK                                                         \
  (1 << D_AL_PULSE | 1 << D_AH_PULSE | 1 << D_nDOUT | 1 << D_nDOE |            \
   1 << D_nWAIT | 1 << D_nCS1 | 1 << D_nCS2 | 1 << D_nWRITE | 1 << D_nREAD |   \
   1 << D_nSLTSEL)
#define D_GPIO_DIR_MASK							\
    (1 << D_AL_PULSE | 1 << D_AH_PULSE | 0 << D_nDOUT | 0 << D_nDOE |	\
     0 << D_nWAIT | 1 << D_nCS1 | 1 << D_nCS2 | 1 << D_nWRITE | 1 << D_nREAD | \
     1 << D_nSLTSEL)
#define D_GPIO_AD_MASK                                                         \
    (1 << D_AD0 | 1 << (D_AD0 + 1) | 1 << (D_AD0 + 2) | 1 << (D_AD0 + 3) | \
     1 << (D_AD0 + 4) | 1 << (D_AD0 + 5) | 1 << (D_AD0 + 6) | 1 << (D_AD0 + 7))




typedef enum {
  CS1 = D_nCS1,
  CS2 = D_nCS2,
  SLTSEL = D_nSLTSEL
} debug_gpio_control_signal_t;

void debug_gpio_init_pins();
void debug_gpio_setup_wait_irq(gpio_irq_callback_t callback);
void debug_gpio_set_address(uint16_t address);
void debug_gpio_set_ad_dir(bool output);
uint8_t debug_gpio_read_data();
void debug_gpio_set_cs(debug_gpio_control_signal_t signal_to_assert, uint8_t value);

/*
If IRQ isn't used to wait for the assertion of the /Wait signal,
This can be used in a while_loop to poll for the wait signal
 */

bool debug_gpio_poll_for_wait();


#endif


