/*
 * main.c
 *
 *  Created on: 27.09.2020
 *      Author: Shady
 */


#include "SysTick.h"
#include "gpio.h"
#include "irq.h"
#include "exti.h"
#include"nvic.h"


int main (void)

{

	SysTick_Init();
	GPIO_init_LED(EVAL_GREEN_LED);
	GPIO_init_LED(EVAL_RED_LED);

	GPIO_Init_PB();
	EXTI_Init_PB();
	NVIC_Init();


	/*Clear PRIMASK . enable IRQ*/

	__enable_irq();

	/*Infinite loop*/

	while(1)

	{

/*
		Trigger EXTI0
		EXTI->SWIER = EXTI_SWIER_SWIER0;
*/




	}

}
