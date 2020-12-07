#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f10x.h"
	
void DelayInit(void);
void delay(uint32_t milliseconds);
void pll_Init(void);

#ifdef __cplusplus
}
#endif
#endif
