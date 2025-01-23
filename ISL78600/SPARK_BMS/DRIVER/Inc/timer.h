/*
 * @filename	timer.h
 * @author		SPARKBMS TEAM
 * @date		Apr 15, 2023
 * @ingroup		FOLDER NAME
 * @prefix		timer
 * 
 * @brief		Add the description
 */
#ifndef DRIVERS_INC_TIMER_H_
#define DRIVERS_INC_TIMER_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "timer_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void BASIC_TIMER_Init(void);

void TIMER_Delay_us(uint16_t micros);

void TIMER_Delay_ms(uint16_t millis);

void GENERAL_TIMER_Init(void);

void TIMER7_Init(void);

void TIMER7_Start(void);

void TIMER7_Stop(void);

void TIMER7_Reset(void);

#endif /* DRIVERS_INC_TIMER_H_ */
