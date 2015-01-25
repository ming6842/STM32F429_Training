#ifndef __DRAWING_H
#define __DRAWING_H

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"

//void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness);
//void DrawNeedle(uint16_t x,uint16_t y,uint16_t radius,float max,float min,float variable);
void Meter(uint16_t x,uint16_t y,uint16_t radius,float max,float min);


#endif