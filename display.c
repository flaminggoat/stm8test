#include "stm8lib/stm8s103.h"
#include "stm8lib/stm8_spi.h"

#define ILI_ODR PC_ODR
#define ILI_A0  (1 << 4)
#define ILI_CS  (1 << 3)

#define ILI_WIDTH (128)
#define ILI_HEIGHT (128)

static inline void spi_setup(void)
{

    PC_DDR |= (1 << 5) | (1 << 6); // configure PC4, 5, 6 as output
    PC_CR1 |= (1 << 5) | (1 << 6); // push-pull mode

    stm8_spi_set_cr2(
        STM8_SPI_BDM_DISABLE,
        STM8_SPI_BD_INPUT,
        STM8_SPI_CRC_DISABLE,
        STM8_SPI_BUFNEXT,
        STM8_SPI_RXTX,
        STM8_SPI_SSM_ENABLE,
        STM8_SPI_SSI_MASTER);

    stm8_spi_set_cr1(
        STM8_SPI_MSBFIRST,
        STM8_SPI_ENABLE,
        STM8_SPI_BR_DIV2,
        STM8_SPI_MASTER,
        STM8_SPI_CPOLCPH00);
}

void ili_fill_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t c)
{
	uint8_t buf[8];

	ILI_ODR &= ~ILI_CS;

	buf[0] = 0x2A;
	ILI_ODR &= ~ILI_A0;
	stm8_spi_sendrecv(buf, 0, 1);
	ILI_ODR |= ILI_A0;

	buf[0] = 0;
	buf[1] = x1;
	buf[2] = 0;
	buf[3] = x2;
	stm8_spi_sendrecv(buf, 0, 4);

	buf[0] = 0x2b;
	ILI_ODR &= ~ILI_A0;
	stm8_spi_sendrecv(buf, 0, 1);
	ILI_ODR |= ILI_A0;

	buf[0] = 0;
	buf[1] = y1;
	buf[2] = 0;
	buf[3] = y2;
	stm8_spi_sendrecv(buf, 0, 4);

	buf[0] = 0x2c;
	ILI_ODR &= ~ILI_A0;
	stm8_spi_sendrecv(buf, 0, 1);
	ILI_ODR |= ILI_A0;

	buf[0] = (uint8_t)(c >> 8);
	buf[1] = (uint8_t)(c & 0xff);
	for(uint16_t i=0, end=((x2-x1+1)*(y2-y1+1)); i<end; ++i)
	{
		stm8_spi_sendrecv(buf, 0, 2);
	}
	
    ILI_ODR |= ILI_CS;
}

void ili_cmd(uint8_t cmd, uint8_t * data, uint8_t length)
{
	ILI_ODR &= ~ILI_A0;
	ILI_ODR &= ~ILI_CS;
	stm8_spi_sendrecv(&cmd, 0, 1);
	ILI_ODR |= ILI_CS;
	if(length)
	{
		ILI_ODR |= ILI_A0;
		ILI_ODR &= ~ILI_CS;
		stm8_spi_sendrecv(data, 0, length);
		ILI_ODR |= ILI_CS;
	}
}

void ili_init(void)
{
	static const uint8_t set_default_gamma[] = {0x04};
	static const uint8_t set_frame_rate[] = {0x0e, 0x10};
	static const uint8_t set_vrh1[] = {0x08, 0x00};
	static const uint8_t set_bt[] = {0x05};
	static const uint8_t set_vmh[] = {0x38,0x40};
	static const uint8_t set_color[] = {0x05};
	static const uint8_t set_rgb[] = {0xc8};
	static const uint8_t set_col_addr[] = {0,0,0,ILI_WIDTH};
	static const uint8_t set_page_addr[] = {0,0,0,ILI_HEIGHT};
	static const uint8_t display_inv[] = {0};
	static const uint8_t gamma_bit[] = {1};
	static const uint8_t gamma_map1[] = {0x3f,0x22,0x20,0x30,0x29,0x0c,0x4e,0xb7,0x3c,0x19,0x22,0x1e,0x02,0x01,0x00};
	static const uint8_t gamma_map2[] = {0x00,0x1b,0x1f,0x0f,0x16,0x13,0x31,0x84,0x43,0x06,0x1d,0x21,0x3d,0x3e,0x3f};

	ILI_ODR |= ILI_A0 | ILI_CS;
	PC_DDR |= ILI_A0 | ILI_CS;
    PC_CR1 |= ILI_A0 | ILI_CS;

	spi_setup();
	ili_cmd(0x01, 0, 0); //reset
	ili_cmd(0x11, 0, 0); //exit sleep

	ili_cmd(0x26, set_default_gamma, sizeof(set_default_gamma)); //Set Default Gamma
	ili_cmd(0xB1, set_frame_rate, sizeof(set_frame_rate)); //Set Frame Rate
	ili_cmd(0xC0, set_vrh1, 2); //Set VRH1[4:0] & VC[2:0] for VCI1 & GVDD
	ili_cmd(0xC1, set_bt, 1); //Set BT[2:0] for AVDD & VCL & VGH & VGL
	ili_cmd(0xC5, set_vmh, 2); //Set VMH[6:0] & VML[6:0] for VOMH & VCOML

	ili_cmd(0x3a, set_color, sizeof(set_color)); //Set Color Format, 5=16 bit,3=12 bit
	ili_cmd(0x36, set_rgb, sizeof(set_rgb)); //RGB

	ili_cmd(0x2A, set_col_addr, sizeof(set_col_addr)); //Set Column Address
	ili_cmd(0x2B, set_page_addr, sizeof(set_page_addr)); //Set Page Address

	ili_cmd(0xB4, display_inv, sizeof(display_inv)); // display inversion

	ili_cmd(0xf2, gamma_bit, sizeof(gamma_bit)); //Enable Gamma bit
	ili_cmd(0xE0, gamma_map1, sizeof(gamma_map1)); 
	ili_cmd(0xE1, gamma_map2, sizeof(gamma_map2));

	ili_cmd(0x29,0, 0); // Display On
	ili_cmd(0x2C, 0, 0); // reset frame ptr      

	ili_fill_rect( 0, 0, 128, 128, 0x0000);
}