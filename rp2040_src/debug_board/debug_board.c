#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "includes/data.h"
#include "includes/debug_gpio.h"
#include "includes/display.h"
#include "includes/ssd1306.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include "pico/time.h"

#define DEBUG_BASE_ADDRESS 0x4000

uint32_t callback_count = 0;
bool data_ready = false;
ssd1306_t display;

void wait_callback(uint gpio, uint32_t events) { data_ready = true; }

void print_standard_message(uint16_t total_bytes, uint16_t current_byte,
                            uint8_t read_data, uint16_t correct_values,
                            bool show_complete) {
  ssd1306_clear(&display);
  display_print(&display, 0, 0, 1, "PicoCart Debug v2.2");
  display_fprint(&display, 0, 8, 1, 30, "Total Bytes: %d", total_bytes);
  display_fprint(&display, 0, 16, 1, 30, "ADD: 0x%04X",
                 DEBUG_BASE_ADDRESS + current_byte);
  display_fprint(&display, 0, 24, 1, 30, "EXP: 0x%02X REAL: 0x%02X",
                 debug_data[current_byte], read_data);
  display_fprint(&display, 0, 56, 1, 30, "%d/%d Passes", correct_values,
                 total_bytes);
  if (show_complete) {
    display_print(&display, 0, 40, 1, "Test Completed...");
  }
  ssd1306_show(&display);
}

/*
  Logic for the debug board should be:
  - It sets up the address on the board
  - It sets the AD pins to read mode
  - It pulses the SLTSEL/CS1 signal
  - It waits for the /WAIT signal
  - It reads the data written from the bus
  - It compares it to the data it expects, and logs the result
  - Loop until program is finished


  TODO: Could have it controllable via UART so you can
  - run individual tests (i.e. check a specific address)
  - run the full test again
 */

int main() {
    sleep_ms(1000);
  uint16_t current_byte = 0;
  uint8_t read_data = 0x00;
  uint16_t correct_values = 0;
  uint pin_value = 0;
  const uint16_t total_bytes = sizeof(debug_data);
  stdio_init_all();
  // Setup Display
  display = display_init(DISPLAY_I2C_FREQ, 26, 27, 128, 64, 0x3C);
  ssd1306_clear(&display);

  // Setup GPIO and IRQ
  debug_gpio_init_pins();

  debug_gpio_set_cs(D_nCS1, 1);
  debug_gpio_setup_wait_irq(&wait_callback);

  // Print Initial Message to Display
  print_standard_message(total_bytes, current_byte, read_data, correct_values,
                         false);

  while (true) {
      pin_value=~pin_value;
      gpio_put(D_nCS2, pin_value);
  }
  // Setup First Address before entering loop

  debug_gpio_set_ad_dir(true);
  debug_gpio_set_address(DEBUG_BASE_ADDRESS + current_byte);
  debug_gpio_set_ad_dir(false);
  debug_gpio_set_cs(D_nCS1, 0);
  while (true) {
    if (!data_ready) {
      gpio_xor_mask(D_nCS2);
      continue;
    }
    debug_gpio_set_cs(D_nCS1, 1);

    data_ready = false;
    read_data = debug_gpio_read_data();
    if (read_data == debug_data[current_byte]) {
      correct_values++;
    }
    current_byte++;
    if (current_byte == total_bytes) {
      break;
    }

    print_standard_message(total_bytes, current_byte, read_data, correct_values,
                           false);

    debug_gpio_set_ad_dir(true);
    debug_gpio_set_address(DEBUG_BASE_ADDRESS + current_byte);
    debug_gpio_set_ad_dir(false);
    debug_gpio_set_cs(D_nCS1, 0);
  }
  print_standard_message(total_bytes, current_byte, read_data, correct_values,
                         true);
  while (true) {
  }
}
