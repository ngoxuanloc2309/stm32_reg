#include "exti.h"

uint8_t get_pin_number(uint16_t GPIO_PIN){
	uint8_t i;
	for(i=0; i<16; i++){
		if(GPIO_PIN & (1<<i)){
			return i;
		}
	}
	return 0xff;
}

void EXTI_INIT(volatile GPIO_Typedef *GPIOx,volatile uint16_t gpio_pin, uint8_t mode){
	uint8_t port_code;
	uint8_t pin;
	uint8_t offset;
	RCC_Enable_AFIO();
	
	pin = get_pin_number(gpio_pin);
	
	if(GPIOx == GPIOA){
		port_code = 0;
	}else
	if(GPIOx == GPIOB){
		port_code = 1;
	}else
	if(GPIOx == GPIOC){
		port_code = 2;
	}else{
		return;
	}
	
	offset = ((pin%4)*4);
	
	if(pin<4){
		//AFIO->EXTICR1.REG &= ~(0xF << offset);
		AFIO->EXTICR1.REG |= (port_code) << offset;
	}else if(pin<8){
		AFIO->EXTICR2.REG &= ~(0xF << offset);
		AFIO->EXTICR2.REG |= (port_code) << offset;
	}else if(pin<12){
		AFIO->EXTICR3.REG &= ~(0xF << offset);
		AFIO->EXTICR3.REG |= (port_code) << offset;
	}else{
		AFIO->EXTICR4.REG &= ~(0xF << offset);
		AFIO->EXTICR4.REG |= (port_code) << offset;
	}
	
	EXTI->IMR.REG |= (1<<pin);
	
	if(pin<5){
		NVIC_ISER0 |= (1<<(6+pin));
	}else if(pin<10){
		NVIC_ISER0 |= (1<<23);
	}else{
		NVIC_ISER1 |= (1<<(40-32));
	}

	if(mode == EXTI_RISING_MODE){
		EXTI->RTSR.REG |= (1<<pin);
		EXTI->FTSR.REG &= (~(1<<pin));
	}else if(mode == EXTI_FALLING_MODE){
		EXTI->FTSR.REG |= (1<<pin);
		EXTI->RTSR.REG &= (~(1<<pin));
	}else{
		EXTI->RTSR.REG |= (1<<pin);
		EXTI->FTSR.REG |= ((1<<pin));
	}
}

__attribute__((weak)) void do_somethingIT0(void) {}
__attribute__((weak)) void do_somethingIT1(void) {}
__attribute__((weak)) void do_somethingIT2(void) {}
__attribute__((weak)) void do_somethingIT3(void) {}
__attribute__((weak)) void do_somethingIT4(void) {}
__attribute__((weak)) void do_somethingIT5(void) {}
__attribute__((weak)) void do_somethingIT6(void) {}
__attribute__((weak)) void do_somethingIT7(void) {}
__attribute__((weak)) void do_somethingIT8(void) {}
__attribute__((weak)) void do_somethingIT9(void) {}
__attribute__((weak)) void do_somethingIT10(void) {}		
__attribute__((weak)) void do_somethingIT11(void) {}
__attribute__((weak)) void do_somethingIT12(void) {}
__attribute__((weak)) void do_somethingIT13(void) {}
__attribute__((weak)) void do_somethingIT14(void) {}
__attribute__((weak)) void do_somethingIT15(void) {}

void EXTI0_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT0) {
		do_somethingIT0();
		EXTI->PR.REG |= (1 << 0);
	}
}

void EXTI1_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT1) {
		do_somethingIT1();
		EXTI->PR.REG |= (1 << 1);
	}
}

void EXTI2_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT2) {
		do_somethingIT2();
		EXTI->PR.REG |= (1 << 2);
	}
}

void EXTI3_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT3) {
		do_somethingIT3();
		EXTI->PR.REG |= (1 << 3);
	}
}

void EXTI4_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT4) {
		do_somethingIT4();
		EXTI->PR.REG |= (1 << 4);
	}
}

void EXTI9_5_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT5) {
		do_somethingIT5();
		EXTI->PR.REG |= (1 << 5);
	}
	if(EXTI->PR.BITS.BIT6) {
		do_somethingIT6();
		EXTI->PR.REG |= (1 << 6);
	}
	if(EXTI->PR.BITS.BIT7) {
		do_somethingIT7();
		EXTI->PR.REG |= (1 << 7);
	}
	if(EXTI->PR.BITS.BIT8) {
		do_somethingIT8();
		EXTI->PR.REG |= (1 << 8);
	}
	if(EXTI->PR.BITS.BIT9) {
		do_somethingIT9();
		EXTI->PR.REG |= (1 << 9);
	}
}

void EXTI15_10_IRQHandler(void) {
	if(EXTI->PR.BITS.BIT10) {
		do_somethingIT10();
		EXTI->PR.REG |= (1 << 10);
	}
	if(EXTI->PR.BITS.BIT11) {
		do_somethingIT11();
		EXTI->PR.REG |= (1 << 11);
	}
	if(EXTI->PR.BITS.BIT12) {
		do_somethingIT12();
		EXTI->PR.REG |= (1 << 12);
	}
	if(EXTI->PR.BITS.BIT13) {
		do_somethingIT13();
		EXTI->PR.REG |= (1 << 13);
	}
	if(EXTI->PR.BITS.BIT14) {
		do_somethingIT14();
		EXTI->PR.REG |= (1 << 14);
	}
	if(EXTI->PR.BITS.BIT15) {
		do_somethingIT15();
		EXTI->PR.REG |= (1 << 15);
	}
}

void NVIC_UART_En(void){
	NVIC_ISER1 |= (1<<(37-32));
}	

void NVIC_USB_En(void){
	NVIC_ISER0 |= (1<<20);
}

