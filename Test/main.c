#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              

void DelayInit(void);
void delay(uint32_t milliseconds);
volatile uint32_t delay_ticks=0;

GPIO_InitTypeDef GPIO_InitStructure;

int main(void)
{
	DelayInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	while(1)
	{
		if(!(GPIO_ReadInputData(GPIOA) & GPIO_Pin_1))
		{
			GPIOB->ODR ^= GPIO_ODR_ODR6;
			delay(1000);
		}
		else
		{
			GPIOB->ODR ^= GPIO_ODR_ODR6;
			delay(200);
		}
		}
}

void SysTick_Handler(void)
{
	delay_ticks++;
}

void DelayInit(void)
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000);
}
void delay(uint32_t milliseconds) {
  uint32_t start = delay_ticks;
  while((delay_ticks - start) < milliseconds);
}

