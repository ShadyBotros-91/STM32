/*
 * SysTick.c
 *
 *  Created on: 27.09.2020
 *      Author: Shady
 */

#include "SysTick.h"


void SysTick_Init(void)

{
	uint32_t returnCode;

	/*Update clock configuration*/
	SystemCoreClockUpdate();

	/*check clock configuration*/
	if(SystemCoreClock != (uint32_t) 180000000)
	{
		/*clock configuration is not OK*/
		while(1);
	}
	else
	{
		/*clock configuration is OK*/
		//SysTick_IncrementTicks_cb();
	}

	/* Configure SysTick to generate an interrupt every millisecond*/
	returnCode = SysTick_Config(SystemCoreClock / 1000);

	/*check return code for errors */

	if(returnCode != 0)
	{
		/*SysTick Configuration failed*/
		while (1);
	}
	else
	{
		/*SysTick Configuration OK*/
		//SysTick_IncrementTicks_cb();
	}
}

void SysTick_IncrementTicks_cb(void)
{

	SysTickCounter ++;
}

uint32_t SysTick_GetCurrentTick(void)
{

	return (SysTickCounter);

}

void SysTick_Delay (uint32_t wait_time_ms)
{

	/*store start tick*/
	uint32_t startTick = SysTickCounter;
	//SysTickCounter ++;
	/*Loop until timeout*/
	while((SysTickCounter - startTick) < wait_time_ms);

}
