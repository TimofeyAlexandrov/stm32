#include "delay.h"

volatile uint32_t delay_ticks=0;

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

void pll_Init(void)
{
	ErrorStatus HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);
		
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
		}
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource()!=0x08)
		{
		}
		SystemCoreClockUpdate();
	}
}
