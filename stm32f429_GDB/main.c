#include "main.h"
#include "stdlib.h"
static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}


void LED3_Toggle(void){


  GPIOG->ODR ^= GPIO_Pin_13;

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
void Timer5_Initialization(void)
{

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM5 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel =  TIM5_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

  /* -- Timer Configuration --------------------------------------------------- */
  TIM_DeInit(TIM5);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_TimeBaseStruct.TIM_Period = 25000 - 1 ;  //250ms  --> 4Hz
  TIM_TimeBaseStruct.TIM_Prescaler = 9000 - 1; // Prescaled by 900 -> = 0.1M(10us)
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1; // Div by one -> 90 MHz (Now RCC_DCKCFGR_TIMPRE is configured to divide clock by two)
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);    // Set interrupt when timer reloads (overflow)
  TIM_ARRPreloadConfig(TIM5, DISABLE);       //Put ARR value into register
  TIM_Cmd(TIM5, ENABLE);
}


int8_t number_unsorted[10];
int8_t number_sorted[10];


uint8_t tim5_update_flag=0;



int main(void)
{

  char lcd_text_main[100];
  uint8_t password[20];

  LED_Initialization();
  Timer5_Initialization();


    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);
    LCD_SetFont(&Font8x12); 

    password[0] = 0x48;             
    password[1] = password[0]+25;   
    password[2] = password[1]+13;   
    password[3] = password[2]-10;   
    password[4] = password[3]+15;    
    password[5] = password[4]-4 ;    
    password[6] = password[5]-2 ;    
    password[7] = password[6]-8 ;   
    password[8] = password[7]-24 ;  
    password[9] = password[8]+28 ;  
     password[10] = password[9]+5 ;  
     password[11] = password[10]-7 ; 
     password[12] = password[9 ]*0 ;  


     number_unsorted[0] = rand();
     number_unsorted[1] = rand();
     number_unsorted[2] = rand();
     number_unsorted[3] = rand();
     number_unsorted[4] = rand();
     number_unsorted[5] = rand();
     number_unsorted[6] = rand();
     number_unsorted[7] = rand();
     number_unsorted[8] = rand();
     number_unsorted[9] = rand();
     number_unsorted[10] = rand();


    sprintf(lcd_text_main,"password is : ");     
    LCD_DisplayStringLine(LINE(0), (uint8_t *)lcd_text_main);

    sprintf(lcd_text_main,"%u %u %u %u %u    ",password[0]
                                           ,password[1]
                                           ,password[2]
                                           ,password[3]
                                           ,password[4]);     
    LCD_DisplayStringLine(LINE(1), (uint8_t *)lcd_text_main);

    sprintf(lcd_text_main,"%u %u %u %u %u    ",password[5]
                                           ,password[6]
                                           ,password[7]
                                           ,password[8]
                                           ,password[9]);     
    LCD_DisplayStringLine(LINE(2), (uint8_t *)lcd_text_main);
 
 
  while (1){

    /* Wait TIM5 update */
    while(tim5_update_flag == 0);
 

    /* Output unsorted data */
    sprintf(lcd_text_main,"Unsorted data :          ");     
    LCD_DisplayStringLine(LINE(5), (uint8_t *)lcd_text_main);

    sprintf(lcd_text_main,"%d %d %d %d %d         ",number_unsorted[0],number_unsorted[1],number_unsorted[2],number_unsorted[3],number_unsorted[4]);     LCD_DisplayStringLine(LINE(6), (uint8_t *)lcd_text_main);
    sprintf(lcd_text_main,"%d %d %d %d %d         ",number_unsorted[5],number_unsorted[6],number_unsorted[7],number_unsorted[8],number_unsorted[9]);     LCD_DisplayStringLine(LINE(7), (uint8_t *)lcd_text_main);



    /* Todo : sort data and output */
    number_sorted[0] = 0;
    number_sorted[1] = 0;
    number_sorted[2] = 0;
    number_sorted[3] = 0;
    number_sorted[4] = 0;
    number_sorted[5] = 0;
    number_sorted[6] = 0;
    number_sorted[7] = 0;
    number_sorted[8] = 0;
    number_sorted[9] = 0;






    /* Output sorted data */
    sprintf(lcd_text_main,"Sorted data :          ");     
    LCD_DisplayStringLine(LINE(9), (uint8_t *)lcd_text_main);
    sprintf(lcd_text_main,"%d %d %d %d %d         ",number_sorted[0],number_sorted[1],number_sorted[2],number_sorted[3],number_sorted[4]);     LCD_DisplayStringLine(LINE(10), (uint8_t *)lcd_text_main);
    sprintf(lcd_text_main,"%d %d %d %d %d         ",number_sorted[5],number_sorted[6],number_sorted[7],number_sorted[8],number_sorted[9]);     LCD_DisplayStringLine(LINE(11), (uint8_t *)lcd_text_main);

 
   }
  
}



void TIM5_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
           LED3_Toggle();
           tim5_update_flag=1;


            number_unsorted[0] = rand();
            number_unsorted[1] = rand();
            number_unsorted[2] = rand();
            number_unsorted[3] = rand();
            number_unsorted[4] = rand();
            number_unsorted[5] = rand();
            number_unsorted[6] = rand();
            number_unsorted[7] = rand();
            number_unsorted[8] = rand();
            number_unsorted[9] = rand();
            number_unsorted[10] = rand();

        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
        }
}



