/*
 * main.c
 *
 *  Created on: 27.09.2020
 *      Author: Shady
 */


#include "SysTick.h"
#include "gpio.h"
#include "nvic.h"
#include"usart1.h"




int main (void)

{


	SysTick_Init();
	GPIO_init_LED(EVAL_GREEN_LED);
	GPIO_init_LED(EVAL_RED_LED);
	NVIC_Init();

	/* GPIO and USART configurations */
	USART1_GPIO_Config();
	USART1_Init();

	/*Clear PRIMASK . enable IRQ*/

	__enable_irq();

	/* Enable transmitter , receiver and interrupts*/
	USART1_Enable();

	/*Infinite loop*/

	while(1)

	{

		/*Sending and receiving data*/
		USART1_Process();

	}

}
