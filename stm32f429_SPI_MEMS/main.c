#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

uint8_t currentLine = 0;
uint8_t currentColumn =0;
uint32_t lineCount=0;
#define TERMINAL_COLUMN_SIZE  30
#define TERMINAL_LINE_SIZE 7
uint8_t lcd_text_buff[TERMINAL_LINE_SIZE ][TERMINAL_COLUMN_SIZE];

uint16_t lineOffset=0;


uint16_t terminalGetLine(uint16_t line){


  return (lineOffset+line)  % TERMINAL_LINE_SIZE;
}

void terminalShiftOneLine(){

  uint16_t i=0;
    lineCount++;
    currentColumn =0;
    if(lineCount > TERMINAL_LINE_SIZE-1)  lineOffset++;

    // Clean current line

    for(i=0;i<TERMINAL_COLUMN_SIZE;i++)
    lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)][currentColumn] =0;


}

void terminalRefresh(){
int i=0;
  for (i=0;i<TERMINAL_LINE_SIZE;i++){

        LCD_DisplayStringLine(LINE(terminalGetLine(i)), (uint8_t*)lcd_text_buff[i]);

  }
}


void terminalWrite(char* s){


    while(*s) {

      if(*s == '\n'){

        LCD_DisplayStringLine(LINE(lineCount - lineOffset ), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);

        // for (;currentColumn<TERMINAL_COLUMN_SIZE;currentColumn++){
        //   lcd_text_buff[currentLine ][currentColumn] = 0;

        // }

        terminalShiftOneLine();
        

        // for (currentColumn=0;currentColumn<TERMINAL_COLUMN_SIZE;currentColumn++){
        //   lcd_text_buff[currentLine ][currentColumn] = 0;

        // }





      }else if(*s == '\r'){

        currentColumn =0;


      }else{


        if(currentColumn< TERMINAL_COLUMN_SIZE-1){

        lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)][currentColumn] = *s;
        currentColumn++;
          
        }else{

        lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)][currentColumn] = *s;
        
        LCD_DisplayStringLine(LINE(lineCount - lineOffset ), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);

        terminalShiftOneLine();

        }


      }

      s++;
    }

    LCD_DisplayStringLine(LINE(lineCount - lineOffset ), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);
        


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

    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
    // sprintf(lcd_text_main,"This is line : %ld              ", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);


   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(500000);

    // terminalWrite(" This is line 1\n");
    // terminalWrite(" HAHA_OHYEA123456789012345678901234567890123456789012345678901234567890lolol\n");
    // terminalWrite(" HAHA_OHYEA123456789012345678901234567890123456789012345678901234567890lolol\n");
    // terminalWrite(" HAHA_OHYEA123456789012345678901234567890123456789012345678901234567890lolol\n");
    

  while (1)
  {

    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(1), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(2), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(3), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(4), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(5), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(6), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(7), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(8), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(9), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(10), (uint8_t*)lcd_text_main);
    // sprintf(lcd_text_main,"HHAAAAAAA: %ld \r\n       ", runner++); LCD_DisplayStringLine(LINE(11), (uint8_t*)lcd_text_main);

         //Delay_1us(500000);
    //terminalRefresh();
         Delay_1us(500000);
    //lineOffset--;
  }
  
}

