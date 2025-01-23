/*
 * @filename	database.h
 * @author		SPARKBMS TEAM
 * @date		Apr 17, 2023
 * @ingroup		FOLDER NAME
 * @prefix		database
 * 
 * @brief		Add the description
 */
#ifndef ENGINE_INC_DATABASE_H_
#define ENGINE_INC_DATABASE_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "database_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/



/*---------------------------------------Function Prototypes-------------------------------------------*/

extern void DATABASE_Init(void);

void DATABASE_WRITE(void *src_database_ptr, DATABASE_e DATABASE_NAME);

void DATABASE_READ(void *dst_database_ptr, DATABASE_e DATABASE_NAME);

void DATABASE_TimeStamp(DATABASE_TIMESTAMP_s *timestamp);

extern uint16_t DATABASE_Length(DATABASE_e	DATABASE_NAME);

#endif /* ENGINE_INC_DATABASE_H_ */
