#include "gpio.h"
#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>

void core_gpio_init_pins() {
  gpio_init_mask(C_GPIO_INIT_MASK);
  gpio_set_dir_masked(C_GPIO_INIT_MASK, C_GPIO_DIR_MASK);
  gpio_pull_up(C_POUT_nDOE);
  gpio_pull_up(C_POUT_nDOUT);
  gpio_pull_up(C_POUT_nAHOE);
  gpio_pull_up(C_POUT_nALOE);
  gpio_pull_up(C_POUT_nWAIT);
 
  return;
}

void core_gpio_set_ad_dir(bool output) {
  if (output) {
    gpio_set_dir_out_masked(C_GPIO_AD_MASK);
    return;
  }
  gpio_set_dir_in_masked(C_GPIO_AD_MASK);
  return;
}

void core_gpio_set_wait_signal(bool value) { gpio_put(C_POUT_nWAIT, value); }

uint8_t core_gpio_read_data() {
  core_gpio_set_ad_dir(false);
  gpio_put_masked(C_GPIO_ADR_OE_MASK, C_GPIO_DATA_IN);
  return  0xFF & (gpio_get_all()>>C_PIO_D0);
}

uint16_t core_gpio_read_address() {
    core_gpio_set_ad_dir(false);
  // Get the low address
  uint16_t address = 0;
  gpio_put_masked(C_GPIO_ADR_OE_MASK, C_GPIO_ALOE_VALUE);
  address = (gpio_get_all() >> C_PIO_D0) & 0x00FF;
  // Get the high address
  gpio_put_masked(C_GPIO_ADR_OE_MASK, C_GPIO_AHOE_VALUE);
  address |= ((gpio_get_all() >> 4) & 0xFF00);
  return address;
}

void core_gpio_write_data(uint8_t data) {
    core_gpio_set_ad_dir(true);
  // Put the data on the bus
  gpio_put_masked(C_GPIO_AD_MASK, 0 | (data << (C_PIO_D0 + 7)));
  gpio_put_masked(C_GPIO_ADR_OE_MASK, C_GPIO_DATA_OUT);
}

void core_gpio_setup_cs_irq(core_gpio_rom_sel_t select_signal,
                            gpio_irq_callback_t callback) {
  gpio_set_irq_enabled_with_callback(select_signal, GPIO_IRQ_EDGE_FALL, true,
                                     callback);
  return;
    
}
