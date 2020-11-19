/*
 * irq.h
 *
 *  Created on: 15.10.2020
 *      Author: Shady
 */

#ifndef INC_IRQ_H_
#define INC_IRQ_H_



#endif /* INC_IRQ_H_ */

#include"stm32f4xx.h"


enum MyIRQs_e

{
	GREEN_LED_ON_IRQ = EXTI0_IRQn,   /*!< EVAL green LED ON interrupt .........................*/
	GREEN_LED_OFF_IRQ = EXTI1_IRQn,  /*!< EVAL green LED OFF interrupt ........................*/
	RED_LED_ON_IRQ = EXTI2_IRQn,     /*!< EVAL red LED ON interrupt ...........................*/
    RED_LED_OFF_IRQ = EXTI3_IRQn     /*!< EVAL red LED OFF interrupt ..........................*/
} MyIRQs;



void IRQ_Init(void);
