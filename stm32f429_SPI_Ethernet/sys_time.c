#include "stm32f4xx_conf.h"
#include "sys_time.h"
#include <stdint.h>
#define ONE_TICK_US 0.005555556
#define ONE_TICK_div (180)
static volatile uint32_t systick_cnt = 0;
static uint32_t systick_reload_cnt;
void SysTick_Handler(void);


void systime_init(uint32_t cnt)
{
	SysTick_Config(cnt);
	systick_reload_cnt = cnt;
}



uint32_t systime_micro(void)
{
	uint32_t ms, sys_val;

	ms = systick_cnt;
	sys_val = SysTick->VAL ;

	if(  ms != systick_cnt) {
		asm volatile("\tnop\n");
		ms = systick_cnt;
		sys_val = SysTick->VAL ;
	}
	return (ms*1000) + 1000 - sys_val/ONE_TICK_div;
}

uint32_t systime_milli(void)
{
	return systick_cnt;
}

void delay_us(uint32_t delay_us)
{
	uint32_t now = systime_micro();
	while( (systime_micro() - now) < delay_us);
}

void delay_ms(uint32_t delay_ms)
{
	uint32_t now = systime_milli();
	while( (systime_milli() - now) < delay_ms);
}


#include "dhcp.h"

void SysTick_Handler(void)
{
    static uint16_t ticks = 0;
    ticks++;
    if(ticks == 1000) {
        DHCP_time_handler();
        ticks = 0;
    }

	systick_cnt++;

}