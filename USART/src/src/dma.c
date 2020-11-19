/*
 * dma.c
 *
 *  Created on: 27.10.2020
 *      Author: Shady
 */

#include "dma.h"


void DMA2_Stream0_Init()
{

	/*Enable DMA clock in RCC*/
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	/*make sure that the DMA2 stream 0 is disabled*/
	if(DMA_SxCR_EN == (DMA_SxCR_EN & DMA2_Stream0->CR))
	{
		/*DMA2 stream 0 is enabled  , shall be disabled first */

		DMA2_Stream0->CR &= ~ DMA_SxCR_EN;

		/*wait until EN bit is cleared*/

		while(DMA_SxCR_EN == (DMA_SxCR_EN & DMA2_Stream0->CR))
		{

			/*Do nothing until EN bit is cleared*/
		}

	}
	else
	{
		/*Do nothing , stream is not enabled*/

	}

	/*select the DMA channel CHSEL[2:0] in the DMA_SxCR
	 * (not needed when M->M)*/

	/*Select stream priority very high*/

	DMA2_Stream0->CR |= DMA_SxCR_PL;

	/*Select the data transfer direction memory to memory*/

	DMA2_Stream0->CR |= DMA_SxCR_DIR_1;

	/*Select memory and peripherals sizes*/

	DMA2_Stream0->CR |= DMA_SxCR_MSIZE_1;
	DMA2_Stream0->CR |= DMA_SxCR_PSIZE_1;

	/*Select FIFO mode , it will be also set by hardware when stream enabled*/

	DMA2_Stream0->FCR |= DMA_SxFCR_DMDIS;

	/*Select FIFO threshold level half FIFO*/

	DMA2_Stream0->FCR |= DMA_SxFCR_FTH_0;

	/*Select Peripheral and memory incremented mode*/

	DMA2_Stream0->CR |= DMA_SxCR_PINC;
	DMA2_Stream0->CR |= DMA_SxCR_MINC;

    /* Enable DMA transfer complete interrupt*/

	DMA2_Stream0->CR |= DMA_SxCR_TCIE;


}


void DMA2_Stream0_Set_Addresses(const uint32_t * src ,
		uint32_t * dst , const uint32_t size)

{

	/*Set the source address to the peripheral port*/

	DMA2_Stream0->PAR = (uint32_t)src;

	/*Set the destination address to the memory port*/

	DMA2_Stream0->M0AR = (uint32_t)dst;

	/*Set the number of data items*/

	DMA2_Stream0->NDTR = size;


}

void DMA2_Stream0_Enable()
{
	/*Clear all interrupt flags */

	DMA2->LIFCR = (DMA_LIFCR_CFEIF0 | DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CTEIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTCIF0);

	/*Enable DMA2 stream0*/

	DMA2_Stream0->CR |= DMA_SxCR_EN;

}

