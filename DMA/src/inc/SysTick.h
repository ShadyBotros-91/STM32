/*
 * SysTick.h
 *
 *  Created on: 27.09.2020
 *      Author: Shady
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

/* INC_SYSTICK_H_ */

#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"


#endif


void SysTick_Init(void);

void SysTick_IncrementTicks_cb(void);

uint32_t SysTick_GetCurrentTick(void);

void SysTick_Delay (uint32_t);
