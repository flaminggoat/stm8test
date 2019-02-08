#ifndef H_DISPLAY
#define H_DISPLAY

void ili_cmd(uint8_t cmd, uint8_t * data, uint8_t length);
void ili_init(void);
void ili_fill_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t c);
void ili_set_pixel(uint8_t x, uint8_t y, uint16_t color);
void ili_draw_char(uint8_t x, uint8_t y, uint8_t scale, uint16_t color, char c);
void ili_draw_string(uint8_t x, uint8_t y, uint8_t scale, uint16_t color, const char * str);

#endif