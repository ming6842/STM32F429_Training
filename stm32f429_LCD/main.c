/**
  ******************************************************************************
  * @file    Touch_Panel/main.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   This example describes how to configure and use the touch panel 
  *          mounted on STM32F429I-DISCO boards.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup Touch_Panel
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness){


    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawFullCircle(x, y, radius);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);
    LCD_DrawFullCircle(x, y, radius-thickness);


}

int main(void)
{
  uint8_t colorR =0 ,colorG =0 ,colorB =0 ;
  uint8_t colorR_dir =0 ,colorG_dir =0 ,colorB_dir =0 ;
  char lcd_text_buff[100];
  uint32_t test_int32 =0;
  float test_float =1.222f;
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32f429_439xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f4xx.c file
  */      

  /* LCD initialization */
  LCD_Init();
  
  /* LCD Layer initialization */
  LCD_LayerInit();
    
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_SetColorKeying(0xFFFFFF);

  /* Need to reload */
  LTDC_ReloadConfig(LTDC_IMReload);

  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
  
  /* Set LCD foreground layer */
  


  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_WHITE);
  LCD_SetFont(&Font16x24);

  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE);

  LCD_DisplayStringLine(LINE(1), (uint8_t*)" LCD text print example ");
  LCD_DisplayStringLine(LINE(2), (uint8_t*)" Ming6842 @ github");
  LCD_DisplayStringLine(LINE(3), (uint8_t*)" -------------------");
  LCD_DisplayStringLine(LINE(5), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(6), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(7), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(8), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(9), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(10), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(11), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");
  LCD_DisplayStringLine(LINE(12), (uint8_t*)" !@#$%%^&*()_+)(*&^%%$#$%%^&*");


    //LCD_SetColors(ASSEMBLE_RGB(colorR, colorG, colorB),LCD_COLOR_BLACK);
    //LCD_DrawFullRect(0,0,240,320);
    LCD_SetLayer(LCD_FOREGROUND_LAYER);


    LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_WHITE);
    LCD_DrawFullRect(0,0,240,320);

    //LCD_SetTransparency(122);
    LCD_Clear(LCD_COLOR_WHITE);

#define X_MIDDLE 120
#define Y_MIDDLE 180




    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75  , X_MIDDLE-75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75-1, X_MIDDLE-75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE+75, Y_MIDDLE-75+1, X_MIDDLE-75, Y_MIDDLE+75+1);

    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75  , X_MIDDLE+75, Y_MIDDLE+75);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75-1, X_MIDDLE+75, Y_MIDDLE+75-1);
    LCD_DrawUniLine(X_MIDDLE-75, Y_MIDDLE-75+1, X_MIDDLE+75, Y_MIDDLE+75+1);


    LCD_DrawFullRect(X_MIDDLE-60,Y_MIDDLE-5,120,10);
    LCD_DrawFullRect(X_MIDDLE-5,Y_MIDDLE-60,10,120);


    DrawThickCircle(X_MIDDLE,Y_MIDDLE,30,7);

    DrawThickCircle(X_MIDDLE+60,Y_MIDDLE,22,   5);
    DrawThickCircle(X_MIDDLE-60,Y_MIDDLE,22,   5);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE+60,22,5);
    DrawThickCircle(X_MIDDLE   ,Y_MIDDLE-60,22,5);

    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE+75,32,5);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE-75,32,5);
    DrawThickCircle(X_MIDDLE+75,Y_MIDDLE-75,32,5);
    DrawThickCircle(X_MIDDLE-75,Y_MIDDLE+75,32,5);

    LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_WHITE-1);

    LCD_DisplayStringLine(LINE(1), (uint8_t*)"     Ce-91     ");

    Delay_1us(10000);

    // LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_WHITE);
    // LCD_DrawFullRect(0,0,240,320);
  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  while (1)
  {


    if(colorR_dir){

          colorR += 1;

      if(colorR > 250) colorR_dir=0;
      
    }else{

      colorR -= 1;

      if(colorR<20) colorR_dir=1;
    }

    if(colorG_dir){

          colorG += 2;

      if(colorG > 250) colorG_dir=0;
      
    }else{

      colorG -= 2;

      if(colorG<25) colorG_dir=1;
    }

    if(colorB_dir){

          colorB += 3;

      if(colorB > 250) colorB_dir=0;
      
    }else{

      colorB -= 3;

      if(colorB<25) colorB_dir=1;
    }


    LCD_SetColors(ASSEMBLE_RGB(colorR, colorG, colorB),LCD_COLOR_BLACK);
    LCD_DrawFullRect(0,0,240,320);




    // LCD_SetTextColor(LCD_COLOR_WHITE);
    // LCD_SetLayer(LCD_FOREGROUND_LAYER);
    // //LCD_DrawFullCircle(120, 240, 40);
    // Delay_1us(10000);

    // LCD_SetColors(ASSEMBLE_RGB(colorR, colorG, colorB),LCD_COLOR_BLACK);
    // //sLCD_DrawFullCircle(120, 240, 30);


    Delay_1us(10000);

     // LCD_Clear(ASSEMBLE_RGB(colorR, colorG, colorB));


      //sprintf(lcd_text_buff," LOLOLOL %ld",test_int32);
      //LCD_DisplayStringLine(LINE(7), (uint8_t*)lcd_text_buff);

      //LCD_DisplayStringLine(LINE(8), (uint8_t*)lcd_text_buff);

  }
  
}

/**
* @brief  Configure the IO Expander and the Touch Panel.
* @param  None
* @retval None
*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
