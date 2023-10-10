#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "sd_card.h"
#include "ff.h"
#include "includes/fs/fs.h"
#include "includes/control/control.h"


__time_critical_func(main_loop)(uint16_t start_address_high, char *file_buffer){
    uint16_t address = 0;
    while (true) {
        if(gpio_get(PIN_nCS1)==0){
            gpio_put(POUT_nDOE,1);
            control_read_address(&address);
            control_output_data(file_buffer[address-start_address_high]);       
            gpio_put(POUT_nDOE,0);          
        } else {
            gpio_put(POUT_nDOE, 1);
        }
    }
}

int main()
{
    stdio_init_all();

    gpio_init_mask(CONTROL_GPIO_INIT_MASK);

    control_init_state();

    



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
    
    main_loop(start_address_high, &file_buffer);


    

    return 0;
}


