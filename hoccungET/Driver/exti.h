#ifndef __exti_h
#define __exti_h

#include "type.h"
#include "afio.h"
#include "gpio.h"
#include "rcc.h"


#define EXTI_RISING_MODE       0x00
#define EXTI_FALLING_MODE      0x01
#define EXTI_BOTH_MODE         0x02

#define   NVIC_ISER0   *((uint32_t *)(0xE000E100))
#define   NVIC_ISER1   *((uint32_t *)(0xE000E104))

typedef struct {
    __32BIT IMR;
    __32BIT EMR;
    __32BIT RTSR;
    __32BIT FTSR;
    __32BIT SWIER;
    __32BIT PR;
}EXTI_Typedef;

#define EXTI_ADD_BASE			0x40010400UL
#define EXTI ((volatile EXTI_Typedef *)EXTI_ADD_BASE)
	
void EXTI_INIT(volatile GPIO_Typedef *GPIOx,volatile uint16_t gpio_pin, uint8_t mode);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

uint8_t get_pin_number(uint16_t GPIO_PIN);
void do_somethingIT0();
void do_somethingIT1();
void do_somethingIT2();
void do_somethingIT3();
void do_somethingIT4();
void do_somethingIT5();
void do_somethingIT6();
void do_somethingIT7();
void do_somethingIT8();
void do_somethingIT9();
void do_somethingIT10();
void do_somethingIT11();
void do_somethingIT12();
void do_somethingIT13();
void do_somethingIT14();
void do_somethingIT15();

void NVIC_UART_En(void);
void NVIC_USB_En(void);
#endif

