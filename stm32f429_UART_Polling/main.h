
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

 #include "stm32f4xx.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void LED_Initialization(void);
void LED3_Toggle(void);
void USART1_Configuration(void);
void USART1_puts(char* s);

static inline void Delay_1us(uint32_t);


#endif /* __MAIN_H */


