#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>

// Base address
#define TIM2_BASE       (0x40000000UL) 
#define TIM3_BASE       (0x40000400UL) 
#define TIM4_BASE       (0x40000800UL) 

// Timer register structure
typedef struct {
    volatile uint32_t CR1;      // 0x00
    volatile uint32_t CR2;      // 0x04
    volatile uint32_t SMCR;     // 0x08
    volatile uint32_t DIER;     // 0x0C
    volatile uint32_t SR;       // 0x10
    volatile uint32_t EGR;      // 0x14
    volatile uint32_t CCMR1;    // 0x18
    volatile uint32_t CCMR2;    // 0x1C
    volatile uint32_t CCER;     // 0x20
    volatile uint32_t CNT;      // 0x24
    volatile uint32_t PSC;      // 0x28
    volatile uint32_t ARR;      // 0x2C
    volatile uint32_t RCR;      // 0x30 (n?u có, TIM1/TIM8 advanced)
    volatile uint32_t CCR1;     // 0x34
    volatile uint32_t CCR2;     // 0x38
    volatile uint32_t CCR3;     // 0x3C
    volatile uint32_t CCR4;     // 0x40
    volatile uint32_t DCR;      // 0x48
    volatile uint32_t DMAR;     // 0x4C
} TIM_TypeDef;

#define TIM1_BASE       (0x40012C00UL)
#define TIM1 ((TIM_TypeDef*) TIM1_BASE)

// Pointers
#define TIM2 ((TIM_TypeDef*) TIM2_BASE)
#define TIM3 ((TIM_TypeDef*) TIM3_BASE)
#define TIM4 ((TIM_TypeDef*) TIM4_BASE)

// APIs
void TIM_Init_IT(TIM_TypeDef *TIMx, uint16_t psc, uint16_t arr, uint8_t irq_ch);
void TIM_IRQHandler(TIM_TypeDef *TIMx, void (*callback)(void));
void delay_ms(TIM_TypeDef *TIMx, uint32_t ms);

#endif
