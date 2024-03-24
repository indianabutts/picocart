#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "includes/ssd1306.h"
#include "pico/time.h"



const char data[] = {
    0x41,0x42,0x43,0x44,0x45,0x46
};

void setup_gpios(void);
void print_message(void);

void fprint_to_display(ssd1306_t *disp,uint32_t x, uint32_t y, uint32_t scale, uint8_t buffer_size, char *format, ...) {
  char formatted_string[buffer_size];
  va_list va;
  va_start(va, format);
  vsprintf(formatted_string, format, va);
  va_end(va);
  ssd1306_draw_string(disp, x, y, scale, formatted_string);
  return;
}

int main(){
    sleep_ms(1000);
    
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
  char formated_string[30];
  fprint_to_display(&disp, 0, 50, 1, 30, "%d Bytes\r\n", sizeof(data));
//  sprintf(formated_string, "%d bytes\r\n", sizeof(data));
  ssd1306_draw_string(&disp, 0, 50, 1, formated_string);
  ssd1306_show(&disp);
  bool has_printed = false;
  printf("Starting Run\r\n");
  while (true) {
      sleep_ms(1000);
      if(!has_printed){
        printf("Running Test %d \r\n", sizeof(data));
	has_printed = true;
      }
      
  }
}





