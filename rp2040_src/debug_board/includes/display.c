#include "display.h"
#include "hardware/gpio.h"
#include "ssd1306.h"
#include <stdarg.h>
//#include "hardware/i2c.h"

void display_fprint(ssd1306_t *disp, uint32_t x, uint32_t y, uint32_t scale,
                       uint8_t buffer_size, const char *format, ...) {
  char formatted_string[buffer_size];

  va_list va;
  va_start(va, formatted_string);
  vsprintf(formatted_string, format, va);
  va_end(va);
  ssd1306_draw_string(disp, x, y, scale, formatted_string);
  return;
}

void display_print(ssd1306_t *disp, uint32_t x, uint32_t y, uint32_t scale,
                   char *string) {
  ssd1306_draw_string(disp, x, y, scale, string);
  return;
}

void display_init(ssd1306_t *disp, uint8_t gpio_scl, uint8_t gpio_sda,
                  uint8_t width, uint8_t height, char i2c_address) {
    //i2c_init(i2c1, 4000000);
  gpio_set_function(gpio_scl, GPIO_FUNC_I2C);
  gpio_set_function(gpio_sda, GPIO_FUNC_I2C);
  gpio_pull_up(gpio_scl);
  gpio_pull_up(gpio_sda);
  disp->external_vcc = false;
  // ssd1306_init(disp, width, height, i2c_address, i2c1);
  return;
}
