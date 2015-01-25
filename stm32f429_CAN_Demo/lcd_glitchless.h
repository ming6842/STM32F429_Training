
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_GLITCHLESS_H
#define __LCD_GLITCHLESS_H

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"
#include <math.h>
typedef struct rectangular_t {
	uint16_t xpos;
	uint16_t ypos;
	uint16_t xlen;
	uint16_t ylen;

} rectangular_t ;

typedef struct triangle_t {
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	uint16_t x3;
	uint16_t y3;

} triangle_t  ;


void DrawDirectlyPixel(uint16_t layer,uint16_t xpos,uint16_t ypos,uint16_t color);
void DrawBufferToScreen(uint16_t layer,uint16_t *buffer_ptr,uint16_t xpos,uint16_t ypos,uint16_t xlen,uint16_t ylen);
void DrawRectangular(uint16_t layer,uint16_t color,uint16_t xpos,uint16_t ypos,uint16_t xlen, uint16_t ylen);
void PadRectangular(uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,rectangular_t *rect);



void DrawNeedle(uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,int32_t x_center,int32_t y_center,float direction,int32_t radius, int32_t base_width);

void MoveNeedle(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,int32_t x_center,int32_t y_center,float directtt,float prev_directions,int32_t radius, int32_t base_width);
void MoveAndUpdateRectangular(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,rectangular_t *old_rect, rectangular_t *new_rect);


#endif