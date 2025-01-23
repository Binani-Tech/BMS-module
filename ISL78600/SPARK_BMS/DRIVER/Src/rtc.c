/*
 * @filename	rtc.c
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rtc
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

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

void RTC_Init(void)
{

	if(HAL_RTC_Init(&rtc_cfg) != HAL_OK)
	{
		Error_Handler();
	}
#if (RTC_SET == 1)
	if(HAL_RTC_SetTime(&rtc_cfg, &rtc_time_cfg, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_RTC_SetDate(&rtc_cfg, &rtc_date_cfg, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
#endif
}

void RTC_SetTime(RTC_TimeTypeDef *time)
{
	HAL_RTC_SetTime(&rtc_cfg, time, RTC_FORMAT_BIN);
}

void RTC_SetDate(RTC_DateTypeDef *date)
{
	HAL_RTC_SetDate(&rtc_cfg, date, RTC_FORMAT_BIN);
}

void RTC_GetTime(RTC_TimeTypeDef *time)
{
	HAL_RTC_GetTime(&rtc_cfg, time, RTC_FORMAT_BIN);
}

void RTC_GetDate(RTC_DateTypeDef *date)
{
	HAL_RTC_GetDate(&rtc_cfg, date, RTC_FORMAT_BIN);
}
