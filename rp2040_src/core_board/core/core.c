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
// #include "includes/sd_hw.c"
#include "../shared_includes/gpio.h"
#include "../shared_includes/data.h"

#define TEST_ADDRESS_OFFSET 0x4000

void __not_in_flash_func(read_callback)(uint test)
{
 return; 
}

int main()
{
  stdio_init_all();
  // Set up our UART with a basic baud rate.
  // uart_init(uart0, 115200);

  // // Set the TX and RX pins by using the function select on the GPIO
  // // Set datasheet for more information on function select
  // gpio_set_function(0, GPIO_FUNC_UART);
  // gpio_set_function(1, GPIO_FUNC_UART);
  core_gpio_init_pins();
  gpio_put(C_POUT_nWAIT, false);

  gpio_put(C_POUT_nDOE, 1);

  uint16_t current_address = 0;
  core_gpio_setup_ad_read();
  while (true)
  {
    if (gpio_get(C_PIN_nSLTSEL)==0){
      current_address = core_gpio_read_address();
      printf("ADD: 0x%04X \r\n", current_address);
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