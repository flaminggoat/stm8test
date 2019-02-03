#include "stm8_helper.h"
#include "stm8s103.h"

uint32_t cpu_freq = 2000000;

void stm8_assert_failed(const char *filename, int line)
{
	volatile const char *_filename = filename;
	volatile int _line = line;
	// disable interrupts;
	__asm__("sim");

    PB_DDR |= (1 << 5); // configure PB5 as output
    PB_CR1 |= (1 << 5); // push-pull mode
	while (1)
	{
		PB_ODR ^= (1 << 5);
		stm8_delay_ms(200);
	}
}

void stm8_delay_ms(uint16_t ms)
{
	uint16_t i, ii;
	uint16_t ms_timer = (cpu_freq / 1800UL);
	for (i = 0; i < ms; ++i)
	{
		for (ii = 0; ii < ms_timer; ++ii)
		{
			__asm__("nop");
		}
	}
}

void stm8_define_cpu_freq(uint32_t freq)
{
	cpu_freq = freq;
}