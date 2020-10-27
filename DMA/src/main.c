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
#include "nvic.h"
#include "memcpy.h"
#include "dma.h"

#define	BUFFER_SIZE		((uint32_t) 500)

static uint32_t	srcBuffer[BUFFER_SIZE];
static uint32_t	dstBuffer[BUFFER_SIZE];


int main (void)

{

	ReturnStatus_Type	returnResults = RETURN_STATUS_NOT_OK;


	SysTick_Init();
	GPIO_init_LED(EVAL_GREEN_LED);
	GPIO_init_LED(EVAL_RED_LED);
	GPIO_Init_PB();
	EXTI_Init_PB();
	NVIC_Init();


	DMA2_Stream0_Init();
	DMA2_Stream0_Set_Addresses(srcBuffer , dstBuffer , BUFFER_SIZE);

	/*Initialize source buffer*/

	for(int idx = 0 ; idx < BUFFER_SIZE ; idx ++)
	{
		srcBuffer[idx] = idx * idx;

	}

//
//	/*copy data*/
//
//	returnResults = memcpy32(srcBuffer , dstBuffer , BUFFER_SIZE);
//
//	/*check return status*/
//	if(RETURN_STATUS_OK != returnResults)
//	{
//		/*copying is not OK , Turn on RED led*/
//
//		GPIO_TurnON_LED(EVAL_RED_LED);
//
//	}
//	else
//	{
//
//		/*copying is OK , Turn off green led*/
//
//		GPIO_TurnOFF_LED(EVAL_GREEN_LED);
//
//	}

	/*Clear PRIMASK . enable IRQ*/

	__enable_irq();

	/*Signal start of copying data , by turning on green LED*/

	GPIO_TurnON_LED(EVAL_GREEN_LED);

	/*DMA2 Stream0 enable*/
	DMA2_Stream0_Enable();

	/*Infinite loop*/

	while(1)

	{

/*
		Trigger EXTI0
		EXTI->SWIER = EXTI_SWIER_SWIER0;
*/




	}

}
