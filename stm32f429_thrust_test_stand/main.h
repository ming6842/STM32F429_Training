
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "terminal.h"
#include <stdio.h>
#include "lcd.h"


void ADC_Initialization(void);
void GPIO_Configuration(void);
void LED4_Toggle(void);
void LED_Initialization(void);
uint8_t PushButton_Read(void);
static inline void Delay_1us(uint32_t nCnt_1us);

#endif /* __MAIN_H */


