#include "debug_gpio.h"
#include "hardware/gpio.h"
#include <stdbool.h>

void debug_gpio_init_pins() {
  gpio_init_mask(D_GPIO_INIT_MASK);
  gpio_set_dir_masked(D_GPIO_INIT_MASK, D_GPIO_DIR_MASK);
  return;
}

void debug_gpio_setup_wait_irq(gpio_irq_callback_t callback) {
    gpio_pull_up(D_nWAIT);
    gpio_set_irq_enabled_with_callback(D_nWAIT, GPIO_IRQ_EDGE_FALL, true, callback);
    return;
}

void debug_gpio_set_ad_dir(bool output) {
  for (uint8_t i = 0; i < 8; i++) {
      gpio_set_dir(D_AD0+i, output);
  }
}

void debug_gpio_set_address(uint16_t address) {
    //First we set the upper address
  gpio_put_masked(D_GPIO_AD_MASK, (address >> 8) & 0x0F);
  gpio_put(D_AH_PULSE, true);
  gpio_put(D_AH_PULSE, false);
  // Then we will push the lower address
  gpio_put_masked(D_GPIO_AD_MASK, address & 0x0F);
  gpio_put(D_AL_PULSE, true);
  gpio_put(D_AL_PULSE, false);
  return;
}

uint8_t debug_gpio_read_data() {
    return (gpio_get_all() & D_GPIO_AD_MASK) >> (D_AD0 + 7);
}

void debug_gpio_set_cs(debug_gpio_control_signal_t signal_to_assert, uint8_t value) {
    gpio_put(signal_to_assert, value);
}

bool debug_gpio_poll_for_wait() { return !gpio_get(D_nWAIT); }
