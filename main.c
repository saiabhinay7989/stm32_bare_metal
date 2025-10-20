#include<stdint.h>//foruint32_t what is t?

#define PERIPH_BASE (0x40000000UL)//base addresses

#define AHB1_PERIPH_OFFSET (0x20000UL)//ahb1 to gpio ,rcc
#define AHB1_PERIPH_BASE (PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define APB1_PERIPH_OFFSET (0x00UL)
#define APB1_PERIPH_BASE (PERIPH_BASE + APB1_PERIPH_OFFSET)

#define GPIOA_OFFSET (0x00UL)
#define GPIOA_BASE (AHB1_PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_PERIPH_BASE + RCC_OFFSET)

#define USART2_OFFSET (0x4400UL)
#define USART2_BASE (APB1_PERIPH_BASE + USART2_OFFSET)

#define GPIOA_MODE_R_OFFSET (0x00UL)

#define GPIOA_AFRL_OFFSET (0x20UL)//here we r using L as there are two type h and l

#define RCC_AHB1_EN_R_OFFSET (0x30UL)
#define RCC_APB1_EN_R_OFFSET (0x40UL)

#define USART_SR_OFFSET (0x00UL)
#define USART_DR_OFFSET (0x04UL)
#define USART_BRR_OFFSET (0x08UL)
#define USART_CR1_OFFSET (0x0CUL)

#define GPIOA_MODE_R (*(volatile uint32_t*)(GPIOA_BASE + GPIOA_MODE_R_OFFSET))
#define GPIOA_AFRL_R (*(volatile uint32_t*)(GPIOA_BASE + GPIOA_AFRL_OFFSET))

#define RCC_AHB1EN_R (*(volatile uint32_t*)(RCC_BASE + RCC_AHB1_EN_R_OFFSET))
#define RCC_APB1EN_R (*(volatile uint32_t*)(RCC_BASE + RCC_APB1_EN_R_OFFSET))

#define USART2_SR (*(volatile uint32_t*)(USART2_BASE + USART_SR_OFFSET))
#define USART2_DR (*(volatile uint32_t*)(USART2_BASE + USART_DR_OFFSET))
#define USART2_BRR (*(volatile uint32_t*)(USART2_BASE + USART_BRR_OFFSET))
#define USART2_CR1 (*(volatile uint32_t*)(USART2_BASE + USART_CR1_OFFSET))

#define GPIOEN (1U<<0)
#define USART2EN (1U<<17)

#define USART_CR1_UE (1U<<13)
#define USART_CR1_TE (1U<<3)

#define USART_SR_TXE (1U<<7)



void uart2_tx_init(void){

	RCC_AHB1EN_R |=GPIOEN;
	RCC_APB1EN_R |=USART2EN;

	GPIOA_MODE_R &=~(1U<<4);
	GPIOA_MODE_R |=(1U<<5);

	GPIOA_AFRL_R |=(1U<<8);
	GPIOA_AFRL_R |=(1U<<9);
	GPIOA_AFRL_R |=(1U<<10);
	GPIOA_AFRL_R &=~(1U<<11);


	USART2_BRR =0x0683;
	USART2_CR1= USART_CR1_UE|USART_CR1_TE;
}

void uart2_write(int ch){
	while(!(USART2_SR & USART_SR_TXE)){};

	USART2_DR=(ch&0xFF);
}

void uart2_write_string(const char *str){
	while(*str){

		uart2_write(*str++);
	}
}
int main (void){
	uart2_tx_init();

	while(1){uart2_write_string("System OK!");}



}





