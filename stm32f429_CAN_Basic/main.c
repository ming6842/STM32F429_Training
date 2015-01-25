
#include "gyro.h"
#include "main.h"
#include "stm32f4xx_can.h"

float Buffer[6];
uint8_t board_ID;

CanRxMsg can2RxMessage;


static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void LED_Initialization(void){

    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE); //LED3/4 GPIO Port

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;  // LED is connected to PG13/PG14
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}


void ID_Pin_Initialization(void){

    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE); //LED3/4 GPIO Port

    /* Configure the GPIO ID pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;  // LED is connected to PG13/PG14
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* Configure GPIO pin for Jumper purpose */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4;  // LED is connected to PG13/PG14
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_SetBits(GPIOE,GPIO_Pin_2 | GPIO_Pin_4);

}

uint8_t PIN_ID_Read(void){


  return (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3))+ 2*(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5));

}


int main(void)
{

    CanTxMsg TxMessage;
    char lcd_text_main[100];

    /* LCD Initialization */
    lcd_init();
    lcd_drawBackground(20,60,250);

    /* LED Initialization */
    LED_Initialization();

    /* CAN Initialization */
    CAN2_Config();
    CAN2_NVIC_Config();


      while(1)
      {

        board_ID = PIN_ID_Read();

        LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
        sprintf(lcd_text_main," CAN Demo ID:%d    ",board_ID);
        LCD_DisplayStringLine(LINE(0), (uint8_t*)lcd_text_main);


         /* Transmit Structure preparation */
         TxMessage.StdId = 0;
         TxMessage.ExtId = (uint32_t)board_ID ;
         TxMessage.RTR = CAN_RTR_DATA;
         TxMessage.IDE = CAN_ID_EXT;
         TxMessage.DLC = 8;
         TxMessage.Data[0] = 0xAA;
         TxMessage.Data[1] = 0x55;
         TxMessage.Data[2] = 0x55;
         TxMessage.Data[3] = 0x55;
         TxMessage.Data[4] = 0x55;
         TxMessage.Data[5] = 0x55;
         TxMessage.Data[6] = 0x55;
         TxMessage.Data[7] = 0x55;

         CAN_Transmit(CAN2, &TxMessage);
          Delay_1us(10000);

            /* Received Data */
            if( can2_rx_isr_flag ==1){

                do{
                  CAN_Receive(CAN2, CAN_FIFO0, &can2RxMessage);
                  GPIO_ToggleBits(GPIOG,GPIO_Pin_14);


                  LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
                  sprintf(lcd_text_main," DATA ID:%lX    ",can2RxMessage.ExtId);
                  LCD_DisplayStringLine(LINE(1), (uint8_t*)lcd_text_main);

                  LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
                  sprintf(lcd_text_main," DATA[0]: 0x%X    ",can2RxMessage.Data[0]);
                  LCD_DisplayStringLine(LINE(2), (uint8_t*)lcd_text_main);

                }while(CAN_MessagePending(CAN2, CAN_FIFO0) > 0);

            }
      }

}

