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

void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness){


    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawFullCircle(x, y, radius);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);
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


    DrawThickCircle(X_MIDDLE,Y_MIDDLE,30,7);

    DrawThickCircle(X_MIDDLE+60,Y_MIDDLE,22,   5);
    DrawThickCircle(X_MIDDLE-60,Y_MIDDLE,22,   5);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE+60,22,5);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE-60,22,5);

    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE+75,32,5);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE-75,32,5);
    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE-75,32,5);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE+75,32,5);

    LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_DisplayStringLine(LINE(1), (uint8_t*)"     Ce-91     ");


}

void lcd_drawBackground(uint8_t color_R,uint8_t color_G,uint8_t color_B){


  	LCD_SetLayer(LCD_BACKGROUND_LAYER);
    LCD_SetColors(ASSEMBLE_RGB(color_R, color_G, color_B),LCD_COLOR_BLACK);
    LCD_DrawFullRect(0,0,240,320);
    LCD_SetLayer(LCD_FOREGROUND_LAYER);


}