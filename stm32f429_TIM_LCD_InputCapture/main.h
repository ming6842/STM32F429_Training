
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "terminal.h"
#include <stdio.h>
#include "lcd.h"


static inline void Delay_1us(uint32_t nCnt_1us);

void TIM2_IRQHandler(void);
void TIM2_Initialization(void);
#endif /* __MAIN_H */


