#ifndef PICO_DEBUG_DISPLAY_H
#define PICO_DEBUG_DISPLAY_H

#include "ssd1306.h"
#include <stdint.h>

#define DISPLAY_I2C_FREQ (1000*1000)

void display_fprint(ssd1306_t *disp, uint32_t x, uint32_t y, uint32_t scale,
                    uint8_t buffer_size, const char *format, ...);

void display_print(ssd1306_t *disp, uint32_t x, uint32_t y, uint32_t scale,
                   char *string);

ssd1306_t display_init(uint32_t freq, uint8_t gpio_scl, uint8_t gpio_sda,
                  uint8_t width, uint8_t height, char i2c_address);

#endif