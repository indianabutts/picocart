#include <stdio.h>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "test_rom.h"
#include "add_sm.pio.h"
// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi1
#define PIN_MISO 8
#define PIN_CS   8
#define PIN_SCK  10
#define PIN_MOSI 11
#define PIN_D0  0
#define PIN_D1 1
#define PIN_D2 2
#define PIN_D3 3
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7
#define PIN_nAHOE 12
#define PIN_nALOE 13
#define PIN_nDOE 14
#define PIN_nDOUT 16
#define PIN_nCS1 17
#define PIN_nCS2 18
#define PIN_nCS12 19
#define PIN_nSLTSEL 20
#define PIN_nREAD 21
#define PIN_nWRITE 22
#define PIN_CLK 26

#define P_OUT_nAHOE 12
#define P_OUT_nALOE 13
#define P_OUT_nDOE 14
#define P_OUT_nDOUT 15
#define P_IN_nREAD 16
#define P_IN_nWRITE 17




void setup_control_pins();
void setup_data_pins_for_write();
void setup_data_pins_for_read();
void write_data(uint8_t data);
void init_pins();
uint16_t get_address();

void irq_handler(uint gpio, uint32_t event_mask){
  //uint8_t gpio_value = gpio_get_all() & 0x000000FF;
    bool nRead = gpio_get(PIN_nREAD);
    bool nSLTSEL = gpio_get(PIN_nSLTSEL);
    //if(!nRead && !nSLTSEL){
      uint16_t address = get_address();
      uint8_t current_byte = romdata[address-0x4000];
      write_data(current_byte);
      printf("ADDRESS: %x %x\n", address, current_byte);
      //}
    setup_data_pins_for_read();
  //printf("GPIO VALUE: %x\n", gpio_value);
}

void dummy_handler(uint gpio, uint32_t event_mask) {
  int test = 0;
  for(int i =0; i < 100; i ++){
    test ++;
    if(test>5){
      printf("%i\n",test);
    }
  }
}

int main()
{
    stdio_init_all();
    init_pins();
    setup_control_pins();

    // SPI initialisation. This example will use SPI at 1MHz.
    //spi_init(SPI_PORT, 1000*1000);
    //gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    //gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    //gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    //gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    //
    //// Chip select is active-low, so we'll initialise it to a driven-high state
    //gpio_set_dir(PIN_CS, GPIO_OUT);
    //gpio_put(PIN_CS, 1);

    // This test, we will use the tank batallion data above so we can forget about SD for now
    // Tank BAtallion is 8kb and uses /CS1 which is GPIO17
    // We also want to watch /SLTSEL (GPIO20) & /READ (GPIO21)
    
    //clock_t startTime = clock();
    //unsigned int romsize = 8192;
    //unsigned int address = 0;
    //while(address < romsize){
    //  uint8_t current_data = data[address];
    //  //printf("** Address : %x", address);
    //  //printf("   Data: %x\n",current_data);
    //  address ++;
    //  //sleep_ms(10);
    //}

    sleep_ms(1000);
    printf("Starting new run");
    //clock_t endTime=clock();
    //double executionTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
    gpio_set_irq_enabled_with_callback(PIN_nCS1, GPIO_IRQ_EDGE_FALL, true, &dummy_handler);
    while(true){
      sleep_ms(1000);
      // bool nRead = gpio_get(PIN_nREAD);
      // bool nSLTSEL = gpio_get(PIN_nSLTSEL);
      // bool nCS1 = gpio_get(PIN_nCS1);
      // if(!nRead && !nSLTSEL %% !nCS1){
      //	 uint16_t address = get_address();
      //	 uint8_t current_byte = romdata[address-0x4000];
      //	 write_data(current_byte);
      //	 printf("ADDRESS: %x %x\n", address, current_byte);
      //	 setup_data_pins_for_read();
      // }
     
    }
    
    return 0;
}

void init_pins(){
  // Start with the Input Pins
  gpio_init_mask(0b000100011111110111111111111111);
}


uint16_t get_address(){
  setup_data_pins_for_read();
  uint32_t mask = (1<<PIN_nDOE) | (1<<PIN_nAHOE)  | (1<<PIN_nALOE) | (1<<PIN_nDOUT);

  uint32_t data = (1<<PIN_nDOE) | (1<<PIN_nAHOE)  | (1<<PIN_nALOE) | (1<<PIN_nDOUT);
  gpio_set_mask(mask);

  gpio_put(PIN_nALOE, false);
  
  uint16_t low_address = (uint16_t)(gpio_get_all() & 0x000000FF);
  
  data = (1<<PIN_nDOE) | (0<<PIN_nAHOE)  | (1<<PIN_nALOE) | (1<<PIN_nDOUT);

  gpio_set_mask(mask);

  gpio_put(PIN_nAHOE, false);
  
  uint16_t upper_address= (uint16_t)(gpio_get_all() & 0x000000FF);
  data = (1<<PIN_nDOE) | (1<<PIN_nAHOE)  | (1<<PIN_nALOE) | (1<<PIN_nDOUT);
  gpio_put_masked(mask, data);
  return upper_address | low_address;
}

void write_data(uint8_t data){
  uint32_t mask = ((1<<PIN_nDOE) | (1<<PIN_nAHOE)  | (1<<PIN_nALOE) | (1<<PIN_nDOUT)) | 0x000000FF;
  uint32_t gpio_data = data | ((0<<PIN_nDOE) | (1<<PIN_nAHOE)  | (1<<PIN_nALOE) | (0<<PIN_nDOUT));
}

void setup_data_pins_for_read(){
  //gpio_set_dir_in_masked(0x000000FF)
  gpio_set_dir(PIN_D0, GPIO_IN);
  gpio_set_dir(PIN_D1, GPIO_IN);
  gpio_set_dir(PIN_D2, GPIO_IN);
  gpio_set_dir(PIN_D3, GPIO_IN);
  gpio_set_dir(PIN_D4, GPIO_IN);
  gpio_set_dir(PIN_D5, GPIO_IN);
  gpio_set_dir(PIN_D6, GPIO_IN);
  gpio_set_dir(PIN_D7, GPIO_IN);
  gpio_put(PIN_nDOUT, 1);
}

void setup_data_pins_for_write(){
  gpio_set_dir_out_masked(0x000000FF);
  gpio_put(PIN_nDOUT, 0);
}
void setup_control_pins(){  
  gpio_set_dir(PIN_nCS1, GPIO_IN);
  gpio_set_dir(PIN_nCS2, GPIO_IN);
  gpio_set_dir(PIN_nCS12, GPIO_IN);
  gpio_set_dir(PIN_nREAD, GPIO_IN);
  gpio_set_dir(PIN_nWRITE, GPIO_IN);
  gpio_set_dir(PIN_nSLTSEL, GPIO_IN);
  gpio_set_dir(PIN_CLK, GPIO_IN);
  gpio_set_dir(PIN_nDOE, GPIO_OUT);
  gpio_set_dir(PIN_nAHOE, GPIO_OUT);
  gpio_set_dir(PIN_nALOE, GPIO_OUT);
  gpio_set_dir(PIN_nDOUT, GPIO_OUT);
  gpio_put(PIN_nDOUT, 1);
  gpio_put(PIN_nDOE, 1);
  gpio_put(PIN_nAHOE,1);
  gpio_put(PIN_nALOE, 1);

}

