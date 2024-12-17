#include "address.pio.h"
#include "msxpio.h"
#include "gpio.h"
static PIO msx_pio;

static struct {
    uint offset;
    pio_sm_config config;
} msx_sm[3];

void msxpio_init(PIO pio){
    msx_pio = pio;

    pio_gpio_init(pio, C_PIN_nSLTSEL);
    gpio_disable_pulls(C_PIN_nSLTSEL);

    for (uint gpio=C_PIO_D0; gpio<C_PIO_D0+16; gpio++){
        pio_gpio_init(pio,gpio);
        gpio_disable_pulls(gpio);
        gpio_set_input_hysteresis_enabled(gpio,false);
    }

    pio_gpio_init(pio, C_PIN_nREAD);
    pio_gpio_init(pio, C_PIN_nWRITE);
    gpio_disable_pulls(C_PIN_nREAD);
    gpio_disable_pulls(C_PIN_nWRITE);
    pio_gpio_init(pio, GPIO_nAOE);
    pio_gpio_init(pio, GPIO_nDOE);
    pio_sm_set_pindirs_with_mask(pio, SM_ADDRESS, 3ul << GPIO_nAOE, 3ul << GPIO_nAOE);
    pio_sm_set_pins_with_mask(pio, SM_ADDRESS, 3ul << GPIO_nAOE, 3ul << GPIO_nAOE);

    gpio_init(C_POUT_nWAIT);
    gpio_disable_pulls(C_POUT_nWAIT);
    gpio_set_dir(C_POUT_nWAIT, true);

    msx_sm[SM_ADDRESS].offset = pio_add_program(pio, &address_program);
    msx_sm[SM_ADDRESS].config = address_program_get_default_config(msx_sm[SM_ADDRESS].offset);
    address_program_set_config(&msx_sm[SM_ADDRESS].config);

    msx_sm[SM_READ].offset = pio_add_program(pio, &read_program);
    msx_sm[SM_READ].config = read_program_get_default_config(msx_sm[SM_READ].offset);
    read_program_set_config(&msx_sm[SM_READ].config);

    msx_sm[SM_WRITE].offset = pio_add_program(pio, &write_program);
    msx_sm[SM_WRITE].config = write_program_get_default_config(msx_sm[SM_WRITE].offset);
    write_program_set_config(&msx_sm[SM_WRITE].config);
    gpio_put(C_POUT_nWAIT, true);
}