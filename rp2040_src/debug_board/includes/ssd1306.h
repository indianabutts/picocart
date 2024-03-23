#ifndef MSX_DEBUG_SSD1306_H
#define MSX_DEBUG_SSD1306_H

#define SSD1306_SET_CONTRAST_REG     0x81
#define SSD1306_SET_ENTIRE_ON_REG    0xA4
#define SSD1306_SET_NORM_INV_REG     0xA6
#define SSD1306_SET_DISP_REG 0xAE
#define SSD1306_SET_MEM_ADDR_REG 0x20
#define SSD1306_SET_COL_ADDR_REG 0x21
#define SSD1306_SET_PAGE_ADDR_REG 0x22
#define SSD1306_SET_DISP_START_LINE_REG 0x40
#define SSD1306_SET_SEG_REMAP_REG 0xA0
#define SSD1306_SET_MUX_RATIO_REG 0xA8
#define SSD1306_SET_COM_OUT_DIR_REG 0xC0
#define SSD1306_SET_DISP_OFFSET_REG 0xD3
#define SSD1306_SET_COM_PIN_CFG_REG 0xDA
#define SSD1306_SET_DISP_CLK_DIV_REG 0xD5
#define SSD1306_SET_PRECHARGE_REG 0xD9
#define SSD1306_SET_VCOM_DESEL 0xDB
#define SSD1306_SET_CHARGE_PUMP 0x8D


// Vertical LSB Monochrome Framebuffer where bit 0 is closest to the top
// and each byte occupies 8 vertical pixels
typedef struct SSD1306_FrameBuffer_Mono_VLSB {
    char* buffer;
    unsigned int width;
    unsigned int height;
} SSD1306_FrameBuffer_Mono_VLSB;



unsigned int SSD1306_framebuffer_get_pages(SSD1306_FrameBuffer_Mono_VLSB *framebuffer);

// Fill the specified buffer with 1 if `value` is greater than 0
void SSD1306_framebuffer_fill(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                              char value);

// Set pixel specified by x,y if value >0, else unset
void SSD1306_framebuffer_pixel(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                               unsigned int x, unsigned int y, char value);

void SSD1306_framebuffer_hline(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                               unsigned int x, unsigned int y, unsigned int width, char value);

void SSD1306_framebuffer_vline(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                               unsigned int x, unsigned int y, unsigned int height, char value);

void SSD1306_framebuffer_line(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                              unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

void SSD1306_framebuffer_rect(SSD1306_FrameBuffer_Mono_VLSB *framebuffer, unsigned int x,
                              unsigned int y, unsigned int width, unsigned int height, char value,
                              char fill);


void SSD1306_framebuffer_text(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                              char *text, unsigned int x, unsigned int y, char value);

void SSD1306_i2c_write_cmd(char i2c_address, char command);

void SSD1306_i2c_write_data(char i2c_address, char *data);

void SSD1306_i2c_init(char address, char *cmd) {
    
}



#endif
