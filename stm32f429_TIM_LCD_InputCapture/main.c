#include "main.h"


#include <stdint.h>

void TIM5_IRQHandler(void);

uint32_t timebaseCapture_prev = 0;
uint32_t timebaseCapture_current =0;
uint32_t timebaseCapture_output = 0;

void TIM2_IRQHandler()
{


  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET) {
    /* Clear TIM1 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

      /* Get the Input Capture value */
      timebaseCapture_prev = timebaseCapture_current;
      timebaseCapture_current = TIM_GetCapture1(TIM2);

      if(timebaseCapture_current > timebaseCapture_prev){

        timebaseCapture_output  = (timebaseCapture_current- timebaseCapture_prev)*5/18;


      }else{

        timebaseCapture_output  =  (0xFFFF - timebaseCapture_prev + timebaseCapture_current)*5/18;
      }
      
  }
}


void TIM2_Initialization(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* TIM2 PWM3  PA0 */  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);

  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_DeInit(TIM2);
  TIM_TimeBaseStruct.TIM_Period = 0xFFFF;              // period = 2.5ms, 400kHz
  TIM_TimeBaseStruct.TIM_Prescaler = 50-1;            //  84 = 1M ( 1us )
  TIM_TimeBaseStruct.TIM_ClockDivision = 0;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    // Counter Up
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM2, &TIM_ICInitStructure);

  /* TIM enable counter */
  TIM_Cmd(TIM2, ENABLE);
  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
  
}


static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}


int main(void)
{

  char lcd_text_main[100];

    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);

    LCD_SetFont(&Font8x12); 

    terminalBufferInitilization();

    /* Begin timer period capture example */


    TIM2_Initialization();

    terminalWrite("Welcome to our termainal .\n");     Delay_1us(100000);
  while (1){


     sprintf(lcd_text_main,"\nPeriod = %ldus",timebaseCapture_output);
     terminalWrite(lcd_text_main); 
     Delay_1us(10000);
  }
  
}

