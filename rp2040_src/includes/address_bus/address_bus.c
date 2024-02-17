#include "address_bus.h"
#include <hardware/pio.h>
#include "address_bus.pio.h"
#include "../config.h"
#include <stdio.h>

static void address_bus_setup(PIO pio, uint sm){
    uint program_offset = pio_add_program(pio, &address_bus_program);
    pio_sm_claim(pio, sm);
    pio_sm_config pio_config = address_bus_program_get_default_config(program_offset);
    sm_config_set_in_pins(&pio_config, PIO_D0);
    sm_config_set_set_pins(&pio_config, POUT_nAHOE, 2);

    sm_config_set_in_shift(&pio_config, false, true, 16);

    pio_sm_init(pio, sm, program_offset, &pio_config);

    pio_gpio_init(pio, PIN_nSLTSEL);
    for(uint8_t i = POUT_nAHOE; i<POUT_nAHOE+2;i++){
        pio_gpio_init(pio, i);
        gpio_set_pulls(i, false, false);
    }
    for(uint8_t i = PIO_D0; i<PIO_D0+8;i++){
        pio_gpio_init(pio, i);
        gpio_set_pulls(i, false, false);
    }
}

void address_bus_init(){
    address_bus_setup(CONFIG_ADDRESS_PIO, 0);
    pio_enable_sm_mask_in_sync(CONFIG_ADDRESS_PIO, 1);
}

void __time_critical_func(address_bus_loop)(){
    while(1){
        uint32_t value = pio_sm_get_blocking(CONFIG_ADDRESS_PIO, 0);
        printf("0x%04X",value);
    }
}