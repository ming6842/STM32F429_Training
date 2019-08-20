#ifndef __SYS_TIME_H
#define __SYS_TIME_H
#include <stdint.h>

typedef uint32_t timeMs_t ;
typedef uint32_t timeUs_t;
typedef int32_t timeDeltaUs_t;

#define TIMEUS_MAX UINT32_MAX

void systime_init(uint32_t cnt);
uint32_t systime_micro(void);
uint32_t systime_milli(void);
void delay_us(uint32_t delay_us);
void delay_ms(uint32_t delay_ms);

#endif