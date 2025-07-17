#include <stdio.h>
#include <stdint.h>
#include <rcc.h>

#define RCC_ADD_BASE				0x40021000UL
#define RCC_ADD_ABP2ENR			(RCC_ADD_BASE + 0x18)
#define APB2_ENR 					 (*(volatile uint32_t *) RCC_ADD_ABP2ENR)


//GPIOA
#define GPIOA_ADD_BASE			0x40010800UL
#define GPIOA_ADD_CRL				(GPIOA_ADD_BASE + 0x00)
#define GPIOA_ADD_ODR				(GPIOA_ADD_BASE + 0x0C)
#define GPIOA_CRL 					 (*(volatile uint32_t *) GPIOA_ADD_CRL)
#define GPIOA_ODR 					 (*(volatile uint32_t *) GPIOA_ADD_ODR)
	
#define GPIOA_ADD_CRH				(GPIOA_ADD_BASE + 0x04)
#define GPIOA_CRH 					 (*(volatile uint32_t *) GPIOA_ADD_CRH)

void delay(volatile uint32_t t);

void delay(volatile uint32_t t){
	volatile uint32_t i;
	for(i=0; i<=t; i++);
}

int main(){
	//RCC PORTA
	//RCC_Cfg_6MHZ();
	RCC->CFGR.BITS.MCO = 4;
	RCC_EN_PORTA();
	GPIOA_CRH = 0x0000000B;

	
	while(1){
//		GPIOA_ODR |= (1<<0);
//		delay(1000000);
//		GPIOA_ODR &= ~(1<<0);
//		delay(1000000);
	}
	
	
}

