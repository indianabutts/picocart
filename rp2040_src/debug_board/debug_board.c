#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "includes/ssd1306.h"



void setup_gpios(void);
void print_message(void);
int main(){
  stdio_init_all();

  // Set the GPIO Based on the Pinout
//  gpio_init_mask(D_GPIO_INIT_MASK);

  setup_gpios();
  print_message();
  return 0;
}

void setup_gpios(void){
  i2c_init(i2c1, 400000);
  gpio_set_function(26, GPIO_FUNC_I2C);
  gpio_set_function(27, GPIO_FUNC_I2C);
  gpio_pull_up(26);
  gpio_pull_up(27);
}


void print_message(void) {
    const char *message[] = {"PicoCart Debug", "I love", "Baba and Mama"};

  ssd1306_t disp;
  disp.external_vcc = false;
  ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
  ssd1306_clear(&disp);
  ssd1306_draw_string(&disp, 0, 0, 1, message[0]);
  for (int i=1; i<3; i++){
      ssd1306_draw_string(&disp, 0, (i+1)*10, 1, message[i]);
  
  }
  ssd1306_show(&disp);
  sleep_ms(25);

  while(true){
      
  }
}





