#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}


int main(void)
{

  char lcd_text_main[100];
  uint32_t runner=0;

    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);

    LCD_SetFont(&Font8x12); 

    terminalBufferInitilization();

  while (1){


     sprintf(lcd_text_main,"\nThis is line : %ld ", runner++); 

     LCD_DisplayStringLine(LINE(2), (uint8_t*)lcd_text_main);

     //Delay_1us(1000000);
  }
  
}

