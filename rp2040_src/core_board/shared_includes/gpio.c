#include "gpio.h"
#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


void _gpio_set_ad_dir(bool output) {
  if (output) {
    gpio_set_dir_out_masked(C_GPIO_AD_MASK);
    return;
  }
  gpio_set_dir_in_masked(C_GPIO_AD_MASK);
  return;
}

void core_gpio_init_pins() {
  gpio_init_mask(C_GPIO_INIT_MASK);
  gpio_set_dir_masked(C_GPIO_INIT_MASK,C_GPIO_DIR_VALUE);
  gpio_pull_up(C_POUT_nDOE);
  gpio_disable_pulls(C_PIN_nSLTSEL);
  gpio_disable_pulls(C_PIN_nREAD);
  gpio_pull_down(C_POUT_nWAIT);
  gpio_put(C_POUT_nWAIT, false);
  gpio_put(C_POUT_nDOE,true);
  return;
}

void core_gpio_setup_ad_read(){
  _gpio_set_ad_dir(false);
  gpio_put_masked(C_GPIO_TXVR_MASK, C_GPIO_ADDR_IN_VALUE);
  return;
}

void core_gpio_setup_data_read(){
  _gpio_set_ad_dir(false);
  gpio_put_masked(C_GPIO_TXVR_MASK, C_GPIO_DATA_READ_VALUE);
  return;
}
void core_gpio_setup_data_write(){
  _gpio_set_ad_dir(true);
  gpio_put_masked(C_GPIO_TXVR_MASK, C_GPIO_DATA_WRITE_VALUE);
  return;
}
void core_gpio_set_wait_signal(bool value) { gpio_put(C_POUT_nWAIT, value); }

uint8_t core_gpio_read_data() {
  return  0xFF & gpio_get_all();
}

uint16_t core_gpio_read_address() {
  return (gpio_get_all() & 0xFFFF);
}

void core_gpio_write_data(uint8_t data) {
  gpio_put_masked(C_GPIO_D_MASK, data);
}
