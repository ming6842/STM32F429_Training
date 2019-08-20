#include "main.h"

/* Internet define */
#include <stdbool.h>
#include <ctype.h>
#include "socket.h"
#include "dhcp.h"
#include "dns.h"

#define DHCP_SOCKET     0
#define DNS_SOCKET      1
#define HTTP_SOCKET     2

// 1K should be enough, see https://forum.wiznet.io/t/topic/1612/2
uint8_t dhcp_buffer[1024];
// 1K seems to be enough for this buffer as well
uint8_t dns_buffer[1024];

volatile bool ip_assigned = false;

void Callback_IPAssigned(void) {
    // UART_Printf("Callback: IP assigned! Leased time: %d sec\r\n", getDHCPLeasetime());
    ip_assigned = true;
}
 
void Callback_IPConflict(void) {
    // UART_Printf("Callback: IP conflict!\r\n");
}

/* Ethernet W5500 define */


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
  uint8_t receivedData=0;

    SPI_Initialization();

    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);

    LCD_SetFont(&Font8x12); 

    terminalBufferInitilization();


    while(1){
      SPI_I2S_SendData(SPI4,0x80);
      while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);

      while (SPI_I2S_GetFlagStatus(SPI4, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI4);

      sprintf(lcd_text_main,"receivedData : %x    \n", receivedData); terminalWrite(lcd_text_main); 
   


      SPI_I2S_SendData(SPI4,0x05);
      while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);

      while (SPI_I2S_GetFlagStatus(SPI4, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI4);
      

      sprintf(lcd_text_main,"receivedData : %x    \n", receivedData); terminalWrite(lcd_text_main); 
   
      Delay_1us(170000);
    }
  
}



// TODO:
/* Systick 1s for DHCP handler




 */