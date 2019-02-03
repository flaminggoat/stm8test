#ifndef H_STM8_HELPER
#define H_STM8_HELPER

#include <stdint.h>

#define STM8_ASSERT(expr) \
    if (!(expr))          \
    stm8_assert_failed(__FILE__, __LINE__)

void stm8_assert_failed(const char *filename, int line);
void stm8_delay_ms(uint16_t ms);

#endif