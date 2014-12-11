#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

uint8_t currentLine = 0;
uint8_t currentColumn =0;
#define TERMINAL_COLUMN_SIZE  30
#define TERMINAL_LINE_SIZE 26
uint8_t lcd_text_buff[TERMINAL_LINE_SIZE ][TERMINAL_COLUMN_SIZE];

void terminalWrite(char* s){


    while(*s) {

      if(*s == '\n'){

        LCD_DisplayStringLine(LINE(currentLine), (uint8_t*)lcd_text_buff[currentLine]);
        currentLine++;
        currentColumn =0;

      }else if(*s == '\r'){

        currentColumn =0;


      }else{


        if(currentColumn< TERMINAL_COLUMN_SIZE-1){

        lcd_text_buff[currentLine][currentColumn] = *s;
        currentColumn++;
          
        }else{

        lcd_text_buff[currentLine][currentColumn] = *s;
        
        LCD_DisplayStringLine(LINE(currentLine), (uint8_t*)lcd_text_buff[currentLine]);

        currentLine++;
        currentColumn =0;

        }


      }

      s++;
    }

    LCD_DisplayStringLine(LINE(currentLine), (uint8_t*)lcd_text_buff[currentLine]);
        


}



int main(void)
{

  char lcd_text_main[100];
  uint32_t runner=0;

    lcd_init();
    lcd_drawBackground(20,60,250);

    lcd_drawBGPersimmon(20, 60, 250);

    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);


  //LCD_Clear(LCD_COLOR_WHITE);
    LCD_SetFont(&Font8x12); // Max 26 (0-25) lines 30 chars per line


    terminalWrite(" HAHA_OHYEA123456789012345678901234567890123456789012345678901234567890lolol");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");
    terminalWrite(" HAHA_OHYEAHOHEAYHOHE\n");

  while (1)
  {

    sprintf(lcd_text_main,"LOLOL: %ld \r\n       ", runner++);
    LCD_DisplayStringLine(LINE(15), (uint8_t*)lcd_text_main);
         //Delay_1us(500000);

  }
  
}

