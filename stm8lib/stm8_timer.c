#include "stm8_timer.h"
#include "stm8_helper.h"
#include "stm8s103.h"

/**
 * @brief Set the prescaler of TIM1.
 * clk_freq/tim_freq - 1 = pcsr
 * 
 * @param pcsr 16 bit prescaler
 */
void stm8_tim1_set_pcsr(uint8_t tim, uint16_t pcsr)
{
	STM8_ASSERT( tim == 1 );

	TIM1_PSCRH = pcsr >> 8;
    TIM1_PSCRL = pcsr & 0xff;
}

/**
 * @brief Set the auto reload register of TIMx 
 * 
 * @param tim timer
 * @param arr auto reload value
 */
void stm8_tim1235_set_arr(uint8_t tim, uint16_t arr)
{
	STM8_ASSERT( tim >= 1 && tim <= 5 && tim != 4 );

	switch(tim)
	{
		case 1:
			TIM1_ARRH = arr >> 8;
    		TIM1_ARRL = arr & 0xff;
			break;
		// TODO: other timers
	}

}

void stm8_tim1235_set_ccr(uint8_t tim, uint8_t cc, uint16_t value)
{
	STM8_ASSERT( tim >= 1 && tim <= 5 && tim != 4 );

	switch(tim)
	{
		case 1:
			STM8_ASSERT( cc >= 1 && cc <= 4);
			switch(cc)
			{
				case 1:
					TIM1_CCR1H = value >> 8;
    				TIM1_CCR1L = value & 0xff;
					break;
				case 2:
					TIM1_CCR2H = value >> 8;
    				TIM1_CCR2L = value & 0xff;
					break;
				case 3:
					TIM1_CCR3H = value >> 8;
    				TIM1_CCR3L = value & 0xff;
					break;
				case 4:
					TIM1_CCR4H = value >> 8;
    				TIM1_CCR4L = value & 0xff;
					break;
			}
			break;
			
		case 2:
			break;
		// TODO: other timers
	}

}
