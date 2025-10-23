#include<stdint.h>

#define PERIPH_BASE (0x40000000UL)

#define AHB1_OFFSET (0x20000UL)
#define AHB1_BASE (PERIPH_BASE + AHB1_OFFSET)

#define APB1_OFFSET (0x00UL)
#define APB1_BASE (PERIPH_BASE + APB1_OFFSET)

#define GPIOA_OFFSET (0x00UL)
#define GPIOA_BASE (AHB1_BASE + GPIOA_OFFSET)

#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_BASE + RCC_OFFSET)
#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x40))

#define TIM2_BASE (APB1_BASE + 0x00UL)
#define TIM2_CR1  (*(volatile uint32_t*)(TIM2_BASE + 0x00))
#define TIM2_DIER (*(volatile uint32_t*)(TIM2_BASE + 0x0C))
#define TIM2_SR  (*(volatile uint32_t*)(TIM2_BASE + 0x10))
#define TIM2_PSC (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR (*(volatile uint32_t*)(TIM2_BASE + 0x2C))
#define TIM2_CNT (*(volatile uint32_t*)(TIM2_BASE + 0x24))

#define NVIC_ISER0 (*(volatile uint32_t*)(0xE000E100UL))
#define TIM2_IRQ_POS   28

#define LED_PIN (1U<<5)

void TIM2_IRQHandler(void){

	if(TIM2_SR&1){
		TIM2_SR&=~(1U<<0);
	GPIOA_ODR ^=LED_PIN;
	}
}



int main(void){

RCC_AHB1ENR |=(1U<<0);

	GPIOA_MODER&=~(1U<<11);
	GPIOA_MODER|=(1U<<10);

	RCC_APB1ENR|=(1U<<0);

	TIM2_PSC=16000 - 1;
	TIM2_ARR=500 - 1;

	TIM2_DIER |=1;
	TIM2_CR1 |=1;

	NVIC_ISER0 |=(1U<<TIM2_IRQ_POS);

	while(1){}








}















