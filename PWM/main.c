#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              
#include "stm32f10x_tim.h"    
#include "delay.h"

void PWM_Init(void);
int brightness;
int main(void)
{
	
	pll_Init();
	DelayInit();
	PWM_Init();
	while(1)
	{
		for(brightness=0;brightness<=79;brightness+=1)
		{
			TIM2->CCR1=brightness;
			delay(50);
		}
		for(brightness=79;brightness>=0;brightness -=1)
		{
			TIM2->CCR1=brightness;
			delay(50);
		}
	}
}

void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	/**********************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InitStruct.TIM_Prescaler = 10;
	TIM_InitStruct.TIM_Period = 79;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);
	TIM_Cmd(TIM2,ENABLE);
	/*********************************************/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	/************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

