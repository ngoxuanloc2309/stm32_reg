#include "spi.h"

void SPI_Init(SPI_Typedef *SPIx, SPI_Config_t *cfg,
              volatile GPIO_Typedef *PORT_SCK, uint16_t PIN_SCK,
              volatile GPIO_Typedef *PORT_MISO, uint16_t PIN_MISO,
              volatile GPIO_Typedef *PORT_MOSI, uint16_t PIN_MOSI,
              volatile GPIO_Typedef *PORT_CS,   uint16_t PIN_CS)
{
    // ==== Enable Clock ====
    if (SPIx == SPI1) {
        RCC->APB2ENR.BITS.SPI1EN = 1;
    } else if (SPIx == SPI2) {
        RCC->APB1ENR.BITS.SPI2EN = 1;
    }

    // ==== GPIO Config ====
    GPIO_Config(PORT_SCK, PIN_SCK, GPIO_MODE_AF_PP);
    GPIO_Config(PORT_MISO, PIN_MISO, GPIO_MODE_INPUT_FLOATING);
    GPIO_Config(PORT_MOSI, PIN_MOSI, GPIO_MODE_AF_PP);
    GPIO_Config(PORT_CS,   PIN_CS, GPIO_MODE_OUTPUT_PP);

    // Set CS HIGH (not selected)
    GPIO_Write_Pin(PORT_CS, PIN_CS, 1);

    // ==== SPI Config ====
    SPIx->CR1 = 0; // Reset

    // Master mode
    SPIx->CR1 |= SPI_CR1_MSTR;

    // Baudrate
    SPIx->CR1 |= (cfg->BaudRate << 3);

    // CPOL & CPHA
    if (cfg->CPOL) SPIx->CR1 |= SPI_CR1_CPOL;
    if (cfg->CPHA) SPIx->CR1 |= SPI_CR1_CPHA;

    // Frame format
    if (cfg->LSBFirst) SPIx->CR1 |= SPI_CR1_LSBFIRST;

    // Data size
    if (cfg->DataSize) SPIx->CR1 |= SPI_CR1_DFF;

    // Software slave management (NSS high internally)
    SPIx->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    // Enable SPI
    SPIx->CR1 |= SPI_CR1_SPE;
}

// ==== Chip Select control ====
void SPI_ChipSelect(volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS, uint8_t state) {
    if (state) {
        GPIO_Write_Pin(PORT_CS, PIN_CS, 1); // Deselect
    } else {
        GPIO_Write_Pin(PORT_CS, PIN_CS, 0); // Select
    }
}

// ==== Send 1 byte ====
void SPI_Send(SPI_Typedef *SPIx, volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS, uint8_t data) {
    SPI_ChipSelect(PORT_CS, PIN_CS, 0);

    while (!(SPIx->SR & SPI_SR_TXE));  // Wait TX empty
    SPIx->DR = data;
    while (!(SPIx->SR & SPI_SR_RXNE)); // Wait RX not empty
    (void)SPIx->DR; // Dummy read to clear RXNE

    while (SPIx->SR & SPI_SR_BSY); // Wait until not busy

    SPI_ChipSelect(PORT_CS, PIN_CS, 1);
}

// ==== Receive 1 byte ====
uint8_t SPI_Receive(SPI_Typedef *SPIx, volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS) {
    uint8_t data;

    SPI_ChipSelect(PORT_CS, PIN_CS, 0);

    while (!(SPIx->SR & SPI_SR_TXE));
    SPIx->DR = 0xFF; // Dummy write

    while (!(SPIx->SR & SPI_SR_RXNE));
    data = SPIx->DR;

    while (SPIx->SR & SPI_SR_BSY);

    SPI_ChipSelect(PORT_CS, PIN_CS, 1);

    return data;
}

// ==== Send & Receive (Full Duplex) ====
uint8_t SPI_TransmitReceive(SPI_Typedef *SPIx, volatile GPIO_Typedef *PORT_CS, uint16_t PIN_CS, uint8_t data) {
    uint8_t received;

    SPI_ChipSelect(PORT_CS, PIN_CS, 0);

    while (!(SPIx->SR & SPI_SR_TXE));
    SPIx->DR = data;

    while (!(SPIx->SR & SPI_SR_RXNE));
    received = SPIx->DR;

    while (SPIx->SR & SPI_SR_BSY);

    SPI_ChipSelect(PORT_CS, PIN_CS, 1);

    return received;
}
