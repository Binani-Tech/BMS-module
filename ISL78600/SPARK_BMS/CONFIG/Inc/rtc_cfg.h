/*
 * @filename	rtc_cfg.h
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rtc_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_RTC_CFG_H_
#define CONFIG_INC_RTC_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define RTC_ASYNCPREDIV		127
#define RTC_SYNCPREDIV		255

#define RTC_HOURS			11
#define RTC_MINS			2
#define RTC_SECS			00

#define RTC_DATE			10
#define RTC_WEEKDAY			RTC_WEEKDAY_MONDAY
#define RTC_MONTH			RTC_MONTH_JUNE
#define RTC_YEAR			24

#define RTC_SET             0
/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern RTC_HandleTypeDef	rtc_cfg;
#if (RTC_SET == 1)
extern RTC_TimeTypeDef		rtc_time_cfg;
extern RTC_DateTypeDef		rtc_date_cfg;
#endif

#endif /* CONFIG_INC_RTC_CFG_H_ */
