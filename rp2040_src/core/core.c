#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "boards/pico.h"
#include "hardware/gpio.h"
#include "includes/config.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "sd_card.h"
#include "ff.h"
#include "includes/fs/fs.h"
#include "includes/control/control.h"
#include "includes/address_bus/address_bus.h"


__time_critical_func(main_loop)(uint16_t start_address_high, char *file_buffer){
    uint16_t address = 0;
    uint16_t offset_address = 0;
    uint8_t data = 0;
    while (true) {
        if(gpio_get(PIN_nCS1)==0 && gpio_get(PIN_nSLTSEL)==0){
            gpio_put(POUT_nDOE,1);
            control_read_address(&address);
            offset_address = address - start_address_high;
            data = file_buffer[offset_address];
            control_output_data(data);       
            gpio_put(POUT_nDOE,gpio_get(PIN_nREAD));   
            //printf("Putting Data 0x%02X at 0x%04X \n", data, address);
        } else {
            gpio_put(POUT_nDOE, 1);
        }
        //puts()
    }
}


bool led_state=false;

void sltsel_callback(uint gpio, uint32_t events) {

    led_state = !led_state;
    gpio_put(PICO_DEFAULT_LED_PIN, led_state);
    gpio_put(28, led_state);
}

int main()
{
    stdio_init_all();

    gpio_init(28);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_init(2);
    gpio_set_dir(2, false);
    gpio_set_dir(28, true);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_FALL, true, sltsel_callback);
    while (true) {
        
	//       sleep_ms(50);
        //gpio_put(PICO_DEFAULT_LED_PIN, 0);
	//gpio_put(28, 0);
	//sleep_ms(50);
    }
    return 0;    
    control_init_state();

    set_sys_clock_khz(CONFIG_SYSCLK * 1000, true);
    

    puts("Starting Run");

    FRESULT fr;
    FATFS fs;
    FIL fil;
    UINT file_size=0;
    int ret;
    char file_buffer[65536];
    memset(file_buffer, 0, sizeof file_buffer);
    char rom_check[2];
    uint16_t rom_start_address;
    char tank[] = "Tank Battalion (1984)(Namcot)(JP).rom";
    printf("Loading %s", tank);
     // Initialize SD card
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }
    // Mount drive
    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        while (true);
    }

    fr = f_open(&fil, tank, FA_READ);
    if (fr != FR_OK){
        printf("ERROR: Could not open file\r\n");
        while (true);
    }
    file_size = f_size(&fil);
    f_read(&fil, &file_buffer, f_size(&fil), NULL);
    printf("", file_size);
    memcpy(&rom_check,&file_buffer,2);
    uint16_t start_address_high = (uint16_t)file_buffer[3]<<8;
    uint16_t start_address_low = (uint16_t)file_buffer[2];
    
    rom_start_address = start_address_high + start_address_low;
    // Unmount drive
    f_unmount("0:");

    control_deassert_wait();



    
    // Loop forever doing nothing
    uint16_t upper_limit = start_address_high + file_size;
    
    // main_loop(start_address_high, &file_buffer);

    address_bus_init();
    address_bus_loop();

    

    return 0;
}


