
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"

void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness);
static inline void Delay_1us(uint32_t nCnt_1us);

#endif /* __MAIN_H */


