#include "drawing.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include <math.h>

// void DrawThickCircle(uint32_t x,uint32_t y,uint32_t radius, uint32_t thickness){

//     LCD_SetTextColor(LCD_COLOR_BLACK);
//     LCD_DrawFullCircle(x, y, radius);
//     LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);
//     LCD_DrawFullCircle(x, y, radius-thickness);
//     LCD_DrawUniLine(x,y,x+radius,y+radius);

// }

void DrawNeedle(uint16_t x,uint16_t y,uint16_t radius,float max,float min,float variable)
{
  float midpoint;
  float range;
  float angle;
  int16_t point2x;
  int16_t point2y;
  midpoint = (max + min)/2;
  range    = max - min;

  if (variable > midpoint)
  {
  	angle = (variable - midpoint)/(range/2)*180;
  }
  else if (variable < midpoint)
  {
  	angle = -(midpoint - variable)/(range/2)*180;
  }
  else if (variable > max && variable < min )
  {
  	angle = 180;
  }
  else
  {
  	angle = 0;
  }

  point2x = x + radius*sin(angle*3.14/180);
  point2y = y - radius*cos(angle*3.14/180);



  LCD_DrawUniLine(x-1,y-1,point2x-1,point2y-1);
  LCD_DrawUniLine(x,y,point2x,point2y);
  LCD_DrawUniLine(x+1,y+1,point2x+1,point2y+1);

}


void Meter(uint16_t x,uint16_t y,uint16_t radius,float max,float min)
{
	char num[100] ;//= "123456789";
	float midpoint = (max + min)/2;
  	float range = max - min;
  	float angle = 0;
  	int16_t point2x;
  	int16_t point2y;
  	uint8_t buff_len;
 
  	// LCD_DisplayChar(30 ,40 ,0x55);
  	// sprintf(num,"%f",-3.33333);
  	// buff_len = strlen(num);
  	// sprintf(num,"%d",buff_len);
  	// LCD_DisplayChar(50 ,115 ,num[0]);
  	// LCD_DisplayChar(50 ,125 ,num[1]);

  	/*Line = x : Column = y*/
  	// LCD_DisplayChar(50 ,50 ,num[0]);
  	

  	float i;
  	uint8_t k = 0;
  	uint8_t j = 0;
  	static uint8_t interval = 5;
  	uint8_t odd = 5;

  	for (i = min + range/10 ; i < max ; i += range/10)
  	{
  		
  		angle += 360/10;
  	 	point2x = x - radius*sin(angle*3.14/180);
  		point2y = y + radius*cos(angle*3.14/180);
  		// LCD_DisplayChar(point2y,point2x,num[j]);
  		// j++;

  		sprintf(num,"%f",i);
  		buff_len = strlen(num);

  		for(j = 0;j < buff_len; j++)
  		{
  			if((buff_len % 2)==0)
  			{
  				LCD_DisplayChar(point2y,point2x-9,num[0]);
  				LCD_DisplayChar(point2y,point2x-3,num[1]);
  				LCD_DisplayChar(point2y,point2x+3,num[2]);
  				LCD_DisplayChar(point2y,point2x+9,num[3]);
  			}
  			else if((buff_len % 2)==1) 
  			{
  				LCD_DisplayChar(point2y,point2x-12,num[0]);
  				LCD_DisplayChar(point2y,point2x-6,num[1]);
  				LCD_DisplayChar(point2y,point2x,num[2]);
  				LCD_DisplayChar(point2y,point2x+6,num[3]);
  				LCD_DisplayChar(point2y,point2x+12,num[4]);
  			}

  		}

  	}

  	//DrawThickCircle(x,y,radius-15,5);		

}