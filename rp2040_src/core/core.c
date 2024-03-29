#include <stdio.h>
#include "hardware/gpio.h"
// 3rd Party Includes
#include "ff.h"
// Project Includes
//#include "includes/sd_hw.c"
#include "includes/gpio.h"


bool read_requested = false;

void cs_callback(uint gpio, uint32_t events) {
    read_requested = true;
}


int main() {
    stdio_init_all();
    core_gpio_init_pins();
    core_gpio_setup_cs_irq(CS1, cs_callback);

    while (true) {
      if (!read_requested) {
	  continue;
      }
      read_requested = false;
      gpio_put(C_POUT_nWAIT, true);
      gpio_put(C_POUT_nWAIT, false);
      sleep_ms(1);
      gpio_put(C_POUT_nWAIT, true);
    }
}

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
