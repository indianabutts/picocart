#include "includes/constants.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "includes/ssd1306.h"


int main(){
  stdio_init_all();

  // Set the GPIO Based on the Pinout
  gpio_init_mask(D_GPIO_INIT_MASK);

  char buffer[4096];

  SSD1306_FrameBuffer_Mono_VLSB framebuffer = {
    .buffer = buffer,
    .height = 64,
    .width = 64
  };

  SSD1306_framebuffer_get_pages(&framebuffer);
  
}
