#include <assert.h>
#include <string.h>
#include "hw_config.h"
#include "diskio.h" /* Declarations of disk functions */

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi1
#define PIN_MISO 8
#define PIN_CS   9
#define PIN_SCK  10
#define PIN_MOSI 11

static spi_t spis[] = {
    {
	.hw_inst = spi1,
	.miso_gpio = 8,
	.mosi_gpio = 11,
	.sck_gpio = 10,
	.baud_rate = 12500 * 1000
    }
};

static sd_card_t sd_cards[] = {
    {
	.pcName = "0:",
	.spi = &spis[0],
	.ss_gpio = 9,
	.use_card_detect = false
    }
};

size_t sd_get_num() { return count_of(sd_cards);}

sd_card_t *sd_get_by_num(size_t num) {
    assert(num <= sd_get_num());
    if (num <= sd_get_num()){
	return &sd_cards[num];
    } else {
	return NULL;
    }
}

size_t spi_get_num() { return count_of(spis); }
spi_t *spi_get_by_num(size_t num) {
    assert(num <= spi_get_num());
    if (num <= spi_get_num()) {
        return &spis[num];
    } else {
        return NULL;
    }
}
