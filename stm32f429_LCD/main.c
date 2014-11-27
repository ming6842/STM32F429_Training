#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness){


    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawFullCircle(x, y, radius);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);
    LCD_DrawFullCircle(x, y, radius-thickness);


}

int main(void)
{
  uint8_t colorR =0 ,colorG =0 ,colorB =0 ;
  uint8_t colorR_dir =0 ,colorG_dir =0 ,colorB_dir =0 ;
  char lcd_text_buff[100];


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

  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  while (1)
  {

    if(colorR_dir){

          colorR += 1;

      if(colorR > 250) colorR_dir=0;
      
    }else{

      colorR -= 1;

      if(colorR<20) colorR_dir=1;
    }

    if(colorG_dir){

          colorG += 2;

      if(colorG > 250) colorG_dir=0;
      
    }else{

      colorG -= 2;

      if(colorG<25) colorG_dir=1;
    }

    if(colorB_dir){

          colorB += 3;

      if(colorB > 250) colorB_dir=0;
      
    }else{

      colorB -= 3;

      if(colorB<25) colorB_dir=1;
    }

    LCD_SetColors(ASSEMBLE_RGB(colorR, colorG, colorB),LCD_COLOR_BLACK);
    LCD_DrawFullRect(0,0,240,320);

    Delay_1us(30000);

  }
  
}

