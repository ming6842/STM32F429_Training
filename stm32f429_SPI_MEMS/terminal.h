
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_H
#define __TERMINAL_H

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"

#define TERMINAL_COLUMN_SIZE  27
#define TERMINAL_LINE_SIZE 25
#define TERMINAL_LINE_OFFSET 1
#define TERMINAL_COLUMN_OFFSET 2

void terminalBufferInitilization(void);
uint16_t terminalGetLine(uint16_t line);
void terminalShiftOneLine(void);
void terminalRefresh(void);
void terminalWrite(char* s);




#endif 