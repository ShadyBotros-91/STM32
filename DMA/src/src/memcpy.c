/*
 * memcpy.c
 *
 *  Created on: 27.10.2020
 *      Author: Shady
 */

#include <stddef.h>
#include "memcpy.h"


ReturnStatus_Type	memcpy32(const uint32_t * src ,
		uint32_t * dst , const uint32_t size)
{
	/* Return status */

	ReturnStatus_Type returnStatus  = RETURN_STATUS_NOT_OK;

	/*check for null pointer */

	if( (NULL != src) && (NULL != dst))
	{

//		/*Pointers are OK , start copying*/
//
//		for(uint32_t idx = 0 ; idx < size ; idx ++)
//		{
//			dst[idx] = src[idx];
//		}

		/*Get array length*/

		uint32_t arrayLength = size;

		while(arrayLength > 0)
		{
			/*copy one word then increment the pointers*/
			*dst++ = *src++;

			/*Decrement array length*/
			arrayLength --;

		}

		/*Return OK*/
		returnStatus = RETURN_STATUS_OK;
	}
	else
	{
		/*NULL pointer , Return status is not OK*/

		returnStatus = RETURN_STATUS_NOT_OK;

	}

}
