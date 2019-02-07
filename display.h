#ifndef H_DISPLAY
#define H_DISPLAY

void ili_cmd(uint8_t cmd, uint8_t * data, uint8_t length);
void ili_init(void);
void ili_fill_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t c);

#endif