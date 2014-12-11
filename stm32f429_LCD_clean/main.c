#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}


int main(void)
{

  char lcd_text_buff[100];


    lcd_init();
    lcd_drawPersimmon();
    lcd_drawBackground(20,60,250);

  while (1)
  {

    // Delay_1us(30000);

  }
  
}

