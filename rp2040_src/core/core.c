#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// 3rd Party Includes
#include "ff.h"
// Project Includes
//#include "includes/sd_hw.c"
#include "includes/gpio.h"
#include "includes/data.h"
#include "pico/multicore.h"

#define TEST_ADDRESS_OFFSET 0x4000

volatile bool read_requested = false;

// void core1_entry() {

//    printf("Starting Core 1");
   
//     while (1){
//       gpio_put(C_POUT_nDOE, C_PIN_nREAD);
//     }
// }

void __not_in_flash_func(cs_callback)(uint gpio, uint32_t events) { 
  if(gpio==C_PIN_nCS1) {
    read_requested = true; 
  }
  if(gpio==C_PIN_nREAD) {
    gpio_put(C_POUT_nDOUT, !gpio_get(C_PIN_nREAD));
  }
  printf("%d\r\n", gpio);
}
void __not_in_flash_func(read_callback)(uint gpio, uint32_t events) { if(gpio==C_PIN_nREAD) gpio_put(C_POUT_nDOUT, !gpio_get(C_PIN_nREAD)); }

  int main() {
    stdio_init_all();
     // Set up our UART with a basic baud rate.
    uart_init(uart0, 115200);
    // multicore_launch_core1(core1_entry);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    core_gpio_init_pins();

    gpio_set_irq_enabled_with_callback(CS1, GPIO_IRQ_EDGE_FALL, true,
                                     cs_callback);
    gpio_set_irq_enabled_with_callback(C_PIN_nREAD, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true,
                                     cs_callback);
    gpio_pull_up(C_PIN_nCS1);
    gpio_put(C_POUT_nDOE, 1);
//    //core_gpio_setup_cs_irq(CS1, cs_callback);
    volatile uint16_t current_address = 0;

    volatile uint8_t data = 0;

  // while(true){
  //   current_address = core_gpio_read_address();
  //   data = debug_data[current_address];
  //        gpio_put(C_POUT_nWAIT, true);
  //        gpio_put(C_POUT_nWAIT, false);
  //        gpio_put(C_POUT_nWAIT, true);
  //   printf("%d %d", current_address, data);

  // }
  
core_gpio_set_ad_dir(false);
gpio_put(C_POUT_nDOUT, true);
 while (true) {
    
    // gpio_put(C_POUT_nDOUT, !gpio_get(C_PIN_nREAD)); 
    if (read_requested) {
      sleep_ms(100);
      read_requested = false;
      gpio_put(C_POUT_nWAIT, true);
       gpio_put(C_POUT_nDOE, 1);
      

      current_address = core_gpio_read_address();
      // gpio_put(C_POUT_nDOE, 1);
      gpio_put(C_POUT_nALOE, 1);  
      gpio_put(C_POUT_nAHOE, 1);
      data = debug_data[current_address-TEST_ADDRESS_OFFSET];
      core_gpio_write_data(data); 
      gpio_put(C_POUT_nDOE, 0);          
      gpio_put(C_POUT_nWAIT, false);
      
    }
  }
}
/* 

int sd_card_backup() {

  FRESULT fr;
  FATFS fs;
  FIL fil;
  UINT file_size = 0;
  int ret;
  char file_buffer[65536];
  memset(file_buffer, 0, sizeof file_buffer);
  char rom_check[2];
  uint16_t rom_start_address;
  char tank[] = "Tank Battalion (1984)(Namcot)(JP).rom";
  printf("Loading %s", tank);

  // Initialize SD card
  if (!sd_init_driver()) {
    printf("ERROR: Could not initialize SD card\r\n");
    while (true)
      ;
  }
  
  // Mount drive
  fr = f_mount(&fs, "0:", 1);
  if (fr != FR_OK) {
    printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
    while (true)
      ;
  }
  //Open the file at the specified path
  fr = f_open(&fil, tank, FA_READ);
  if (fr != FR_OK) {
    printf("ERROR: Could not open file\r\n");
    while (true)
      ;
  }
  file_size = f_size(&fil);
  f_read(&fil, &file_buffer, f_size(&fil), NULL);
  printf("", file_size);

  //Copy the first 2 bytes to make sure the rom is valid (0x41 0x42)
  memcpy(&rom_check, &file_buffer, 2);

  // Unmount drive
  f_unmount("0:");
  return 0;
}
 */