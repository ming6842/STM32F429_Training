
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
  float X_offset =0.0f,Y_offset =0.0f,Z_offset =0.0f;
  float test_float=0.0f; uint8_t test_int=0;
  float GyX =0.0f, GyY =0.0f, GyZ =0.0f;
  float GyX_prev=0.0f,GyY_prev=0.0f,GyZ_prev=0.0f;
      uint16_t x_len=240;
      uint16_t y_len=320;

      uint16_t i=0;
      uint16_t buffer_screen[x_len][y_len];

      /* For gyro receiving  */
     float receivedGyro1=0,receivedGyro1_prev=0;
     float receivedGyro2=0,receivedGyro2_prev=0;
     float receivedGyro3=0,receivedGyro3_prev=0;
     uint8_t *ptr = & receivedGyro1;


      // uint16_t *buf_ptr = &buffer_screen;
      float runner=-8.0;

      rectangular_t rect1;
      rectangular_t prev_rect;
      rectangular_t rect_screen;


    char lcd_text_main[100];

    /* LCD Initialization */
    lcd_init();
    lcd_drawBackground(20,60,250);
    //lcd_drawBGPersimmon(20, 60, 250);



    /* LED Initialization */
    LED_Initialization();

    /* CAN Initialization */
    CAN2_Config();
    CAN2_NVIC_Config();

    /* MEMS Initialization */
    Demo_GyroConfig();

    Delay_1us(10000);
      #define CALIBRATE_COUNT 1000
      for (i=0;i<CALIBRATE_COUNT ;i++){
        Demo_GyroReadAngRate (Buffer);
        X_offset+= Buffer[0];
        Y_offset+= Buffer[1];
        Z_offset+= Buffer[2];
      }

      X_offset = X_offset/ (float)CALIBRATE_COUNT;
      Y_offset = Y_offset/ (float)CALIBRATE_COUNT;
      Z_offset = Z_offset/ (float)CALIBRATE_COUNT;


        rect_screen.xlen = x_len;
        rect_screen.ylen = y_len;
        rect_screen.xpos = 0;
        rect_screen.ypos = 0;

        #define NEEDLE_RADIUS 65
        #define NEEDLE_BASE_WIDTH 14
        #define NEEDLE_FRAME_THICKNESS 5
        
        #define NEEDLE1_CENTER_X 80
        #define NEEDLE1_CENTER_Y 100

        #define NEEDLE2_CENTER_X 80
        #define NEEDLE2_CENTER_Y 200

        #define NEEDLE3_CENTER_X 80
        #define NEEDLE3_CENTER_Y 300

        /* Drawing Needle frame 1 */
        LCD_SetLayer(LCD_BACKGROUND_LAYER);

        DrawThickCircle(NEEDLE1_CENTER_X ,NEEDLE1_CENTER_Y,NEEDLE_RADIUS+NEEDLE_FRAME_THICKNESS, 4,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
       
        LCD_SetLayer(LCD_FOREGROUND_LAYER);

        DrawThickCircle(NEEDLE1_CENTER_X ,NEEDLE1_CENTER_Y,NEEDLE_BASE_WIDTH, 6,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
        
        LCD_SetLayer(LCD_BACKGROUND_LAYER);
        LCD_SetColors(ASSEMBLE_RGB(20, 60, 250),LCD_COLOR_BLACK);
        LCD_DrawFullRect(NEEDLE1_CENTER_X- NEEDLE_RADIUS-NEEDLE_FRAME_THICKNESS*2,NEEDLE1_CENTER_Y+ NEEDLE_BASE_WIDTH+3,NEEDLE_RADIUS*2+NEEDLE_FRAME_THICKNESS*4,NEEDLE_RADIUS);

        LCD_SetLayer(LCD_FOREGROUND_LAYER);

        LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        LCD_DrawFullRect(NEEDLE1_CENTER_X- NEEDLE_RADIUS,NEEDLE1_CENTER_Y+ NEEDLE_BASE_WIDTH,NEEDLE_RADIUS*2,NEEDLE_FRAME_THICKNESS-1);

        /* Drawing Needle frame 2 */
        LCD_SetLayer(LCD_BACKGROUND_LAYER);

        DrawThickCircle(NEEDLE2_CENTER_X ,NEEDLE2_CENTER_Y,NEEDLE_RADIUS+NEEDLE_FRAME_THICKNESS, 4,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
       
        LCD_SetLayer(LCD_FOREGROUND_LAYER);

        DrawThickCircle(NEEDLE2_CENTER_X ,NEEDLE2_CENTER_Y,NEEDLE_BASE_WIDTH, 6,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
        
        LCD_SetLayer(LCD_BACKGROUND_LAYER);
        LCD_SetColors(ASSEMBLE_RGB(20, 60, 250),LCD_COLOR_BLACK);
        LCD_DrawFullRect(NEEDLE2_CENTER_X- NEEDLE_RADIUS-NEEDLE_FRAME_THICKNESS*2,NEEDLE2_CENTER_Y+ NEEDLE_BASE_WIDTH+3,NEEDLE_RADIUS*2+NEEDLE_FRAME_THICKNESS*4,NEEDLE_RADIUS);

        LCD_SetLayer(LCD_FOREGROUND_LAYER);

        LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        LCD_DrawFullRect(NEEDLE2_CENTER_X- NEEDLE_RADIUS,NEEDLE2_CENTER_Y+ NEEDLE_BASE_WIDTH,NEEDLE_RADIUS*2,NEEDLE_FRAME_THICKNESS-1);


        /* Drawing Needle frame 2 */
        LCD_SetLayer(LCD_BACKGROUND_LAYER);

        DrawThickCircle(NEEDLE3_CENTER_X ,NEEDLE3_CENTER_Y,NEEDLE_RADIUS+NEEDLE_FRAME_THICKNESS, 4,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
       
        LCD_SetLayer(LCD_FOREGROUND_LAYER);

        DrawThickCircle(NEEDLE3_CENTER_X ,NEEDLE3_CENTER_Y,NEEDLE_BASE_WIDTH, 6,LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
        
        LCD_SetLayer(LCD_BACKGROUND_LAYER);
        LCD_SetColors(ASSEMBLE_RGB(20, 60, 250),LCD_COLOR_BLACK);
        LCD_DrawFullRect(NEEDLE3_CENTER_X- NEEDLE_RADIUS-NEEDLE_FRAME_THICKNESS*2,NEEDLE3_CENTER_Y+ NEEDLE_BASE_WIDTH+3,NEEDLE_RADIUS*2+NEEDLE_FRAME_THICKNESS*4,NEEDLE_RADIUS);

        LCD_SetLayer(LCD_FOREGROUND_LAYER);

        LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        LCD_DrawFullRect(NEEDLE3_CENTER_X- NEEDLE_RADIUS,NEEDLE3_CENTER_Y+ NEEDLE_BASE_WIDTH,NEEDLE_RADIUS*2,NEEDLE_FRAME_THICKNESS-1);

        /* Clear drawing buffer */
        PadRectangular(&buffer_screen,x_len,y_len,LCD_COLOR_WHITE, &rect_screen);




      while(1)
      {

        board_ID = PIN_ID_Read();

        LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
        sprintf(lcd_text_main," CAN Demo ID:%d    ",board_ID);
        LCD_DisplayStringLine(LINE(0), (uint8_t*)lcd_text_main);

        Demo_GyroReadAngRate (Buffer);

        //Delay_1us(1000);

        /* MEMS Filtering */
        #define LP_ALPHA 0.1f
        GyX = GyX*(1.0f - LP_ALPHA) + (Buffer[0] - X_offset)*LP_ALPHA;
        GyY = GyY*(1.0f - LP_ALPHA) + (Buffer[1] - Y_offset)*LP_ALPHA;
        GyZ = GyZ*(1.0f - LP_ALPHA) + (Buffer[2] - Z_offset)*LP_ALPHA;

        if(GyX >  90.0f)  GyX =  90.0f;
        if(GyX < -90.0f)  GyX = -90.0f;
        if(GyY >  90.0f)  GyY =  90.0f;
        if(GyY <  -90.0f) GyY = -90.0f;
        if(GyZ >  90.0f)  GyZ =  90.0f;
        if(GyZ < -90.0f)  GyZ = -90.0f;

        /* Start drawing rectangular */
        prev_rect = rect1;

        rect1.xlen = 25;
        rect1.ylen = 30;
        rect1.xpos = x_len/2+ (int16_t)(GyY)-10;
        rect1.ypos = y_len/2 + (int16_t)(GyX)-10;


        if(board_ID == 1){


          MoveNeedle(LCD_BACKGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_GREEN,NEEDLE1_CENTER_X,NEEDLE1_CENTER_Y,-GyZ,-GyZ_prev,NEEDLE_RADIUS,NEEDLE_BASE_WIDTH);

        }else if(board_ID == 2){

          MoveNeedle(LCD_BACKGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_GREEN,NEEDLE2_CENTER_X,NEEDLE2_CENTER_Y,-GyZ,-GyZ_prev,NEEDLE_RADIUS,NEEDLE_BASE_WIDTH);

        }else {

          MoveNeedle(LCD_BACKGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_GREEN,NEEDLE3_CENTER_X,NEEDLE3_CENTER_Y,-GyZ,-GyZ_prev,NEEDLE_RADIUS,NEEDLE_BASE_WIDTH);

        }

            CAN2_TransmitGyro(board_ID,GyZ);

            /* Received Data */
            if( can2_rx_isr_flag ==1){

              do{

            if( can2_rx_isr_flag ==1){
                  can2RxMessage = CAN2_PassRXMessage();
                  can2_rx_isr_flag=0;
                }else{

                  CAN_Receive(CAN2, CAN_FIFO0, &can2RxMessage);
                }
                  GPIO_ToggleBits(GPIOG,GPIO_Pin_14);

                    ptr[0] = can2RxMessage.Data[0];
                    ptr[1] = can2RxMessage.Data[1];
                    ptr[2] = can2RxMessage.Data[2];
                    ptr[3] = can2RxMessage.Data[3];


                    if(( can2RxMessage.ExtId &   0x0000FFFF) == 1){
                        ptr = & receivedGyro1;
                    ptr[0] = can2RxMessage.Data[0];
                    ptr[1] = can2RxMessage.Data[1];
                    ptr[2] = can2RxMessage.Data[2];
                    ptr[3] = can2RxMessage.Data[3];


                        MoveNeedle(LCD_BACKGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_RED,NEEDLE1_CENTER_X,NEEDLE1_CENTER_Y,-receivedGyro1,-receivedGyro1_prev,NEEDLE_RADIUS,NEEDLE_BASE_WIDTH);
                        
                    receivedGyro1_prev = receivedGyro1;
                    }else if (( can2RxMessage.ExtId & 0x0000FFFF) == 2){
                        ptr = & receivedGyro2;
                    ptr[0] = can2RxMessage.Data[0];
                    ptr[1] = can2RxMessage.Data[1];
                    ptr[2] = can2RxMessage.Data[2];
                    ptr[3] = can2RxMessage.Data[3];
                        MoveNeedle(LCD_BACKGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_RED,NEEDLE2_CENTER_X,NEEDLE2_CENTER_Y,-receivedGyro2,-receivedGyro2_prev,NEEDLE_RADIUS,NEEDLE_BASE_WIDTH);
                        
                    receivedGyro2_prev = receivedGyro2;
                    }else if (( can2RxMessage.ExtId & 0x0000FFFF) == 3){
                        ptr = & receivedGyro3;
                    ptr[0] = can2RxMessage.Data[0];
                    ptr[1] = can2RxMessage.Data[1];
                    ptr[2] = can2RxMessage.Data[2];
                    ptr[3] = can2RxMessage.Data[3];
                        MoveNeedle(LCD_BACKGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_RED,NEEDLE3_CENTER_X,NEEDLE3_CENTER_Y,-receivedGyro3,-receivedGyro3_prev,NEEDLE_RADIUS,NEEDLE_BASE_WIDTH);
                        
                    receivedGyro3_prev = receivedGyro3;
                    }
                  // LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
                  // sprintf(lcd_text_main," ID :%d         ", can2RxMessage.StdId);
                  // LCD_DisplayStringLine(LINE(1), (uint8_t*)lcd_text_main);
                  // LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);
                  // sprintf(lcd_text_main," Data :%f        ", receivedGyro);
                  // LCD_DisplayStringLine(LINE(2), (uint8_t*)lcd_text_main);
                }while(CAN_MessagePending(CAN2, CAN_FIFO0) > 0);



            }



          // {
          //   uint8_t status=0;



          //   while(CAN_TransmitStatus(CAN2, 0) != CAN_TxStatus_Ok ){

          //     status = CAN_TransmitStatus(CAN2, 0);
          //        if(status == CAN_TxStatus_Failed){

          //         GPIO_ToggleBits(GPIOG,GPIO_Pin_14);


          //        }
          //  }

          // }
            // TxMessage.StdId = (uint32_t)board_ID;
            // TxMessage.RTR = CAN_RTR_DATA;
            // TxMessage.IDE = CAN_ID_STD;
            // TxMessage.DLC = 8;
            // TxMessage.Data[0] = 0x01;
            // TxMessage.Data[1] = 0x01;
            // TxMessage.Data[2] = 0x01;
            // TxMessage.Data[3] = 0x01;
            // TxMessage.Data[4] = 0x01;
            // TxMessage.Data[5] = 0x01;
            // TxMessage.Data[6] = 0x01;
            // TxMessage.Data[7] = 0x01;
            // CAN_Transmit(CAN2, &TxMessage);

        //CAN2_TransmitGyro(test_int++,test_float);

        test_float += 0.1f;

        GyX_prev = GyX;
        GyZ_prev = GyZ;
        GyY_prev = GyY;

        runner += 1.0f;


        /* Faster method */
        //MoveAndUpdateRectangular(LCD_FOREGROUND_LAYER,&buffer_screen,x_len,y_len,LCD_COLOR_BLACK,&prev_rect, &rect1);
        
        /* Regular method */
        // PadRectangular(&buffer_screen,x_len,y_len,LCD_COLOR_WHITE, &prev_rect);
        // PadRectangular(&buffer_screen,x_len,y_len,LCD_COLOR_BLACK, &rect1);
         //DrawBufferToScreen(LCD_FOREGROUND_LAYER,buf_ptr,0,0, x_len,y_len);

      }

    
  
}

