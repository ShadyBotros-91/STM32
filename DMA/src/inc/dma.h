/*
 * dma.h
 *
 *  Created on: 27.10.2020
 *      Author: Shady
 */

#ifndef INC_DMA_H_
#define INC_DMA_H_


#include"stm32f4xx.h"
#include <inttypes.h>


void DMA2_Stream0_Init();

void DMA2_Stream0_Set_Addresses(const uint32_t * src ,
		uint32_t * dst , const uint32_t size);

void DMA2_Stream0_Enable();


#endif /* INC_DMA_H_ */


