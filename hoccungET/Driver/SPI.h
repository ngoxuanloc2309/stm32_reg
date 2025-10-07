#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>
#include "gpio.h"
#include "rcc.h"

// ================= SPI Register Map =================
typedef struct {
    volatile uint32_t CR1;      // 0x00
    volatile uint32_t CR2;      // 0x04
    volatile uint32_t SR;       // 0x08
    volatile uint32_t DR;       // 0x0C
    volatile uint32_t CRCPR;    // 0x10
    volatile uint32_t RXCRCR;   // 0x14
    volatile uint32_t TXCRCR;   // 0x18
    volatile uint32_t I2SCFGR;  // 0x1C
    volatile uint32_t I2SPR;    // 0x20
} SPI_Typedef;

// ================= Base address =====================
#define SPI1 ((SPI_Typedef*)0x40013000UL)
#define SPI2 ((SPI_Typedef*)0x40003800UL)

// ================= SR Register Flags ================
#define SPI_SR_RXNE   (1 << 0)   // Receive buffer not empty
#define SPI_SR_TXE    (1 << 1)   // Transmit buffer empty
#define SPI_SR_BSY    (1 << 7)   // Busy flag

// ================= CR1 Config Bits ==================
#define SPI_CR1_CPHA       (1 << 0)
#define SPI_CR1_CPOL       (1 << 1)
#define SPI_CR1_MSTR       (1 << 2)
#define SPI_CR1_BR_DIV2    (0 << 3)
#define SPI_CR1_BR_DIV4    (1 << 3)
#define SPI_CR1_BR_DIV8    (2 << 3)
#define SPI_CR1_BR_DIV16   (3 << 3)
#define SPI_CR1_BR_DIV32   (4 << 3)
#define SPI_CR1_BR_DIV64   (5 << 3)
#define SPI_CR1_BR_DIV128  (6 << 3)
#define SPI_CR1_BR_DIV256  (7 << 3)
#define SPI_CR1_SPE        (1 << 6)
#define SPI_CR1_LSBFIRST   (1 << 7)
#define SPI_CR1_SSI        (1 << 8)
#define SPI_CR1_SSM        (1 << 9)
#define SPI_CR1_RXONLY     (1 << 10)
#define SPI_CR1_DFF        (1 << 11)  // 0=8bit, 1=16bit

// ================== SPI Config Struct ===============
typedef struct {
    uint8_t CPOL;       // 0 = Low idle, 1 = High idle
    uint8_t CPHA;       // 0 = 1st edge, 1 = 2nd edge
    uint8_t BaudRate;   // BR[2:0] divider
    uint8_t LSBFirst;   // 0 = MSB first, 1 = LSB first
    uint8_t DataSize;   // 0 = 8-bit, 1 = 16-bit
} SPI_Config_t;

// ================= Function Prototypes ==============
void SPI_Init(SPI_Typedef *SPIx, SPI_Config_t *cfg,
              volatile GPIO_Typedef *PORT_SCK, uint16_t PIN_SCK,
              volatile GPIO_Typedef *PORT_MISO, uint16_t PIN_MISO,
              volatile GPIO_Typedef *PORT_MOSI, uint16_t PIN_MOSI,
              volatile GPIO_Typedef *PORT_CS,   uint16_t PIN_CS);

void SPI_ChipSelect(volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS, uint8_t state);
void SPI_Send(SPI_Typedef *SPIx, volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS, uint8_t data);
uint8_t SPI_Receive(SPI_Typedef *SPIx, volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS);
uint8_t SPI_TransmitReceive(SPI_Typedef *SPIx, volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS, uint8_t data);

#endif
