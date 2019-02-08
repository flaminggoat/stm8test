#include "stm8_spi.h"
#include "stm8_helper.h"
#include "stm8s103.h"

void stm8_spi_set_cr1(uint8_t lsbfirst, uint8_t enable, uint8_t baudrate, uint8_t master, uint8_t cpolcpha)
{
	STM8_ASSERT(lsbfirst == STM8_SPI_LSBFIRST || lsbfirst == STM8_SPI_MSBFIRST);
	STM8_ASSERT(enable == STM8_SPI_ENABLE || enable == STM8_SPI_DISABLE);
	STM8_ASSERT(baudrate == STM8_SPI_BR_DIV2 ||
				(baudrate >= STM8_SPI_BR_DIV4 && baudrate <= STM8_SPI_BR_DIV256));
	STM8_ASSERT(master == STM8_SPI_MASTER || master == STM8_SPI_SLAVE);
	STM8_ASSERT(cpolcpha >= STM8_SPI_CPOLCPH00 && cpolcpha <= STM8_SPI_CPOLCPH11);

	SPI_CR1 = lsbfirst | enable | baudrate | master | cpolcpha;
}

void stm8_spi_set_cr2(uint8_t bdm, uint8_t bdoe, uint8_t crc_en, uint8_t crcnext,
					  uint8_t rxonly, uint8_t ssm, uint8_t ssi)
{
	//TODO assert
	SPI_CR2 = bdm | bdoe | crc_en | crcnext | rxonly | ssm | ssi;
}

void stm8_spi_disable()
{
	if (SPI_CR2 & (STM8_SPI_BDM_ENABLE | STM8_SPI_RX_ONLY) == 0)
	{
		while(1);
	}
	// TODO other configurations
}

void stm8_spi_sendrecv(const uint8_t * send, uint8_t * recv, uint8_t length)
{
	uint8_t dummy_read;

	dummy_read = SPI_DR; // Empty recieve buffer

	for(;length > 0; --length)
	{
		SPI_DR = *send++;
		//while(!(SPI_SR & STM8_SPI_TXE)); // Ensure tx buffer is empty
		while(!(SPI_SR & STM8_SPI_RXNE));
		if(recv != 0)
		{
			*recv++ = SPI_DR;
		} else
		{
			dummy_read = SPI_DR;
		}
		
		
	}
}
