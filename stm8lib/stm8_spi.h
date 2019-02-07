#ifndef H_STM8_SPI
#define H_STM8_SPI

#include <stdint.h>
#include <stdbool.h>

// CR1 Register
#define STM8_SPI_LSBFIRST	(1 << 7)
#define STM8_SPI_MSBFIRST	(0 << 7)

#define STM8_SPI_ENABLE		(0x01 << 6)
#define STM8_SPI_DISABLE	(0x00 << 6)

#define STM8_SPI_BR_DIV2	(0x00 << 3)
#define STM8_SPI_BR_DIV4	(0x01 << 3)
#define STM8_SPI_BR_DIV8	(0x02 << 3)
#define STM8_SPI_BR_DIV16	(0x03 << 3)
#define STM8_SPI_BR_DIV32	(0x04 << 3)
#define STM8_SPI_BR_DIV64	(0x05 << 3)
#define STM8_SPI_BR_DIV128	(0x06 << 3)
#define STM8_SPI_BR_DIV256	(0x07 << 3)
#define STM8_SPI_BR_MASK	(0x07 << 3)

#define STM8_SPI_MASTER (1 << 2)
#define STM8_SPI_SLAVE  (0 << 2)

#define STM8_SPI_CPOLCPH00 (0x00)
#define STM8_SPI_CPOLCPH01 (0x01)
#define STM8_SPI_CPOLCPH10 (0x02)
#define STM8_SPI_CPOLCPH11 (0x03)

// CR2 Register
#define STM8_SPI_BDM_ENABLE (1 << 7)
#define STM8_SPI_BDM_DISABLE (0 << 7)

#define STM8_SPI_BD_OUTPUT (1 << 6)
#define STM8_SPI_BD_INPUT (0 << 6)

#define STM8_SPI_CRC_ENABLE (1 << 5)
#define STM8_SPI_CRC_DISABLE (0 << 5)

#define STM8_SPI_CRCNEXT (1 << 4)
#define STM8_SPI_BUFNEXT (0 << 4)

#define STM8_SPI_RX_ONLY (1 << 2)
#define STM8_SPI_RXTX (0 << 2)

#define STM8_SPI_SSM_ENABLE (1 << 1)
#define STM8_SPI_SSM_DISABLE (0 << 1)

#define STM8_SPI_SSI_MASTER (1)
#define STM8_SPI_SSI_SLAVE (0)

// Status register
#define STM8_SPI_BSY	(1 << 7)
#define STM8_SPI_OVR	(1 << 6)
#define STM8_SPI_MODF	(1 << 5)
#define STM8_SPI_CRCERR	(1 << 4)
#define STM8_SPI_WKUP	(1 << 3)
#define STM8_SPI_TXE	(1 << 1)
#define STM8_SPI_RXNE	(1 << 0)

void stm8_spi_set_cr1(uint8_t lsbfirst, uint8_t enable, uint8_t baudrate, uint8_t master, uint8_t cpolcpha);
void stm8_spi_set_cr2(uint8_t bdm, uint8_t bdoe, uint8_t crc_en, uint8_t crcnext,
					  uint8_t rxonly, uint8_t ssm, uint8_t ssi);
void stm8_spi_disable();
void stm8_spi_sendrecv(uint8_t * send, uint8_t * recv, uint8_t length);

#endif