
#ifndef FILE_CAN_H
#define FILE_CAN_H
#include "stm32f4xx_conf.h"
#include "stm32f4xx_can.h"


#define CANx CAN2
#define CAN_CLK RCC_APB1Periph_CAN2
#define CAN_RX_PIN GPIO_Pin_12
#define CAN_TX_PIN GPIO_Pin_13
#define CAN_GPIO_PORT GPIOB
#define CAN_GPIO_CLK RCC_AHB1Periph_GPIOB
#define CAN_AF_PORT GPIO_AF_CAN2
#define CAN_RX_SOURCE GPIO_PinSource12
#define CAN_TX_SOURCE GPIO_PinSource13

extern uint8_t can2_rx_isr_flag;

void CAN2_Config(void);
void CAN2_Transmit(void);
void CAN2_NVIC_Config(void);
void CAN2_RX0_IRQHandler(void);
void CAN2_TransmitGyro(uint8_t ID,float gyro_value);
CanRxMsg CAN2_PassRXMessage(void);
#endif