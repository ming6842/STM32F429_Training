#include "main.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void SPI_Initialization(void){

  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);


  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI4);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  /* SPI baudrate is set to 5.6 MHz (PCLK2/SPI_BaudRatePrescaler = 90/16 = 5.625 MHz)  */

  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI4, &SPI_InitStructure);

  /* Enable SPI4  */
  SPI_Cmd(SPI4, ENABLE);
  
  /* Configure GPIO PIN for Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_SPI4);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);

  /* Configure GPIO PIN for SPI4 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_5 |GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);


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

