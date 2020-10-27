/*
 * exti.c
 *
 *  Created on: 17.10.2020
 *      Author: Shady
 */


#include "exti.h"

void EXTI_Init_PB()
{

	/*Enable SYSCFG clock*/

	RCC->APB2ENR |= RCC_APB2LPENR_SYSCFGLPEN;

	/* Map PA0 to EXT0*/

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

	/* Enable rising edge trigger*/

	EXTI->RTSR |= EXTI_RTSR_TR0;

	/* Disable falling edge trigger*/

	EXTI->FTSR &= ~(EXTI_FTSR_TR0);

	/*Enable interrupt line*/

	EXTI->IMR |= EXTI_IMR_MR0;

	/*Enable event line*/

	EXTI->EMR |= EXTI_EMR_MR0;




}
