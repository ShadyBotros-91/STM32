/*
 * main.c
 *
 *  Created on: 27.09.2020
 *      Author: Shady
 */


#include "SysTick.h"
#include "gpio.h"
#include "irq.h"


int main (void)

{

	SysTick_Init();
	IRQ_Init();
	GPIO_init_LED(EVAL_GREEN_LED);
	GPIO_init_LED(EVAL_RED_LED);


	/* Trigger LED ON interrupts */
	NVIC_SetPendingIRQ(GREEN_LED_ON_IRQ);


	/*Clear PRIMASK . enable IRQ*/

	__enable_irq();

	/*Infinite loop*/

	while(1)

	{


//		/* Trigger LED ON interrupts */
//		NVIC_SetPendingIRQ(GREEN_LED_ON_IRQ);
//		NVIC_SetPendingIRQ(RED_LED_ON_IRQ);
//		SysTick_Delay(300);
//
//		/* Trigger LED OFF interrupts */
//		NVIC->STIR = GREEN_LED_OFF_IRQ;
//		NVIC->STIR = RED_LED_OFF_IRQ;
//		SysTick_Delay(700);

	}

}
