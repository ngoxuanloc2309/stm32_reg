#include "timer.h"
#include "rcc.h"
#include "exti.h"   // d? dùng NVIC_ISERx

// Hàm kh?i t?o timer v?i ng?t
void TIM_Init_IT(TIM_TypeDef *TIMx, uint16_t psc, uint16_t arr, uint8_t irq_ch) {
    // B?t clock
    if(TIMx == TIM1) RCC->APB2ENR.BITS.TIM1EN = 1;   // TIM1 n?m trên APB2
    else if(TIMx == TIM2) RCC->APB1ENR.BITS.TIM2EN = 1;
    else if(TIMx == TIM3) RCC->APB1ENR.BITS.TIM3EN = 1;
    else if(TIMx == TIM4) RCC->APB1ENR.BITS.TIM4EN = 1;

    // C?u hình prescaler và auto-reload
    TIMx->PSC = psc;
    TIMx->ARR = arr;

    // Enable update interrupt
    TIMx->DIER |= (1<<0);

    // Clear flag
    TIMx->SR &= ~(1<<0);

    // Enable counter
    TIMx->CR1 |= (1<<0);

    // Enable NVIC
    if(irq_ch < 32) NVIC_ISER0 |= (1<<irq_ch);
    else NVIC_ISER1 |= (1<<(irq_ch-32));
}


// Hàm handler chung
void TIM_IRQHandler(TIM_TypeDef *TIMx, void (*callback)(void)) {
    if(TIMx->SR & (1<<0)) {
        callback();
        TIMx->SR &= ~(1<<0); // clear flag
    }
}

// Dùng timer d? delay
void delay_ms(TIM_TypeDef *TIMx, uint32_t ms){
    TIMx->PSC = 7999;     // 1ms tick (8MHz / 8000 = 1kHz)
    TIMx->ARR = ms;
    TIMx->CNT = 0;

    TIMx->CR1 |= (1<<0);   // Enable
    while(TIMx->CNT < ms);
    TIMx->CR1 &= ~(1<<0);  // Disable
    TIMx->CNT = 0;
}
