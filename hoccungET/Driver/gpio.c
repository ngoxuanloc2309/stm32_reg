#include "gpio.h"

uint8_t check_reset_crl;
uint8_t check_set;
uint8_t check_reset_crh;


void GPIO_Config(volatile GPIO_Typedef *GPIOx, uint16_t pin, uint32_t mode){
	uint32_t pos=0;
	uint32_t config=0;
	for(pos=0; pos<16; pos++){
		if((pin&(1<<pos)) != 0){
			if(pos < 8){
				GPIOx->CRL.REG &= ~(uint32_t)(15 << (pos*4));
				check_reset_crl=0;
			}
			else{
				GPIOx->CRH.REG &= ~(uint32_t)(15 << ((pos-8)*4));
				check_reset_crh=0;;

			}
			
			switch(mode){
				case GPIO_MODE_OUTPUT_PP:
					//cfg = (0x03)|(0x00<<2)
					config = 0x03;
					break;
				case GPIO_MODE_OUTPUT_OD:
					config = (0x03 << 0) | (0x01 << 2);
					break;
				case GPIO_MODE_AF_PP:
					config = (0x03 << 0) | (0x02 << 2);
					break;
				case GPIO_MODE_AF_OD:
					config = (0x03 << 0) | (0x03 << 2);
					break;
				case GPIO_MODE_INPUT_ANALOG:
					config = (0x00 << 2);
					break;
				case GPIO_MODE_INPUT_FLOATING:
					config = (0x01 << 2);
					break;
				case GPIO_MODE_INPUT_PU:
					config = (0x02 << 2);
					GPIOx->ODR.REG |= (1 << pos);
					break;
				case GPIO_MODE_INPUT_PD:
					config = (0x02 << 2);
					GPIOx->ODR.REG &= ~(1 << pos);
					break;
			}
			
			if(pos<8 && check_reset_crl==0){
				GPIOx->CRL.REG |= (config<<(pos*4));				
			}else
			if(pos>=8 && check_reset_crh == 0){
				GPIOx->CRH.REG |= (config<<((pos-8)*4));
			}
		}
	}
}

void GPIO_Write_Pin(volatile GPIO_Typedef *GPIOx, uint16_t pin, uint8_t state){
	if(state){
		GPIOx->BSRR.REG = pin;
	}else{
		GPIOx->BRR.REG = pin;
	}
}

void GPIO_Toggle_Pin(volatile GPIO_Typedef *GPIOx, uint16_t pin){
	GPIOx->ODR.REG ^= pin;
}

uint8_t GPIO_Read_Pin(volatile GPIO_Typedef *GPIOx, uint16_t pin){
	return (((GPIOx->IDR.REG)&(pin)) != 0) ? 1 : 0;
}	
