#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "includes/ssd1306.h"
//#include "includes/display.h"
//#include "includes/debug_gpio.h"
//#include "pico/time.h"


uint32_t callback_count = 0;

//void wait_callback(uint gpio, uint32_t events) {
//  callback_count++;
  
//}


const char data[] = {
    0x41,0x42,0x43,0x44,0x45,0x46
};



//int main() {
//  stdio_init_all();
//  ssd1306_t display;
//  display_init(&display, 26, 27, 128, 64, 0x78);
//  ssd1306_clear(&display);
//  debug_gpio_init_pins();
//  debug_gpio_setup_wait_irq(&wait_callback);
//
//  display_print(&display, 0, 0, 1, "PicoCart Debug v2");
//  ssd1306_show(&display);
//
//  while (true) {
//    sleep_ms(500);
//    ssd1306_clear(&display);
//    display_fprint(&display, 0, 10, 1, 30, "Callback Count: %d",
//                   callback_count);
//    ssd1306_show(&display);
//    printf("Still Running");
//  }
//  
//}

/* OLD CODE, Keeping until I can test this against the Pi Pico
 */
void setup_gpios(void);
void print_message();

int main(){
  stdio_init_all();
  
    //display_init(&disp, 26, 27, 128, 64, 0x3C);
    //Set the GPIO Based on the Pinout
  //gpio_init_mask(D_GPIO_INIT_MASK);

 setup_gpios();
 print_message();
 while (true) {
     
 }
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
    ssd1306_draw_string(&disp, 0, (i + 1) * 10, 1, message[i]);
  }
  //display_fprint(disp, 0, 50, 1, 30, "%d Bytes\r\n", sizeof(data));
  ssd1306_show(&disp);
}

