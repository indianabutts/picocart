#include <stdio.h>
#include <time.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "test_rom.h"
#include "add_sm.pio.h"
// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments




#define P_IN_nSLTSEL 2
#define P_IN_nCS1 3
#define P_IN_nCS2 4
#define P_IN_nCS12 5

#define P_IN_nREAD 6
#define P_IN_nWRITE 7


#define SPI_PORT spi1
#define SPI_MISO 8
#define SPI_CS   9
#define SPI_SCK  10
#define SPI_MOSI 11


#define P_IO_D0 12
#define P_IO_D1 13
#define P_IO_D2 14
#define P_IO_D3 15
#define P_IO_D4 16
#define P_IO_D5 17
#define P_IO_D6 18
#define P_IO_D7 19


#define P_OUT_nAHOE 20
#define P_OUT_nALOE 21
#define P_OUT_nWAIT 22
#define P_LED 25
#define P_IN_CLK 26
#define P_OUT_nDOUT 27
#define P_OUT_nDOE 28

#define DATA_MASK (1 << P_IO_D0 ) | (1 << P_IO_D1) | (1<<P_IO_D2)| (1<<P_IO_D3)| (1<<P_IO_D4)| (1<<P_IO_D5)| (1<<P_IO_D6)| (1<<P_IO_D7)




void setup_control_pins();
void setup_data_pins_for_write();
void setup_data_pins_for_read();
void write_data(uint8_t data);
void init_pins();
uint16_t get_address();


void core1_uart(){

}

int main()
{
    stdio_init_all();
    init_pins();
    setup_control_pins();
    gpio_put(P_LED, true);

    PIO pio = pio0;

    setup_data_pins_for_read();
    uint offsetAddr = pio_add_program(pio, &address_program);
    uint smAddr = pio_claim_unused_sm(pio, true);
    address_init(pio, smAddr, offsetAddr, P_IO_D0, P_OUT_nAHOE);
    pio_sm_clear_fifos(pio, smAddr);

    //multicore_launch_core1(core1_uart);
    puts("\r\n============Starting Program=============\r\n");
    bool nALOE = false;
    uint16_t address=0;
    uint8_t data=0;
    while(true){
      
      address = (pio_sm_get_blocking(pio, smAddr)>>16);
      //setup_data_pins_for_write();
      data= romdata[address-0x4000];
      //write_data(0xFF);
      //gpio_put(P_OUT_nALOE, nALOE);
      //gpio_put(P_OUT_nAHOE, !nALOE);
      //nALOE = !nALOE;
      
      //uint32_t address = 0;
      //data = 0;
      //printf("A: 0x%04x\n", address>>16);
      //setup_data_pins_for_read();
      
      //uint16_t address = get_address();
      if(address==0x4000 || address ==0x4001){
	printf("A: 0x%04x\tD: 0x%02x\r\n", address,data);
      }
    }
    return 0;
}

uint16_t get_address(){
  gpio_put(P_OUT_nALOE,1);
  gpio_put(P_OUT_nAHOE,0);
  uint16_t address = (gpio_get_all() & DATA_MASK) >> 4;
  gpio_put(P_OUT_nAHOE,1);
  gpio_put(P_OUT_nALOE,0);
  return address | ((gpio_get_all() & DATA_MASK) >> P_IO_D0);


}

void init_pins(){
  // Start with the Input Pins
  //gpio_init_mask(0b011110011111111111111111111100);
  
  gpio_init(P_LED);
  gpio_init(P_IN_CLK);
  gpio_init(P_IN_nSLTSEL);
  gpio_init(P_IN_nCS12);
  gpio_init(P_IN_nCS2);
  gpio_init(P_IN_nCS1);
  gpio_init(P_OUT_nWAIT);
  gpio_init(SPI_MISO);
  gpio_init(SPI_CS);
  gpio_init(SPI_SCK);
  gpio_init(SPI_MOSI);
  
  gpio_init(P_OUT_nAHOE);
  gpio_init(P_OUT_nALOE);
  gpio_init(P_OUT_nDOE);
  gpio_init(P_OUT_nDOUT);
  gpio_init(P_IN_nREAD);
  gpio_init(P_IN_nWRITE);
  
  gpio_init(P_IO_D0);
  gpio_init(P_IO_D1);
  gpio_init(P_IO_D2);
  gpio_init(P_IO_D3);
  gpio_init(P_IO_D4);
  gpio_init(P_IO_D5);
  gpio_init(P_IO_D6);
  gpio_init(P_IO_D7);
}

void write_data(uint8_t data){
  uint32_t mask = ((1<<P_OUT_nDOE) | (1<<P_OUT_nAHOE)  | (1<<P_OUT_nALOE) | (1<<P_OUT_nDOUT) | (data << P_IO_D0)) | DATA_MASK;
  uint32_t gpio_data = (data << P_IO_D0) | ((0<<P_OUT_nDOE) | (1<<P_OUT_nAHOE)  | (1<<P_OUT_nALOE) | (0<<P_OUT_nDOUT));
  gpio_put_masked(mask, gpio_data);
}

void setup_data_pins_for_read(){
  gpio_set_dir_in_masked(DATA_MASK);
  gpio_put(P_OUT_nDOUT, 1);
}

void setup_data_pins_for_write(){
  gpio_set_dir_out_masked(DATA_MASK);
  gpio_put(P_OUT_nDOUT, 0);
}
void setup_control_pins(){  
  gpio_set_dir(P_IN_nCS1, GPIO_IN);
  gpio_set_dir(P_IN_nCS2, GPIO_IN);
  gpio_set_dir(P_IN_nCS12, GPIO_IN);
  gpio_set_dir(P_IN_nREAD, GPIO_IN);
  gpio_set_dir(P_IN_nWRITE, GPIO_IN);
  gpio_set_dir(P_IN_nSLTSEL, GPIO_IN);
  gpio_set_dir(P_IN_CLK, GPIO_IN);
  gpio_set_dir(P_OUT_nDOE, GPIO_OUT);
  gpio_set_dir(P_OUT_nAHOE, GPIO_OUT);
  gpio_set_dir(P_OUT_nALOE, GPIO_OUT);
  gpio_set_dir(P_OUT_nDOUT, GPIO_OUT);
  gpio_set_dir(P_OUT_nWAIT, GPIO_OUT);
  gpio_set_dir(P_LED, GPIO_OUT);
  gpio_put(P_OUT_nDOUT, 1);
  gpio_put(P_OUT_nDOE, 1);
  gpio_put(P_OUT_nAHOE,1);
  gpio_put(P_OUT_nALOE, 1);
  gpio_put(P_OUT_nWAIT,1);

}

