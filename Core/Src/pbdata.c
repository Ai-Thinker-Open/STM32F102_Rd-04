#include "pbdata.h"

uint8_t dt = 0;

void delay_us(uint32_t udelay)
{
	uint32_t startval, tickn, delays, wait;

	startval = SysTick->VAL;
	tickn = HAL_GetTick();
	//sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
	delays = udelay * 72; //sysc / 1000 * udelay;
	if (delays > startval)
	{
		while (HAL_GetTick() == tickn)
		{

		}
		wait = 72000 + startval - delays;
		while (wait < SysTick->VAL)
		{

		}
	}
	else
	{
		wait = startval - delays;
		while (wait < SysTick->VAL && HAL_GetTick() == tickn)
		{

		}
	}
}

