// LCD.h
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"


void lcd_init(void);
// void lcd_drawPersimmon(void);
// void lcd_drawSmallPersimmon(void);

void lcd_drawBGPersimmon(uint8_t BGColor_R,uint8_t BGColor_G,uint8_t BGColor_B);
void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness,uint16_t edgeColor,uint16_t innerColor);
void lcd_drawBackground(uint8_t color_R,uint8_t color_G,uint8_t color_B);
#endif 