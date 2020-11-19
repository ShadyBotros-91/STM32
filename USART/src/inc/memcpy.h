/*
 * memcpy.h
 *
 *  Created on: 27.10.2020
 *      Author: Shady
 */

#ifndef INC_MEMCPY_H_
#define INC_MEMCPY_H_

#include <inttypes.h>


#endif /* INC_MEMCPY_H_ */

typedef enum
{
	RETURN_STATUS_NOT_OK,

	RETURN_STATUS_OK,

}ReturnStatus_Type;


ReturnStatus_Type memcpy32(const uint32_t * src ,
		uint32_t * dst , const uint32_t size);
