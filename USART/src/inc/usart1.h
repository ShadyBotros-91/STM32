/*
 * usart1.h
 *
 *  Created on: 19.11.2020
 *      Author: Shady
 */

#ifndef INC_USART1_H_
#define INC_USART1_H_

#include"stm32f4xx.h"


void USART1_GPIO_Config(void);
void USART1_Init(void);
void USART1_Enable(void);
void USART1_Process(void);
void USART1_IRQ_Callback(void);



#endif /* INC_USART1_H_ */
