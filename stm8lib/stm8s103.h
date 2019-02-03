#ifndef H_STM8S103
#define H_STM8S103

#define _SFR_(mem_addr)     (*(volatile unsigned char *)(0x5000 + (mem_addr)))

//ISR
#define TIM1_ISR 11 
#define TIM1_CC_ISR 12 
#define TIM4_ISR 23

// PORT A
#define PA_ODR      _SFR_(0x00)
#define PA_IDR		_SFR_(0x01)
#define PA_DDR      _SFR_(0x02)
#define PA_CR1      _SFR_(0x03)
#define PA_CR2      _SFR_(0x04)

// PORT B
#define PB_ODR      _SFR_(0x05)
#define PB_IDR		_SFR_(0x06)
#define PB_DDR      _SFR_(0x07)
#define PB_CR1      _SFR_(0x08)
#define PB_CR2      _SFR_(0x09)

// PORT C
#define PC_ODR      _SFR_(0x0A)
#define PC_IDR		_SFR_(0x0B)
#define PC_DDR      _SFR_(0x0C)
#define PC_CR1      _SFR_(0x0D)
#define PC_CR2      _SFR_(0x0E)

// PORT D
#define PD_ODR      _SFR_(0x0F)
#define PD_IDR		_SFR_(0x10)
#define PD_DDR      _SFR_(0x11)
#define PD_CR1      _SFR_(0x12)
#define PD_CR2      _SFR_(0x13)

// CLK
#define CLK_CMSR	_SFR_(0xC3)
#define CLK_SWR		_SFR_(0xC4)
#define CLK_CKDIVR	_SFR_(0xC6)

// TIM 1
#define TIM1_CR1	_SFR_(0x250)
#define TIM1_CR2	_SFR_(0x251)
#define TIM1_SMCR	_SFR_(0x252)
#define TIM1_ETR	_SFR_(0x253)
#define TIM1_IER	_SFR_(0x254)
#define TIM1_SR1	_SFR_(0x255)
#define TIM1_SR2	_SFR_(0x256)
#define TIM1_EGR	_SFR_(0x257)
#define TIM1_CCMR1	_SFR_(0x258)
#define TIM1_CCMR2	_SFR_(0x259)
#define TIM1_CCMR3	_SFR_(0x25A)
#define TIM1_CCMR4	_SFR_(0x25B)
#define TIM1_CCER1	_SFR_(0x25C)
#define TIM1_CCER2	_SFR_(0x25D)
#define TIM1_CNTRH	_SFR_(0x25E)
#define TIM1_CNTRL	_SFR_(0x25F)
#define TIM1_PSCRH	_SFR_(0x260)
#define TIM1_PSCRL	_SFR_(0x261)
#define TIM1_ARRH	_SFR_(0x262)
#define TIM1_ARRL	_SFR_(0x263)
#define TIM1_RCR	_SFR_(0x264)
#define TIM1_CCR1H	_SFR_(0x265)
#define TIM1_CCR1L	_SFR_(0x266)
#define TIM1_CCR2H	_SFR_(0x267)
#define TIM1_CCR2L	_SFR_(0x268)
#define TIM1_CCR3H	_SFR_(0x269)
#define TIM1_CCR3L	_SFR_(0x26A)
#define TIM1_CCR4H	_SFR_(0x26B)
#define TIM1_CCR4L	_SFR_(0x26C)
#define TIM1_BKR	_SFR_(0x26D)
#define TIM1_DTR	_SFR_(0x26E)
#define TIM1_OISR	_SFR_(0x26F)

// TIM 4
#define TIM4_CR1	_SFR_(0x340)
#define TIM4_IER	_SFR_(0x343)
#define TIM4_SR		_SFR_(0x344)
#define TIM4_EGR	_SFR_(0x345)
#define TIM4_CNTR	_SFR_(0x346)
#define TIM4_PSCR	_SFR_(0x347)
#define TIM4_ARR	_SFR_(0x348)

#define TIM4_IER_UIE (1 << 0)
#define TIM4_IER_TIE (1 << 6)
#define TIM4_SR_UIF (1 << 0)

#endif