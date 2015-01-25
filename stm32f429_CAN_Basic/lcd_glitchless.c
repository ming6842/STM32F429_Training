/* For direct write test */

#include "lcd_glitchless.h"

#define TRANSPARENCY_COLOR LCD_COLOR_WHITE

void DrawDirectlyPixel(uint16_t layer,uint16_t xpos,uint16_t ypos,uint16_t color){

       *(__IO uint16_t*) (LCD_FRAME_BUFFER + BUFFER_OFFSET*layer +(2*((xpos) + LCD_PIXEL_WIDTH*(ypos)))) = color; 

}

void DrawRectangular(uint16_t layer,uint16_t color,uint16_t xpos,uint16_t ypos,uint16_t xlen, uint16_t ylen){


	uint16_t i,j;

        for(i=0;i< xlen;i++){
          for(j=0;j< ylen;j++)
          DrawDirectlyPixel(layer,i+xpos,j+ypos,color);
        }

}

void DrawBufferToScreen(uint16_t layer,uint16_t *buffer_ptr,uint16_t xpos,uint16_t ypos,uint16_t xlen,uint16_t ylen){

	uint16_t i,j;

        for(i=0;i< xlen;i++){
          for(j=0;j< ylen;j++)
          DrawDirectlyPixel(layer,i+xpos,j+ypos,buffer_ptr[j + ylen*i]);
        }


}

void DrawPartofBufferToScreen(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,rectangular_t *rect_to_draw){

	uint16_t i,j;

        for(i=(rect_to_draw->xpos);i< (rect_to_draw->xpos) +( rect_to_draw->xlen);i++){
          for(j=rect_to_draw->ypos;j< (rect_to_draw->ypos) +( rect_to_draw->ylen);j++)
          DrawDirectlyPixel(layer,i,j,buffer_ptr[j + buffer_y_len*i]);
        }


}

void PadRectangular(uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,rectangular_t *rect){

      //uint16_t (*array_ptr)[xlen][ylen] = buffer_ptr;

	uint16_t i,j;

        for(i= rect->xpos;i< (rect->xpos)+(rect->xlen);i++){
          for(j=rect->ypos;j< (rect->ypos) + (rect->ylen);j++)

          		//(*array_ptr)[i][j] = color;
				 buffer_ptr[j + buffer_y_len*i] = color;
        }

}

#define MIDDLE_POINT_LEFT 1
#define MIDDLE_POINT_RIGHT 2
#define MIDDLE_POINT_INLINE 3

void PadFillTriangle(uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,triangle_t* triang ){

	float x[3]; 
	float y[3];	// Min to max wrt. y

	float c1=0,c2=0,c3=0;
	float w1=0,w2=0,w3=0;

	float testy=0,testx=0;

	uint16_t left_limit=0,right_limit=0;
	uint16_t upper_limit,middle_limit,lower_limit;
	uint8_t middlepoint_location=0;

	uint16_t i,j;
	/* Arrange 3 points wrt. y position */


          if((triang->y1) > (triang->y2)){

            if((triang->y1)>(triang->y3)){

              x[2] = (float)(triang->x1);
              y[2] = (float)(triang->y1);

                if((triang->y2)>(triang->y3)){

                  x[1] = (float)(triang->x2);
                  y[1] = (float)(triang->y2);

                  x[0] = (float)(triang->x3);
                  y[0] = (float)(triang->y3);
                }else{

                  x[1] = (float)(triang->x3);
                  y[1] = (float)(triang->y3);

                  x[0] = (float)(triang->x2);
                  y[0] = (float)(triang->y2);
                }

            }else{

              x[2] = (float)(triang->x3);
              y[2] = (float)(triang->y3);

              x[1] = (float)(triang->x1);
              y[1] = (float)(triang->y1);

              x[0] = (float)(triang->x2);
              y[0] = (float)(triang->y2);

            }

          }else{ // (triang->y2)>(triang->y1)

              if((triang->y2)>(triang->y3)){

                x[2]  = (float)(triang->x2);
                y[2]  = (float)(triang->y2);

                  if((triang->y3)>(triang->y1)){

                    x[1] = (float)(triang->x3);
                    y[1] = (float)(triang->y3);

                    x[0] = (float)(triang->x1);
                    y[0] = (float)(triang->y1);
                  }else{
                    x[1] = (float)(triang->x1);
                    y[1] = (float)(triang->y1);

                    x[0] = (float)(triang->x3);
                    y[0] = (float)(triang->y3);

                  }

              }else{ // (triang->y3)>(triang->y2)
                x[2]  = (triang->x3);
                y[2]  = (triang->y3);

                x[1]  = (triang->x2);
                y[1]  = (triang->y2);

                x[0]  = (triang->x1);
                y[0]  = (triang->y1);
              }

          }

          /* Check if middle is left or right */
          /* Build up equation for Max-min point first then check side of middle point */

          /* Constructing equation between y[2] and y[0] */
          c1 = y[2] - x[2] * (y[2] - y[0]) / (x[2]-x[0]);
          w1 = (x[2] - x[0])/ (y[2] - y[0]);

          /* Constructing equation between y[2] and y[1] */
          c2 = y[2] - x[2] * (y[2] - y[1]) / (x[2]-x[1]);
          w2 = (x[2] - x[1])/ (y[2] - y[1]);

          /* Constructing equation between y[0] and y[1] */
          c3 = y[0] - x[0] * (y[0] - y[1]) / (x[0]-x[1]);
          w3 = (x[0] - x[1])/ (y[0] - y[1]);

          /* test the side of middle point */

          		if(x[2] == x[0]){

          			testx = x[2];
          		}else{

		          testx = (y[1]-c1) * w1;
		        }

          if(x[1] > testx){

          	middlepoint_location = MIDDLE_POINT_RIGHT;

          }else if(testx > x[1]){

          	middlepoint_location = MIDDLE_POINT_LEFT;

          }else{

          	middlepoint_location =  MIDDLE_POINT_INLINE;

          }

          if(middlepoint_location == MIDDLE_POINT_RIGHT){

          	/* Y[2]---Y[0] line is on the left, Y[2]---Y[1] line is on the right until middle point */

          	upper_limit = y[2];
          	middle_limit = y[1];
          	lower_limit = y[0];

          	for(j = upper_limit;j>middle_limit;j--){

          		/* calculating left and right limit for each of Y for upper part*/
          		if(x[2] == x[0]){

          			left_limit = x[2];
          		}else{

          		left_limit = (uint16_t)(((float)j-c1) * w1);

          		}

				if(x[2] == x[1]){
					right_limit = x[2];
				}else{

          		right_limit = (uint16_t)(((float)j-c2) * w2);

				}


          		for(i = left_limit;i<=right_limit;i++){
				 buffer_ptr[j + buffer_y_len*i] = color;
          		}

          	}

          	for(j=middle_limit;j>lower_limit;j--){

          		/* calculating left and right limit for each of Y for lower part*/
          		if(x[2] == x[0]){

          			left_limit = x[2];
          		}else{

          		left_limit = (uint16_t)(((float)j-c1) * w1);

          		}


				if(x[0] == x[1]){
					right_limit = x[2];
				}else{

          		right_limit = (uint16_t)(((float)j-c3) * w3);
				}

          		for(i = left_limit;i<=right_limit;i++){
				 buffer_ptr[j + buffer_y_len*i] = color;
          		}
          	}



          }else{  // middlepoint is on the left or in line

          	/* Y[2]---Y[0] line is on the right, Y[2]---Y[1] line is on the left until middle point */

          	upper_limit = y[2];
          	middle_limit = y[1];
          	lower_limit = y[0];

          	for(j = upper_limit;j>middle_limit;j--){

          		/* calculating left and right limit for each of Y for upper part*/


				if(x[2] == x[1]){
					left_limit = x[2];
				}else{
          		left_limit = (uint16_t)(((float)j-c2) * w2);
          		}


          		if(x[2] == x[0]){

          			right_limit = x[2];
          		}else{
          		right_limit = (uint16_t)(((float)j-c1) * w1);
          		}

          		for(i = left_limit;i<=right_limit;i++){
				 buffer_ptr[j + buffer_y_len*i] = color;
          		}

          	}

          	for(j=middle_limit;j>lower_limit;j--){

          		/* calculating left and right limit for each of Y for lower part*/

				if(x[0] == x[1]){
					left_limit = x[2];
				}else{
          		left_limit = (uint16_t)(((float)j-c3) * w3);
          		}

          		if(x[2] == x[0]){

          			right_limit = x[2];
          		}else{
          		right_limit = (uint16_t)(((float)j-c1) * w1);
          		}

          		for(i = left_limit;i<=right_limit;i++){
				 buffer_ptr[j + buffer_y_len*i] = color;
          		}
          	}

          }


}


void DrawPartofBufferToScreenTriangle(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,triangle_t* triang ){

	float x[3]; 
	float y[3];	// Min to max wrt. y

	float c1=0,c2=0,c3=0;
	float w1=0,w2=0,w3=0;

	float testy=0,testx=0;

	uint16_t left_limit=0,right_limit=0;
	uint16_t upper_limit,middle_limit,lower_limit;
	uint8_t middlepoint_location=0;

	uint16_t i,j;
	/* Arrange 3 points wrt. y position */


          if((triang->y1) > (triang->y2)){

            if((triang->y1)>(triang->y3)){

              x[2] = (float)(triang->x1);
              y[2] = (float)(triang->y1);

                if((triang->y2)>(triang->y3)){

                  x[1] = (float)(triang->x2);
                  y[1] = (float)(triang->y2);

                  x[0] = (float)(triang->x3);
                  y[0] = (float)(triang->y3);
                }else{

                  x[1] = (float)(triang->x3);
                  y[1] = (float)(triang->y3);

                  x[0] = (float)(triang->x2);
                  y[0] = (float)(triang->y2);
                }

            }else{

              x[2] = (float)(triang->x3);
              y[2] = (float)(triang->y3);

              x[1] = (float)(triang->x1);
              y[1] = (float)(triang->y1);

              x[0] = (float)(triang->x2);
              y[0] = (float)(triang->y2);

            }

          }else{ // (triang->y2)>(triang->y1)

              if((triang->y2)>(triang->y3)){

                x[2]  = (float)(triang->x2);
                y[2]  = (float)(triang->y2);

                  if((triang->y3)>(triang->y1)){

                    x[1] = (float)(triang->x3);
                    y[1] = (float)(triang->y3);

                    x[0] = (float)(triang->x1);
                    y[0] = (float)(triang->y1);
                  }else{
                    x[1] = (float)(triang->x1);
                    y[1] = (float)(triang->y1);

                    x[0] = (float)(triang->x3);
                    y[0] = (float)(triang->y3);

                  }

              }else{ // (triang->y3)>(triang->y2)
                x[2]  = (triang->x3);
                y[2]  = (triang->y3);

                x[1]  = (triang->x2);
                y[1]  = (triang->y2);

                x[0]  = (triang->x1);
                y[0]  = (triang->y1);
              }

          }

          /* Check if middle is left or right */
          /* Build up equation for Max-min point first then check side of middle point */

          /* Constructing equation between y[2] and y[0] */
          c1 = y[2] - x[2] * (y[2] - y[0]) / (x[2]-x[0]);
          w1 = (x[2] - x[0])/ (y[2] - y[0]);

          /* Constructing equation between y[2] and y[1] */
          c2 = y[2] - x[2] * (y[2] - y[1]) / (x[2]-x[1]);
          w2 = (x[2] - x[1])/ (y[2] - y[1]);

          /* Constructing equation between y[0] and y[1] */
          c3 = y[0] - x[0] * (y[0] - y[1]) / (x[0]-x[1]);
          w3 = (x[0] - x[1])/ (y[0] - y[1]);

          /* test the side of middle point */

          		if(x[2] == x[0]){

          			testx = x[2];
          		}else{

		          testx = (y[1]-c1) * w1;
		        }

          if(x[1] > testx){

          	middlepoint_location = MIDDLE_POINT_RIGHT;

          }else if(testx > x[1]){

          	middlepoint_location = MIDDLE_POINT_LEFT;

          }else{

          	middlepoint_location =  MIDDLE_POINT_INLINE;

          }

          if(middlepoint_location == MIDDLE_POINT_RIGHT){

          	/* Y[2]---Y[0] line is on the left, Y[2]---Y[1] line is on the right until middle point */

          	upper_limit = y[2];
          	middle_limit = y[1];
          	lower_limit = y[0];

          	for(j = upper_limit;j>middle_limit;j--){

          		/* calculating left and right limit for each of Y for upper part*/
          		if(x[2] == x[0]){

          			left_limit = x[2];
          		}else{

          		left_limit = (uint16_t)(((float)j-c1) * w1);

          		}

				if(x[2] == x[1]){
					right_limit = x[2];
				}else{

          		right_limit = (uint16_t)(((float)j-c2) * w2);

				}


          		for(i = left_limit;i<=right_limit;i++){


          		DrawDirectlyPixel(layer,i,j,buffer_ptr[j + buffer_y_len*i]);
				 // buffer_ptr[j + buffer_y_len*i] = color;
          		}

          	}

          	for(j=middle_limit;j>lower_limit;j--){

          		/* calculating left and right limit for each of Y for lower part*/
          		if(x[2] == x[0]){

          			left_limit = x[2];
          		}else{

          		left_limit = (uint16_t)(((float)j-c1) * w1);

          		}


				if(x[0] == x[1]){
					right_limit = x[2];
				}else{

          		right_limit = (uint16_t)(((float)j-c3) * w3);
				}

          		for(i = left_limit;i<=right_limit;i++){
          		DrawDirectlyPixel(layer,i,j,buffer_ptr[j + buffer_y_len*i]);
          		}
          	}



          }else{  // middlepoint is on the left or in line

          	/* Y[2]---Y[0] line is on the right, Y[2]---Y[1] line is on the left until middle point */

          	upper_limit = y[2];
          	middle_limit = y[1];
          	lower_limit = y[0];

          	for(j = upper_limit;j>middle_limit;j--){

          		/* calculating left and right limit for each of Y for upper part*/


				if(x[2] == x[1]){
					left_limit = x[2];
				}else{
          		left_limit = (uint16_t)(((float)j-c2) * w2);
          		}


          		if(x[2] == x[0]){

          			right_limit = x[2];
          		}else{
          		right_limit = (uint16_t)(((float)j-c1) * w1);
          		}

          		for(i = left_limit;i<=right_limit;i++){
          		DrawDirectlyPixel(layer,i,j,buffer_ptr[j + buffer_y_len*i]);
          		}

          	}

          	for(j=middle_limit;j>lower_limit;j--){

          		/* calculating left and right limit for each of Y for lower part*/

				if(x[0] == x[1]){
					left_limit = x[2];
				}else{
          		left_limit = (uint16_t)(((float)j-c3) * w3);
          		}

          		if(x[2] == x[0]){

          			right_limit = x[2];
          		}else{
          		right_limit = (uint16_t)(((float)j-c1) * w1);
          		}

          		for(i = left_limit;i<=right_limit;i++){
          		DrawDirectlyPixel(layer,i,j,buffer_ptr[j + buffer_y_len*i]);
          		}
          	}



          }


}




void DrawNeedle(uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,int32_t x_center,int32_t y_center,float directions,int32_t radius, int32_t base_width){

  	directions += 180.0f;

    triangle_t triang1;

       
  triang1.x1 = x_center + (int32_t)((float) base_width * cosf(directions * 0.0174444444444f));
  triang1.y1 = y_center + (int32_t)((float) base_width * sinf(directions * 0.0174444444444f));

  triang1.x2 = x_center - (int32_t)((float) radius * sinf(directions * 0.0174444444444f));
  triang1.y2 = y_center + (int32_t)((float) radius * cosf(directions * 0.0174444444444f));

  triang1.x3 = x_center - (int32_t)((float) base_width * cosf(directions * 0.0174444444444f));
  triang1.y3 = y_center - (int32_t)((float) base_width * sinf(directions * 0.0174444444444f));

 		GPIO_ResetBits(GPIOG,GPIO_Pin_13);
  		PadFillTriangle(buffer_ptr,buffer_x_len,buffer_y_len,color,&triang1);

        GPIO_ToggleBits(GPIOG,GPIO_Pin_13);
  		DrawPartofBufferToScreenTriangle(LCD_FOREGROUND_LAYER,buffer_ptr,buffer_x_len,buffer_y_len,&triang1);

}


void MoveNeedle(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,int32_t x_center,int32_t y_center,float directtt,float prev_directions,int32_t radius, int32_t base_width){

  	directtt += 180.0f;
  	prev_directions += 180.0f;
    triangle_t current_triang;
    triangle_t old_triang;

       
  current_triang.x1 = x_center + (int32_t)((float) base_width * cosf(directtt * 0.0174444444444f));
  current_triang.y1 = y_center + (int32_t)((float) base_width * sinf(directtt * 0.0174444444444f));

  current_triang.x2 = x_center - (int32_t)((float) radius * sinf(directtt * 0.0174444444444f));
  current_triang.y2 = y_center + (int32_t)((float) radius * cosf(directtt * 0.0174444444444f));

  current_triang.x3 = x_center - (int32_t)((float) base_width * cosf(directtt * 0.0174444444444f));
  current_triang.y3 = y_center - (int32_t)((float) base_width * sinf(directtt * 0.0174444444444f));

       
  old_triang.x1 = x_center + (int32_t)((float) base_width * cosf(prev_directions * 0.0174444444444f));
  old_triang.y1 = y_center + (int32_t)((float) base_width * sinf(prev_directions * 0.0174444444444f));

  old_triang.x2 = x_center - (int32_t)((float) radius * sinf(prev_directions * 0.0174444444444f));
  old_triang.y2 = y_center + (int32_t)((float) radius * cosf(prev_directions * 0.0174444444444f));

  old_triang.x3 = x_center - (int32_t)((float) base_width * cosf(prev_directions * 0.0174444444444f));
  old_triang.y3 = y_center - (int32_t)((float) base_width * sinf(prev_directions * 0.0174444444444f));



  	 // 	PadFillTriangle(buffer_ptr,buffer_x_len,buffer_y_len,TRANSPARENCY_COLOR,&old_triang);
  	 // 	PadFillTriangle(buffer_ptr,buffer_x_len,buffer_y_len,color,&current_triang); 

  	 // 	DrawPartofBufferToScreenTriangle(LCD_FOREGROUND_LAYER,buffer_ptr,buffer_x_len,buffer_y_len,&current_triang);
  		// DrawPartofBufferToScreenTriangle(LCD_FOREGROUND_LAYER,buffer_ptr,buffer_x_len,buffer_y_len,&old_triang);
  		
  		MoveAndUpdateTriangle(layer,buffer_ptr,buffer_x_len,buffer_y_len,color,&old_triang,&current_triang);
}


void MoveAndUpdateRectangular(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,rectangular_t *old_rect, rectangular_t *new_rect){

		/* Clean up old rect */
        PadRectangular(buffer_ptr,buffer_x_len,buffer_y_len,TRANSPARENCY_COLOR, old_rect);

 	 	/* Pad new rect */
        PadRectangular(buffer_ptr,buffer_x_len,buffer_y_len,color, new_rect);

        /* Update ONLY old rect area */
		DrawPartofBufferToScreen(layer,buffer_ptr,buffer_x_len,buffer_y_len,old_rect);
		DrawPartofBufferToScreen(layer,buffer_ptr,buffer_x_len,buffer_y_len,new_rect);

}


void MoveAndUpdateTriangle(uint16_t layer,uint16_t *buffer_ptr,uint16_t buffer_x_len,uint16_t buffer_y_len,uint16_t color,triangle_t *old_triang, triangle_t *new_triang){

		/* Clean up old triangle*/
        PadFillTriangle(buffer_ptr,buffer_x_len,buffer_y_len,TRANSPARENCY_COLOR,old_triang);
        
 	 	/* Pad new triangle */
        PadFillTriangle(buffer_ptr,buffer_x_len,buffer_y_len,color,new_triang);

        /* Update ONLY old area */
  		DrawPartofBufferToScreenTriangle(layer,buffer_ptr,buffer_x_len,buffer_y_len,old_triang);

        /* Update ONLY new area */
  		DrawPartofBufferToScreenTriangle(layer,buffer_ptr,buffer_x_len,buffer_y_len,new_triang);

}