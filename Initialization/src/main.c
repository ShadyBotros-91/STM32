/*
 * main.c
 *
 *  Created on: 27.09.2020
 *      Author: Shady
 */


#include "SysTick.h"
#include "gpio.h"


int main (void)

{

	SysTick_Init();
	GPIO_init_LED(EVAL_GREEN_LED);


	/*Infinite loop*/

	while(1)

	{


		GPIO_TurnON_LED(EVAL_GREEN_LED);
		SysTick_Delay(300);

		GPIO_TurnOFF_LED(EVAL_GREEN_LED);
		SysTick_Delay(700);




	}

}
