
#include "main.h"
#include "tm_stm32f4_usb_hid_device.h"
#include "tm_stm32f4_disco.h"
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
void LED3_OFF(void){

  GPIO_SetBits(GPIOG,GPIO_Pin_13);

}

void LED3_ON(void){

  GPIO_ResetBits(GPIOG, GPIO_Pin_13);
}

void LED3_Toggle(void){


  GPIOG->ODR ^= GPIO_Pin_13;

}


void Timer_Initialization(void)
{

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel =  TIM5_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

  /* -- Timer Configuration --------------------------------------------------- */
  TIM_DeInit(TIM5);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_TimeBaseStruct.TIM_Period = 2500 - 1 ;  //250ms 
  TIM_TimeBaseStruct.TIM_Prescaler = 1640 - 1; //84 = 1M(1us)
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM5, ENABLE);
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

/**************************************************************************************/
int main(void)
{
        uint8_t already = 0;
    /* Initialize system */
    SystemInit();
    RCC_Configuration();
    GPIO_Configuration();
    USART1_Configuration();
    LED_Initialization();

    Timer_Initialization();
    //**********************************************/
        /* Set structs for all examples */
    TM_USB_HIDDEVICE_Keyboard_t Keyboard;
    TM_USB_HIDDEVICE_Gamepad_t Gamepad1, Gamepad2;
    TM_USB_HIDDEVICE_Mouse_t Mouse;
    /* Initialize USB HID Device */
    TM_USB_HIDDEVICE_Init();
    
    /* Set default values for mouse struct */
    TM_USB_HIDDEVICE_MouseStructInit(&Mouse);
    /* Set default values for keyboard struct */
    TM_USB_HIDDEVICE_KeyboardStructInit(&Keyboard);
    /* Set default values for gamepad structs */
    TM_USB_HIDDEVICE_GamepadStructInit(&Gamepad1);
    TM_USB_HIDDEVICE_GamepadStructInit(&Gamepad2);

    //********************************************

    USART1_puts("Hello World!\r\n");
    USART1_puts("Just for STM32F429I Discovery verify USART1 with USB TTL Cable\r\n");
while (1) {          
        /* If we are connected and drivers are OK */
        if (TM_USB_HIDDEVICE_GetStatus() == TM_USB_HIDDEVICE_Status_Connected) {
            /* Turn on green LED */
            TM_DISCO_LedOn(LED_GREEN);
            
/* Simple sketch start */    
            
            /* If you pressed button right now and was not already pressed */
            if (TM_DISCO_ButtonPressed() && already == 0) { /* Button on press */
                already = 1;
                
                /* Set pressed keys = WIN + R */
                Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Pressed;    /* Win button */
                Keyboard.Key1 = 0x15;                                 /* R */
                /* Result = "Run" command */
                
                /* Send keyboard report */
                TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
            } else if (!TM_DISCO_ButtonPressed() && already == 1) { /* Button on release */
                already = 0;
                
                /* Release all buttons */
                Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Released;    /* No button */
                Keyboard.Key1 = 0x00;                                 /* No key */
                /* Result = Released everything */
                
                /* Send keyboard report */
                TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
            }
            
/* Simple sketch end */
            
        } else {
            /* Turn off green LED */
            //TM_DISCO_LedOff(LED_GREEN);
        }
    }

    while(1); // Don't want to exit
}




void TIM5_IRQHandler()
{
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
           LED3_Toggle();

        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
        }
}


