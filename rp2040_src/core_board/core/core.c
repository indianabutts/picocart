#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// 3rd Party Includes
#include "ff.h"
// Project Includes
// #include "includes/sd_hw.c"
#include "../shared_includes/gpio.h"
#include "../shared_includes/data.h"
#include "hardware/vreg.h"

#define TEST_ADDRESS_OFFSET 0x4000

void __time_critical_func(read_callback)()
{
  uint16_t current_address = 0;
  uint8_t data = 0;
  uint32_t gpio=0;
  core_gpio_setup_ad_read();
  gpio_put(C_POUT_nWAIT, 1);
  bool previous_state = false;
  while (1)
  {
    gpio = gpio_get_all();
    if ((gpio & 1<<C_PIN_nSLTSEL) == 0){
      if (!previous_state) {
       current_address = gpio & C_GPIO_AD_MASK;
       if (current_address >0x7FFF || current_address<TEST_ADDRESS_OFFSET || (gpio & 0x00100000) ==0){continue;};
       data = debug_data[current_address-TEST_ADDRESS_OFFSET];
       core_gpio_write_data(data);
       core_gpio_setup_data_write();
      printf("ADD: 0x%04X    DATA: 0x%02X \r\n", current_address,data);
       previous_state=true;

      }
     }
     else {
      previous_state=false;
      core_gpio_setup_ad_read();
     }
  }
 return; 
}

int main()
{
  stdio_init_all();
  set_sys_clock_khz(250000, true);
  
  // Set up our UART with a basic baud rate.
  // uart_init(uart0, 115200);

  // // Set the TX and RX pins by using the function select on the GPIO
  // // Set datasheet for more information on function select
  // gpio_set_function(0, GPIO_FUNC_UART);
  // gpio_set_function(1, GPIO_FUNC_UART);
  core_gpio_init_pins();
  read_callback();
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