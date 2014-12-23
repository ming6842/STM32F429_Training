#include "main.h"

#include <stdint.h>

#define RISING 0
#define FALLING 1

void TIM5_IRQHandler(void);

enum {
  INC1 = 0,
  INC2,
  INC3,
  INC4,
  INC5,
  INC6,
};


typedef struct input_capture{
  volatile uint8_t status; 
  volatile uint32_t curr_value; // Use this value for control operation
  volatile uint32_t prev_value;

} input_capture_t;

input_capture_t inc[6];

void TIM5_IRQHandler()
{

  uint32_t current[2];
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);

  if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == SET) {
    /* Clear TIM1 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);

    if (inc[INC4].status == RISING) {
      TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
      TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;

      /* Get the Input Capture value */
      inc[INC4].prev_value = TIM_GetCapture1(TIM5);
      inc[INC4].status = FALLING;
      
    } else {

      TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
      TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;

      /* Get the Input Capture value */
      current[0] =  TIM_GetCapture1(TIM5);

      if (current[0] > inc[INC4].prev_value)
        inc[INC4].curr_value =  current[0] - inc[INC4].prev_value;
      else if (current[0] < inc[INC4].prev_value)
        inc[INC4].curr_value = 0xFFFF - inc[INC4].prev_value+ current[0] ;

      inc[INC4].status = RISING;

    }
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
  }
  if (TIM_GetITStatus(TIM5, TIM_IT_CC2) == SET) {
    /* Clear TIM1 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);
    if (inc[INC3].status == RISING) {
      TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
      TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;

      /* Get the Input Capture value */
      inc[INC3].prev_value = TIM_GetCapture2(TIM5);
      inc[INC3].status = FALLING;
  
    } else {

      TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
      TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;

      /* Get the Input Capture value */
      current[1] =  TIM_GetCapture2(TIM5);

      if (current[1] > inc[INC3].prev_value)
        inc[INC3].curr_value =  current[1] - inc[INC3].prev_value;
      else if (current[1] < inc[INC3].prev_value)
        inc[INC3].curr_value = 0xFFFF - inc[INC3].prev_value+ current[1] ;

      inc[INC3].status = RISING;

    }
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
  }

}


void enable_tim5(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* TIM2 PWM3  PA0 */  /* TIM2 PWM4  PA1 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_DeInit(TIM5);
  TIM_TimeBaseStruct.TIM_Period = 0xFFFF;              // period = 2.5ms, 400kHz
  TIM_TimeBaseStruct.TIM_Prescaler = 5;            //  84 = 1M ( 1us )
  TIM_TimeBaseStruct.TIM_ClockDivision = 0;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    // Counter Up
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM5, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);

  /* TIM enable counter */
  TIM_Cmd(TIM5, ENABLE);
  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
  TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);
  
}



static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void RCC_Configuration(void)
{
      /* --------------------------- System Clocks Configuration -----------------*/
      /* USART1 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
      /* GPIOA clock enable */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}
 
/**************************************************************************************/
 
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*-------------------------- GPIO Configuration ----------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect USART pins to AF */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);   // USART1_TX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);  // USART1_RX
}
 
/**************************************************************************************/
 
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

void USART1_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     *  - BaudRate = 57600 baud
     *  - Word Length = 8 Bits
     *  - One Stop Bit
     *  - No parity
     *  - Hardware flow control disabled (RTS and CTS signals)
     *  - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate = 57600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

}

void USART1_puts(char* s)
{
    while(*s) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, *s);
        s++;
    }
}

void LED3_On(void){

  GPIO_SetBits(GPIOG,GPIO_Pin_13);

}

void LED3_Toggle(void){


  GPIOG->ODR ^= GPIO_Pin_13;

}


/**************************************************************************************/
int main(void)
{
    //uint16_t pwm_out=0;
    RCC_Configuration();
    GPIO_Configuration();
    LED_Initialization();
    USART1_Configuration();
    enable_tim5();
    USART1_puts("Input Capture Example\r\n");
    while(1)
    {

    }

}
