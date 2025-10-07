#include <stdio.h>
#include <stdint.h>
#include <rcc.h>
#include <gpio.h>
#include <exti.h>
#include <timer.h>
#include <USB.h>
void delay(volatile uint32_t t);

void delay(volatile uint32_t t){
	volatile uint32_t i;
	for(i=0; i<=t; i++);
}

void do_somethingIT2(){
	GPIO_Toggle_Pin(GPIOC, GPIO_PIN_13);
}

void do_something_TIM2(){
	GPIO_Toggle_Pin(GPIOC, GPIO_PIN_13);
}

int main(){
	//RCC PORTA
	//RCC_Cfg_6MHZ();
	RCC_Config_72Mhz();
	RCC_Enable_PortC();
	RCC_Enable_PortA();
	RCC_Enable_AFIO();
	RCC_Enable_USB();
	TIM_Init_IT(TIM2, 7199, 299, 25);
	GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP);
	GPIO_Config(GPIOA, GPIO_PIN_2,	GPIO_MODE_INPUT_PU);
	EXTI_INIT(GPIOA, GPIO_PIN_2, EXTI_FALLING_MODE);
	
	USB_Init();
	
	while(1){
		GPIO_Toggle_Pin(GPIOC, GPIO_PIN_13);
		delay(500000);
	}
	
	
}

