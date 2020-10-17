/*
 * irq.c
 *
 *  Created on: 15.10.2020
 *      Author: Shady
 */


#include "irq.h"


void IRQ_Init(void)
{

	/* Set priority group to 3
	 * bits[3:0] are the sub-priority
	 * bits[4:0] are the pre-empt priority
	 */

	NVIC_SetPriorityGrouping(3);

	/*Set priority levels*/

	NVIC_SetPriority(GREEN_LED_OFF_IRQ , 1);
	NVIC_SetPriority(RED_LED_OFF_IRQ ,   2);

	NVIC_SetPriority(GREEN_LED_ON_IRQ,   4);
	NVIC_SetPriority(RED_LED_ON_IRQ,     3);


	/*Enable interrupt at NVIC*/

	NVIC_EnableIRQ(GREEN_LED_OFF_IRQ);
	NVIC_EnableIRQ(RED_LED_OFF_IRQ);


	NVIC_EnableIRQ(GREEN_LED_ON_IRQ);
	NVIC_EnableIRQ(RED_LED_ON_IRQ);

}
