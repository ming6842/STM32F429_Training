
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "terminal.h"
#include <stdio.h>
#include "lcd.h"


static inline void Delay_1us(uint32_t nCnt_1us);
void LED_Initialization(void);
void Timer5_Initialization(void);
void TIM5_IRQHandler(void);

void LED3_Toggle(void);

#endif /* __MAIN_H */


