#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
// #include "pico/multicore.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// 3rd Party Includes
#include "ff.h"
// Project Includes
//#include "includes/sd_hw.c"
#include "msxpio.h"
#include "../shared_includes/data.h"
#include "../shared_includes/gpio.h"


#define TEST_ADDRESS_OFFSET 0x4000

void __time_critical_func(bus_loop)(void){
  
  
  
}

int main(void) {
  stdio_init_all();
  msxpio_init(pio0);
  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
  gpio_put(PICO_DEFAULT_LED_PIN,true);
  printf("Starting Run\r\n");
  // multicore_launch_core1(bus_loop);
  while (true){
    uint32_t pico = msxpio_get_address(pio0);
    uint32_t addr = pico & C_GPIO_AD_MASK;
    uint32_t n_read = pico & 0x00100000;
    uint32_t data = 0;
    if (!n_read){
      data = debug_data[addr-TEST_ADDRESS_OFFSET];
      msxpio_put_data(pio0, data);
      printf("ADD: 0x%04X    DATA: 0x%02X \r\n", addr,data);  

    }
  }
  // printf("ADD: 0x%04X    DATA: 0x%02X \r\n", addr,data);  
}
