#ifndef __I2C_H
#define __I2C_H
#include <stdint.h>

#define I2C1_BASE     0x40005400


#define I2C_CR1    0x00
#define I2C_CR2    0x04
#define I2C_OAR1   0x08
#define I2C_OAR2   0x0C
#define I2C_DR     0x10
#define I2C_SR1    0x14
#define I2C_SR2    0x18
#define I2C_CCR    0x1C
#define I2C_TRISE  0x20

#define I2C1_CR1     *((volatile uint32_t*)(I2C1_BASE + I2C_CR1))
#define I2C1_CR2     *((volatile uint32_t*)(I2C1_BASE + I2C_CR2))
#define I2C1_OAR1    *((volatile uint32_t*)(I2C1_BASE + I2C_OAR1))
#define I2C1_OAR2    *((volatile uint32_t*)(I2C1_BASE + I2C_OAR2))
#define I2C1_DR      *((volatile uint32_t*)(I2C1_BASE + I2C_DR))
#define I2C1_SR1     *((volatile uint32_t*)(I2C1_BASE + I2C_SR1))
#define I2C1_SR2     *((volatile uint32_t*)(I2C1_BASE + I2C_SR2))
#define I2C1_CCR     *((volatile uint32_t*)(I2C1_BASE + I2C_CCR))
#define I2C1_TRISE   *((volatile uint32_t*)(I2C1_BASE + I2C_TRISE))

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Send_Addr(uint8_t addr, uint8_t rw);
uint8_t I2C_Send_Data(uint8_t data);
uint8_t I2C_Read_Data(uint8_t ack);

#endif