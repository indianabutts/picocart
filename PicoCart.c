#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "sd_card.h"
#include "ff.h"
#include "includes/fs/fs.h"


int main()
{
    FRESULT fr;
    FATFS fs;
    FIL fil;
    int ret;
    char buf[100];
    char filename[] = "tank2.txt";
    char tank[] = "Tank Battalion (1984)(Namcot)(JP).rom";
    stdio_init_all();
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
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }
    char tank_buf[256];
    f_read(&fil, &tank_buf, sizeof tank_buf, NULL);

    f_close(&fil);

    // Open file for writing ()
    fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }

    // Write something to file
    //ret = f_printf(&fil, tank_buf);
    ret = f_write(&fil, tank_buf, sizeof tank_buf, NULL);
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }


    // Close file
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Unmount drive
    f_unmount("0:");

    // Loop forever doing nothing
    while (true) {
        sleep_ms(1000);
    }


    

    return 0;
}
