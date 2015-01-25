
#ifndef __GYRO_H
#define __GYRO_H

#include "stm32f4xx.h"
#include "stm32f429i_discovery_l3gd20.h"
/* Private macro -------------------------------------------------------------*/
#define ABS(x)                     (x < 0) ? (-x) : x
#define L3G_Sensitivity_250dps     (float)114.285f        /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_500dps     (float)57.1429f        /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_2000dps    (float)14.285f         /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */
  
void Demo_GyroConfig(void);
void Demo_GyroReadAngRate (float* pfData);


#endif