#include <stdint.h>
#include "stm8lib/stm8s103.h"
#include "stm8lib/stm8_timer.h"

#define F_CPU 16000000UL

#define LED_PIN 5 // PB5d

static inline void tim4_setup(void)
{
    // Set prescaler
    TIM4_PSCR = 12; // 2^15 = 32768
    // Set auto reload value
    TIM4_ARR = 0xff;
    // set interupt on update
    TIM4_IER |= TIM4_IER_UIE;
    // enable timer
    TIM4_CR1 |= 1;
}

void tim4_isr(void) __interrupt(TIM4_ISR)
{
    static unsigned char i = 0;
    static unsigned char x = 1;
    static unsigned char counting_down = 0;
    if (i++ > 100)
    {
        i = 0;

        x = counting_down ? x - 1 : x + 1;
        if (x == 50)
        {
            counting_down = 1;
        }
        if (x == 0)
        {
            counting_down = 0;
        }

        stm8_tim1235_set_ccr(1, 1, x);
    }
    TIM4_SR &= ~TIM4_SR_UIF;
}

static inline void tim1_setup(void)
{

    stm8_tim1_set_pcsr(1, 0x63f);
    stm8_tim1235_set_arr(1, 120);
    stm8_tim1235_set_ccr(1, 1, 0);

    // enable uie and cc1 interuppts
    TIM1_IER = 0b11;

    //enable timer
    TIM1_CR1 |= 0b1;
}

void tim1_isr(void) __interrupt(TIM1_ISR)
{
    // turn on led
    PB_ODR &= ~(1 << LED_PIN);
    //PB_ODR ^= (1 << LED_PIN);
    // clear uie interrupt flag
    TIM1_SR1 &= ~0b1;
}

void tim1_cc_isr(void) __interrupt(TIM1_CC_ISR)
{
    if (TIM1_SR1 & 0b10)
    {
        // turn off led
        PB_ODR |= (1 << LED_PIN);
    }

    // clear cc interrupt flags
    TIM1_SR1 &= ~0b11110;
}

void main()
{
    __asm__("rim"); //enable interrupts

    CLK_CKDIVR = 0x00; // Set clock scaler to div 1 (16MHz if using HSI)

    tim1_setup();
    tim4_setup();

    PB_ODR = (1 << LED_PIN);
    PB_DDR |= (1 << LED_PIN); // configure PB4 as output
    PB_CR1 |= (1 << LED_PIN); // push-pull mode

    while (1)
    {
        // wait for interrupt
        __asm__("wfi");
        /* toggle pin every 250ms */
        //PB_ODR ^= (1 << LED_PIN);
        //delay_ms(250);
    }
}
