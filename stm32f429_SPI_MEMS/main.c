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


    terminalWrite("LCD with terminal  \n");     Delay_1us(100000);
    terminalWrite("Initializing .");     Delay_1us(1000000);
    terminalWrite(".");     Delay_1us(1000000);
    terminalWrite(".");     Delay_1us(1000000);
    terminalWrite(".");     Delay_1us(10000);
    terminalWrite(".");     Delay_1us(10000);
    terminalWrite(".");     Delay_1us(10000);
    terminalWrite(".\n");     Delay_1us(1000000);

    terminalWrite("Unpack lib-shit32 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-garbage32 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(10000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-something32 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-AOE2 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-counterstrike32 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-lolv21 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-error9000 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-error9001 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-error9002 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-error9003 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-error9004 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack lib-error9005 .");     Delay_1us(10000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    
    terminalWrite("Downloading garbage ... -");     Delay_1us(100000);
    {
      uint32_t spinning_count = 5;
while(spinning_count--){
    terminalWrite("\rDownloading garbage ... /");     Delay_1us(70000);
    terminalWrite("\rDownloading garbage ... -");     Delay_1us(70000);
    terminalWrite("\rDownloading garbage ... \\");    Delay_1us(70000);
    terminalWrite("\rDownloading garbage ... |");     Delay_1us(70000);
    }

  }

    terminalWrite("\rDownloading garbage ...done"); 
    Delay_1us(100000);


    terminalWrite("Unpack gb-shit32 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-garbage32 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-something .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-AOE2 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-counterstrike .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-lolv21 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-error9000 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-error9001 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-error9002 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-error9003 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-error9004 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    terminalWrite("Unpack gb-error9005 .");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".");     Delay_1us(100000);    terminalWrite(".\n");     Delay_1us(100000);
    


    terminalWrite("\nAccessing NCKU-WLAN ... "); 


    {
      uint32_t spinning_count = 20;
while(spinning_count--){
    terminalWrite("\rAccessing NCKU-WLAN ... /");     Delay_1us(70000);
    terminalWrite("\rAccessing NCKU-WLAN ... -");     Delay_1us(70000);
    terminalWrite("\rAccessing NCKU-WLAN ... \\");    Delay_1us(70000);
    terminalWrite("\rAccessing NCKU-WLAN ... |");     Delay_1us(70000);
    }

  }

    terminalWrite("\nNCKU Internet is too slow ... \n");     Delay_1us(100000);
    terminalWrite("\nSystem is crashing .");     Delay_1us(100000);
    terminalWrite(".");     Delay_1us(100000);
    terminalWrite(".");    Delay_1us(100000);
    terminalWrite(".\n");     Delay_1us(100000);


    terminalWrite("\rClearing screen in ... 5");     Delay_1us(500000);
    terminalWrite("\rClearing screen in ... 4");     Delay_1us(500000);
    terminalWrite("\rClearing screen in ... 3");     Delay_1us(500000);
    terminalWrite("\rClearing screen in ... 2");     Delay_1us(500000);
    terminalWrite("\rClearing screen in ... 1");     Delay_1us(500000);
    terminalClearScreen();



    terminalWrite("Welcome to our termainal .");     Delay_1us(100000);
  while (1){


   //sprintf(lcd_text_main,"This is line : %ld \n", runner++); terminalWrite(lcd_text_main); 
   
         //Delay_1us(500000);
  }
  
}

