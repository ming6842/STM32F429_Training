#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

#define TERMINAL_COLUMN_SIZE  27
#define TERMINAL_LINE_SIZE 25
#define TERMINAL_LINE_OFFSET 1
#define TERMINAL_COLUMN_OFFSET 2

uint8_t currentLine = 0;
uint8_t currentColumn = 0;
uint32_t lineCount=0;
uint8_t lcd_text_buff[TERMINAL_LINE_SIZE ][TERMINAL_COLUMN_SIZE+ TERMINAL_COLUMN_OFFSET];

uint16_t lineOffset=0;

void terminalBufferInitilization(void){
  uint16_t i_line=0,i_column=0;
  for (i_line=0;i_line < TERMINAL_LINE_SIZE;i_line++){


      for (i_column=0;i_column < TERMINAL_COLUMN_SIZE; i_column++){

          lcd_text_buff[i_line][i_column] = ' ';
      }


  }

}

uint16_t terminalGetLine(uint16_t line){


  return (lineOffset+line)  % TERMINAL_LINE_SIZE;
}

void terminalShiftOneLine(){

  uint16_t i=0;


    if(lineCount  > TERMINAL_LINE_SIZE-2)  {

      terminalRefresh();
      lineOffset++;
    }

    lineCount++;
    currentColumn = 0;
    // Clean current line

    for(i=TERMINAL_COLUMN_OFFSET;i<TERMINAL_COLUMN_SIZE+1;i++)
    lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)][i] =' ';


}

void terminalRefresh(){
uint32_t i=0;
  for (i= lineCount -1 ;i> (lineCount - TERMINAL_LINE_SIZE);i--){
    
        LCD_DisplayStringLine(LINE(i - lineOffset + TERMINAL_LINE_OFFSET), (uint8_t*)lcd_text_buff[i%((uint32_t)TERMINAL_LINE_SIZE+0)]);

  }
}


void terminalWrite(char* s){


    while(*s) {

      if(*s == '\n'){

        LCD_DisplayStringLine(LINE(lineCount - lineOffset + TERMINAL_LINE_OFFSET), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);

        // for (;currentColumn<TERMINAL_COLUMN_SIZE;currentColumn++){
        //   lcd_text_buff[currentLine ][currentColumn] = 0;

        // }

        terminalShiftOneLine();
        

        // for (currentColumn=0;currentColumn<TERMINAL_COLUMN_SIZE;currentColumn++){
        //   lcd_text_buff[currentLine ][currentColumn] = 0;

        // }





      }else if(*s == '\r'){

        currentColumn = 0;


      }else{


        if(currentColumn< TERMINAL_COLUMN_SIZE-1){

        lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)][currentColumn + TERMINAL_COLUMN_OFFSET] = *s;
        currentColumn++;
          
        }else{

        lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)][currentColumn+ TERMINAL_COLUMN_OFFSET] = *s;
        
        LCD_DisplayStringLine(LINE(lineCount - lineOffset + TERMINAL_LINE_OFFSET ), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);

        terminalShiftOneLine();

        }


      }

      s++;
    }

    LCD_DisplayStringLine(LINE(lineCount - lineOffset + TERMINAL_LINE_OFFSET), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);
        


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

    terminalBufferInitilization();
   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(100000);
   

  while (1){


   sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); Delay_1us(1000);
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
         //Delay_1us(500000);
    //lineOffset--;
  }
  
}

