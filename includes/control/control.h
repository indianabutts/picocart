#ifndef PICO_CONTROL_H
#define PICO_CONTROL_H


#include "pico/stdlib.h"
#include "../config.h"



#define CONTROL_GPIO_INIT_MASK (1<<PIN_nSLTSEL | 1<<PIN_nCS1 | 1<<PIN_nCS2 | 1<<PIN_nCS12 | 1<<PIN_nREAD | 1<<PIN_nWRITE | 1<<PIN_CLK | 1<<POUT_nAHOE | 1<<POUT_nALOE  | 1<<POUT_nWAIT | 1<<POUT_nDOUT | 1<<POUT_nDOE | 1<<PIO_D0 | 1<<(PIO_D0+1) | 1<<(PIO_D0+2) | 1<<(PIO_D0+3) | 1<<(PIO_D0 +4) | 1<<(PIO_D0 +5) | 1<<(PIO_D0 +6) | 1<<(PIO_D0 +7) )
#define CONTROL_GPIO_INPUTS_MASK (1<<PIN_nSLTSEL | 1<<PIN_nCS1 | 1<<PIN_nCS2 | 1<<PIN_nCS12 | 1<<PIN_nREAD | 1<<PIN_nWRITE | 1<<PIN_CLK)
#define CONTROL_GPIO_OUTPUTS_MASK (1<<POUT_nAHOE | 1<<POUT_nALOE  | 1<<POUT_nWAIT | 1<<POUT_nDOUT | 1<<POUT_nDOE)
#define CONTROL_GPIO_ADDRESS_MASK (1<<POUT_nAHOE | 1<<POUT_nALOE)
#define CONTROL_GPIO_DATA_MASK (1<<PIO_D0 | 1<<(PIO_D0+1) | 1<<(PIO_D0+2) | 1<<(PIO_D0+3) | 1<<(PIO_D0 +4) | 1<<(PIO_D0 +5) | 1<<(PIO_D0 +6) | 1<<(PIO_D0 +7) )
uint8_t control_init_state(){
    gpio_set_dir_in_masked(CONTROL_GPIO_INPUTS_MASK);
    gpio_set_dir_out_masked(CONTROL_GPIO_OUTPUTS_MASK | CONTROL_GPIO_DATA_MASK);
    gpio_set_mask(CONTROL_GPIO_OUTPUTS_MASK);
    gpio_clr_mask(1<<POUT_nWAIT | 1<<POUT_nDOUT | 1<<POUT_nAHOE);
}

uint8_t control_deassert_wait(){
    gpio_put(POUT_nWAIT,1);
}

uint8_t control_assert_wait(){
    gpio_put(POUT_nWAIT,0);
}

uint8_t control_read_address(uint16_t *address){
    gpio_set_dir_in_masked(CONTROL_GPIO_DATA_MASK);
    gpio_put_masked(CONTROL_GPIO_ADDRESS_MASK, 0 | (0<<POUT_nAHOE | 1<<POUT_nALOE));
    (*address) = ((gpio_get_all() & CONTROL_GPIO_DATA_MASK)>>4);
    gpio_put_masked(CONTROL_GPIO_ADDRESS_MASK, 0 | (1<<POUT_nAHOE | 0<<POUT_nALOE));
    (*address) |= ((gpio_get_all() & CONTROL_GPIO_DATA_MASK)>>PIO_D0);
    (*address) |= ((gpio_get_all() & CONTROL_GPIO_DATA_MASK)>>PIO_D0);
    gpio_put_masked(CONTROL_GPIO_ADDRESS_MASK, 0 | (1<<POUT_nAHOE | 1<<POUT_nALOE));
}

uint8_t control_output_data(uint8_t data){
    gpio_set_dir_out_masked(CONTROL_GPIO_DATA_MASK);
    gpio_put_masked(CONTROL_GPIO_DATA_MASK, data >> PIO_D0);
}

#endif