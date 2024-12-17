#ifndef MSX_PIO_H
#define MSX_PIO_H

#include "hardware/pio.h"

#define SM_ADDRESS 0
#define SM_READ 1
#define SM_WRITE 2

void msxpio_init(PIO pio);

void msxpio_resethandler(void(*handler)(bool asserted));

static __always_inline uint32_t msxpio_get_address(PIO pio){
    uint retry = 32;
    while(pio->fstat & (1u << (PIO_FSTAT_RXEMPTY_LSB + SM_ADDRESS)) && --retry ){
        tight_loop_contents();
    }
    return pio->rxf[SM_ADDRESS];
}

static __always_inline uint32_t msxpio_get_data(PIO pio){
    uint retry = 32;
    while(pio->fstat & (1u << (PIO_FSTAT_RXEMPTY_LSB + SM_WRITE)) && --retry ){
        tight_loop_contents();
    }
    return pio->rxf[SM_WRITE];
}


static __always_inline void msxpio_put_data(PIO pio, uint32_t data){
    pio->txf[SM_READ] = data;
}

#endif