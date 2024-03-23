#include "ssd1306.h"




const char SSD1306_INIT_SEQUENCE[] = {
    SSD1306_SET_DISP_REG | 0x00, SSD1306_SET_MEM_ADDR_REG, 0x00,
    SSD1306_SET_DISP_START_LINE_REG | 0x00, SSD1306_SET_SEG_REMAP_REG | 0x01,
    SSD1306_SET_MUX_RATIO_REG, 0xFF, SSD1306_SET_COM_OUT_DIR_REG | 0x08,
    SSD1306_SET_DISP_OFFSET_REG, 0x00, SSD1306_SET_COM_PIN_CFG_REG, 0xFF,
     
};



void SSD1305_framebuffer_fill(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                              char value) {
    
  unsigned int buffer_size = sizeof(&framebuffer->buffer) / sizeof(char);
  char write_value = 0;
  
  if (value > 0) {
      write_value = 0xFF;
  }
  for (int i = 0; i < buffer_size; i++) {
      framebuffer->buffer[i]=write_value;
  }
}



void SSD1306_framebuffer_pixel(SSD1306_FrameBuffer_Mono_VLSB *framebuffer,
                               unsigned int x, unsigned int y, char value) {

  unsigned int buffer_size = sizeof(&framebuffer->buffer) / sizeof(char);

  // Need to consider that given an x and y, a particular vertical slice will be
  // hit, we can't just go to buffer[x,y]

  unsigned int y_slice = y / 8;
  unsigned int y_slice_offset = y % 8;


}


unsigned int
SSD1306_framebuffer_get_pages(SSD1306_FrameBuffer_Mono_VLSB *framebuffer) {
    return framebuffer->height/8;
    
}
