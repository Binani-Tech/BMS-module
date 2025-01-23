/*
 * @filename	database.c
 * @author		SPARKBMS TEAM
 * @date		Apr 17, 2023
 * @ingroup		FOLDER NAME
 * @prefix		database
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "database.h"
#include "rtc.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */


void DATABASE_Init(void)
{
	if(sizeof(database_header_dev) == 0)
	{
		while(1);
	}

	for(uint16_t i=0; i < database_header_dev.no_of_database; i++)
	{
		uint8_t *database_elementptr = (uint8_t*)(void*)*(uint32_t*)(database_header_dev.database_headerptr + i);

		for(uint16_t j=0; j < (database_header_dev.database_headerptr+i)->database_length; j++)
		{
			*database_elementptr = 0;
			database_elementptr++;
		}
	}

}

void DATABASE_WRITE(void *src_database_ptr, DATABASE_e DATABASE_NAME)
{
	void *srcDataPtr;
	void *dstDataPtr;
	uint32_t dataLength;
	DATABASE_TIMESTAMP_s	timestamp;

	DATABASE_TimeStamp(&timestamp);

	srcDataPtr = src_database_ptr;
	dstDataPtr = (database_header_dev.database_headerptr + DATABASE_NAME)->databaseptr;
	dataLength = (database_header_dev.database_headerptr + DATABASE_NAME)->database_length;

	memcpy(dstDataPtr,srcDataPtr,dataLength);
	memcpy(dstDataPtr,(void*)(&timestamp),6);

}

void DATABASE_READ(void *dst_database_ptr, DATABASE_e	DATABASE_NAME)
{
	void *srcDataPtr;
	void *dstDataPtr;
	uint32_t dataLength;

	srcDataPtr = (database_header_dev.database_headerptr + DATABASE_NAME)->databaseptr;
	dstDataPtr = dst_database_ptr;
	dataLength = (database_header_dev.database_headerptr + DATABASE_NAME)->database_length;

	memcpy(dstDataPtr,srcDataPtr,dataLength);
}

void DATABASE_TimeStamp(DATABASE_TIMESTAMP_s	*timestamp)
{
	RTC_TimeTypeDef	time;
	RTC_DateTypeDef	date;

	RTC_GetTime(&time);
	RTC_GetDate(&date);

	timestamp->hour = time.Hours;
	timestamp->minute = time.Minutes;
	timestamp->second = time.Seconds;
	timestamp->day = date.Date;
	timestamp->month = date.Month;
	timestamp->year = date.Year;
}

uint16_t DATABASE_Length(DATABASE_e	DATABASE_NAME)
{
	uint16_t length;

	length = (database_header_dev.database_headerptr + DATABASE_NAME)->database_length;

	return length;
}
