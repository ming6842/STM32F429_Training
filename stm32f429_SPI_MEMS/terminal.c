// terminal

#include "terminal.h"


uint8_t currentLine = 0;
uint8_t currentColumn = 0;
uint32_t lineCount=0;
uint8_t lcd_text_buff[TERMINAL_LINE_SIZE +TERMINAL_LINE_OFFSET][TERMINAL_COLUMN_SIZE+ TERMINAL_COLUMN_OFFSET];
uint16_t lineOffset=0;

void terminalBufferInitilization(void){
  uint16_t i_line=0,i_column=0;
  for (i_line=0;i_line < TERMINAL_LINE_SIZE+TERMINAL_LINE_OFFSET;i_line++){


      for (i_column=0;i_column < TERMINAL_COLUMN_SIZE+TERMINAL_COLUMN_OFFSET; i_column++){

          lcd_text_buff[i_line][i_column] = ' ';
      }


  }

}

uint16_t terminalGetLine(uint16_t line){


  return (lineOffset+line)  % TERMINAL_LINE_SIZE;
}

void terminalShiftOneLine(void){

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

void terminalRefresh(void){
uint32_t i=0;
  for (i= lineCount -1 ;i> (lineCount - TERMINAL_LINE_SIZE);i--){
    
        LCD_DisplayStringLine(LINE(i - lineOffset + TERMINAL_LINE_OFFSET), (uint8_t*)lcd_text_buff[i%((uint32_t)TERMINAL_LINE_SIZE+0)]);

  }
}


void terminalWrite(char* s){


    while(*s) {

      if(*s == '\n'){

        LCD_DisplayStringLine(LINE(lineCount - lineOffset + TERMINAL_LINE_OFFSET), (uint8_t*)lcd_text_buff[lineCount%((uint32_t)TERMINAL_LINE_SIZE+0)]);

        terminalShiftOneLine();
        
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

void terminalClearScreen(void){

uint32_t lineScan = 0;
    terminalBufferInitilization();

    for(lineScan = 0;lineScan < TERMINAL_LINE_SIZE+TERMINAL_LINE_OFFSET;lineScan++)
    LCD_DisplayStringLine(LINE(lineScan), (uint8_t*)lcd_text_buff[lineScan]);
     

    terminalRefresh();
    currentColumn =0 ;
    currentLine = 0;
    lineCount=0;
    lineOffset=0;


}