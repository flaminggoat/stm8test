#ifndef H_STM8_TIMER
#define H_STM8_TIMER

#include <stdint.h>

#define  STM8_TIM1_FREQ_TO_PCSR(CLKFREQ, TIMFREQ) ((CLKFREQ)/(TIMFREQ) - 1) 

void stm8_tim1_set_pcsr(uint8_t tim, uint16_t pcsr);
void stm8_tim1235_set_arr(uint8_t tim, uint16_t arr);
void stm8_tim1235_set_ccr(uint8_t tim, uint8_t cc, uint16_t value);

#endif