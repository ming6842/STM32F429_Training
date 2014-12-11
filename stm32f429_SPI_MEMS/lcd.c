#include "lcd.h"


void lcd_init(void){



  /* LCD initialization */
  LCD_Init();
  
  /* LCD Layer initialization */
  LCD_LayerInit();
    
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_SetColorKeying(0xFFFFFF);

  /* Need to reload */
  LTDC_ReloadConfig(LTDC_IMReload);

  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
  
  /* Set LCD foreground layer */

  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_WHITE);
  LCD_SetFont(&Font16x24);

  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE);

  LCD_DisplayStringLine(LINE(1), (uint8_t*)" LCD text print example ");
  LCD_DisplayStringLine(LINE(2), (uint8_t*)" Ming6842 @ github");

    LCD_SetLayer(LCD_FOREGROUND_LAYER);

    LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_WHITE);
    LCD_DrawFullRect(0,0,240,320);

    LCD_Clear(LCD_COLOR_WHITE);



}

void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness,uint16_t edgeColor,uint16_t innerColor){



    LCD_SetTextColor(edgeColor);
    LCD_DrawFullCircle(x, y, radius);
    LCD_SetTextColor(innerColor);
    LCD_DrawFullCircle(x, y, radius-thickness);


}

void lcd_drawPersimmon(void){


#define X_MIDDLE 120
#define Y_MIDDLE 180

    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75  , X_MIDDLE-75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75-1, X_MIDDLE-75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75+1, X_MIDDLE-75, Y_MIDDLE+75+1);

    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75  , X_MIDDLE+75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75-1, X_MIDDLE+75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75+1, X_MIDDLE+75, Y_MIDDLE+75+1);


    LCD_DrawFullRect(X_MIDDLE-60,Y_MIDDLE-5,120,10);
    LCD_DrawFullRect(X_MIDDLE-5,Y_MIDDLE-60,10,120);


    DrawThickCircle(X_MIDDLE,Y_MIDDLE,30,7,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    DrawThickCircle(X_MIDDLE+60,Y_MIDDLE,22,   5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE-60,Y_MIDDLE,22,   5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE+60,22,5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE-60,22,5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE+75,32,5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE-75,32,5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE-75,32,5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE+75,32,5,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_DisplayStringLine(LINE(1), (uint8_t*)"     Ce-91     ");


}

#define BLEND_THIS(colorToBlend , BackGroundColorToBlend,BlendingAlpha) (uint32_t)(colorToBlend)*(10- (uint32_t)BlendingAlpha)+(uint32_t)BackGroundColorToBlend*(uint32_t)BlendingAlpha

void lcd_drawBGPersimmon(uint8_t BGColor_R,uint8_t BGColor_G,uint8_t BGColor_B){

uint16_t edgeColor=0,innerColor=0;

uint8_t alphaBlender = 3; //full scale 10
uint8_t alphaBlenderEdge = 3; //full scale 10

innerColor = ASSEMBLE_RGB(BLEND_THIS(BGColor_R,LCD_COLOR_WHITE,alphaBlender),BLEND_THIS(BGColor_G,LCD_COLOR_WHITE,alphaBlender),BLEND_THIS(BGColor_B,LCD_COLOR_WHITE,alphaBlender));
edgeColor =  ASSEMBLE_RGB(BLEND_THIS(255/5,LCD_COLOR_BLACK,alphaBlender),BLEND_THIS(255/5,LCD_COLOR_BLACK,alphaBlender),BLEND_THIS(255/5,LCD_COLOR_BLACK,alphaBlender));

#define X_MIDDLE 120
#define Y_MIDDLE 150

    LCD_SetLayer(LCD_BACKGROUND_LAYER);

    LCD_SetColors(edgeColor,ASSEMBLE_RGB(BGColor_R,BGColor_G,BGColor_B));
    LCD_SetFont(&Font16x24);
    LCD_DisplayStringLine(LINE(10), (uint8_t*)"     Ce-91     ");
    LCD_SetFont(&Font8x12);
    LCD_DisplayStringLine(LINE(23), (uint8_t*)"           Persimmon Dev Team");
    LCD_DisplayStringLine(LINE(24), (uint8_t*)"             071 Research Lab");
    LCD_DisplayStringLine(LINE(25), (uint8_t*)"          All rights reserved");


    LCD_SetTextColor(edgeColor);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75  , X_MIDDLE-75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75-1, X_MIDDLE-75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75+1, X_MIDDLE-75, Y_MIDDLE+75+1);

    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75  , X_MIDDLE+75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75-1, X_MIDDLE+75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75+1, X_MIDDLE+75, Y_MIDDLE+75+1);


    LCD_DrawFullRect(X_MIDDLE-60,Y_MIDDLE-5,120,10);
    LCD_DrawFullRect(X_MIDDLE-5,Y_MIDDLE-60,10,120);


    DrawThickCircle(X_MIDDLE,Y_MIDDLE,30,7,edgeColor,innerColor);

    DrawThickCircle(X_MIDDLE+60,Y_MIDDLE,22,   5,edgeColor,innerColor);
    DrawThickCircle(X_MIDDLE-60,Y_MIDDLE,22,   5,edgeColor,innerColor);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE+60,22,5,edgeColor,innerColor);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE-60,22,5,edgeColor,innerColor);

    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE+75,32,5,edgeColor,innerColor);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE-75,32,5,edgeColor,innerColor);
    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE-75,32,5,edgeColor,innerColor);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE+75,32,5,edgeColor,innerColor);

    LCD_SetLayer(LCD_FOREGROUND_LAYER);



}

void lcd_drawSmallPersimmon(void){


#define X_MIDDLE 120
#define Y_MIDDLE 180

    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawUniLine(X_MIDDLE+23, Y_MIDDLE-23  , X_MIDDLE-23, Y_MIDDLE+23);
    LCD_DrawUniLine(X_MIDDLE+23, Y_MIDDLE-23-1, X_MIDDLE-23, Y_MIDDLE+23-1);
    LCD_DrawUniLine(X_MIDDLE+23, Y_MIDDLE-23+1, X_MIDDLE-23, Y_MIDDLE+23+1);

    LCD_DrawUniLine(X_MIDDLE-23, Y_MIDDLE-23  , X_MIDDLE+23, Y_MIDDLE+23);
    LCD_DrawUniLine(X_MIDDLE-23, Y_MIDDLE-23-1, X_MIDDLE+23, Y_MIDDLE+23-1);
    LCD_DrawUniLine(X_MIDDLE-23, Y_MIDDLE-23+1, X_MIDDLE+23, Y_MIDDLE+23+1);


    LCD_DrawFullRect(X_MIDDLE-21,Y_MIDDLE-1,42,2);
    LCD_DrawFullRect(X_MIDDLE-1,Y_MIDDLE-21,2,42);


    DrawThickCircle(X_MIDDLE,Y_MIDDLE,11,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    DrawThickCircle(X_MIDDLE+21,Y_MIDDLE   ,8,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE-21,Y_MIDDLE   ,8,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE+21,8,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE-21,8,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    DrawThickCircle(X_MIDDLE+23,Y_MIDDLE+23,12,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE-23,Y_MIDDLE-23,12,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE+23,Y_MIDDLE-23,12,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
    DrawThickCircle(X_MIDDLE-23,Y_MIDDLE+23,12,2,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_DisplayStringLine(LINE(1), (uint8_t*)"     Ce-91     ");


}

void lcd_drawBackground(uint8_t color_R,uint8_t color_G,uint8_t color_B){


  	LCD_SetLayer(LCD_BACKGROUND_LAYER);
    LCD_SetColors(ASSEMBLE_RGB(color_R, color_G, color_B),LCD_COLOR_BLACK);
    LCD_DrawFullRect(0,0,240,320);
    LCD_SetLayer(LCD_FOREGROUND_LAYER);


}