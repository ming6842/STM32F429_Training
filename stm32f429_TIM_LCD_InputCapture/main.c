#include "main.h"


#include <stdint.h>

#define RISING 0
#define FALLING 1

void TIM5_IRQHandler(void);

typedef struct input_capture{
  volatile uint8_t status; 
  volatile uint32_t curr_value; // Use this value for control operation
  volatile uint32_t prev_value;

} input_capture_t;

input_capture_t inputCaptureData;

void TIM5_IRQHandler()
{

  uint32_t current[2];
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);

  if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == SET) {
    /* Clear TIM1 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);

    if (inputCaptureData.status == RISING) {
      TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
      TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;

      /* Get the Input Capture value */
      inputCaptureData.prev_value = TIM_GetCapture1(TIM5);
      inputCaptureData.status = FALLING;
      
    } else {

      TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
      TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;

      /* Get the Input Capture value */
      current[0] =  TIM_GetCapture1(TIM5);

      if (current[0] > inputCaptureData.prev_value)
        inputCaptureData.curr_value =  current[0] - inputCaptureData.prev_value;
      else if (current[0] < inputCaptureData.prev_value)
        inputCaptureData.curr_value = 0xFFFF - inputCaptureData.prev_value+ current[0] ;

      inputCaptureData.status = RISING;

    }
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
  }

}


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

    /* TIM2 PWM3  PA0 */  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
  //GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5); //doesn't work (MEMS chip conflict)

  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_DeInit(TIM5);
  TIM_TimeBaseStruct.TIM_Period = 0xFFFF-1;              // period = 2.5ms, 400kHz
  TIM_TimeBaseStruct.TIM_Prescaler = 5-1;            //  84 = 1M ( 1us )
  TIM_TimeBaseStruct.TIM_ClockDivision = 0;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    // Counter Up
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM5, &TIM_ICInitStructure);

  /* TIM enable counter */
  TIM_Cmd(TIM5, ENABLE);
  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
  
}


void enable_tim2(void)
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
  TIM_TimeBaseStruct.TIM_Period = 0xFFFF-1;              // period = 2.5ms, 400kHz
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
  uint32_t runner=0;

    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);

    LCD_SetFont(&Font8x12); 

    terminalBufferInitilization();



    enable_tim5();
    enable_tim2();



    terminalWrite("Welcome to our termainal .\n");     Delay_1us(100000);
  while (1){


     sprintf(lcd_text_main,"\nBase: %ld IC: %ld ",timebaseCapture_output , inputCaptureData.curr_value);
     terminalWrite(lcd_text_main); 
     Delay_1us(10000);
  }
  
}

