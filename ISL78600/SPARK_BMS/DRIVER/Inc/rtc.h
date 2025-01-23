/*
 * @filename	rtc.h
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rtc
 * 
 * @brief		Add the description
 */
#ifndef DRIVERS_INC_RTC_H_
#define DRIVERS_INC_RTC_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "rtc_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void RTC_Init(void);
void RTC_SetTime(RTC_TimeTypeDef *time);
void RTC_SetDate(RTC_DateTypeDef *date);
void RTC_GetTime(RTC_TimeTypeDef *time);
void RTC_GetDate(RTC_DateTypeDef *date);


#endif /* DRIVERS_INC_RTC_H_ */
