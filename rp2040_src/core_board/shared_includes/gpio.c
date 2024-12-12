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
  gpio_init_mask(C_GPIO_INIT_MASK | C_GPIO_AD_MASK);
  gpio_init(C_POUT_nDOE);
  gpio_set_dir_masked(C_GPIO_INIT_MASK, C_GPIO_DIR_MASK);
  gpio_pull_up(C_POUT_nDOE);
  gpio_pull_up(C_POUT_nDOUT);
  gpio_pull_up(C_POUT_nWAIT);
  gpio_put(C_POUT_nDOE,true);
  return;
}

void core_gpio_setup_ad_read(){
  _gpio_set_ad_dir(false);
  gpio_put_masked((1<<C_POUT_nDOUT) | (1 << C_POUT_nDOE) | (1<<C_POUT_nAOE), ((1<<C_POUT_nDOUT) | (1 << C_POUT_nDOE)) & (0<<C_POUT_nAOE));
  return;
}

void core_gpio_setup_data_read(){
  _gpio_set_ad_dir(false);
  gpio_put_masked((1<<C_POUT_nDOUT) | (1 << C_POUT_nDOE) | (1<<C_POUT_nAOE), ((1<<C_POUT_nDOUT) | (1 << C_POUT_nAOE)) & (0<<C_POUT_nDOE));
  return;
}
void core_gpio_setup_data_write(){
  _gpio_set_ad_dir(true);
  gpio_put_masked((1<<C_POUT_nDOUT) | (1 << C_POUT_nDOE) | (1<<C_POUT_nAOE), ((1 << C_POUT_nAOE)) & (0<<C_POUT_nDOE) & (0<<C_POUT_nDOUT));
  return;
}
void core_gpio_set_wait_signal(bool value) { gpio_put(C_POUT_nWAIT, value); }

uint8_t core_gpio_read_data() {

  //gpio_put_masked(C_GPIO_ADR_OE_MASK, C_GPIO_DATA_IN);
  return  0xFF & gpio_get_all();
}

uint16_t core_gpio_read_address() {
  return (gpio_get_all() & 0xFFFF);
}

void core_gpio_write_data(uint8_t data) {
  gpio_put_masked(C_GPIO_AD_MASK, data);

}
