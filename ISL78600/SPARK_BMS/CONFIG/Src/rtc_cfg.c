/*
 * @filename	rtc_cfg.c
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rtc_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "rtc_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

RTC_HandleTypeDef	rtc_cfg = {

		.Instance = RTC,
		.Init.HourFormat = RTC_HOURFORMAT_24,
		.Init.AsynchPrediv = RTC_ASYNCPREDIV,
		.Init.SynchPrediv = RTC_SYNCPREDIV,
		.Init.OutPut = RTC_OUTPUT_DISABLE,
		.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE,
		.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH,
		.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN
};

#if (RTC_SET == 1)
RTC_TimeTypeDef		rtc_time_cfg = {

		.Hours = RTC_HOURS,
		.Minutes = RTC_MINS,
		.Seconds = RTC_SECS,
		.DayLightSaving = RTC_DAYLIGHTSAVING_NONE,

};

RTC_DateTypeDef		rtc_date_cfg = {

		.Date = RTC_DATE,
		.WeekDay = RTC_WEEKDAY,
		.Month = RTC_MONTH,
		.Year = RTC_YEAR,

};
#endif
