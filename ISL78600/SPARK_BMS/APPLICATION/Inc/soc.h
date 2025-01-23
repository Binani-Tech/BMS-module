/*
 * @filename	soc.h
 * @author		SPARKBMS TEAM
 * @date		03-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		soc
 * 
 * @brief		Add the description
 */
#ifndef APPLICATION_INC_SOC_H_
#define APPLICATION_INC_SOC_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "database.h"
#include "fault_monitor.h"
#include "isl78600.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define BATTERY_CAPACITY		105			// Unit : Ah

#define BATTERY_WH		        70000

#define CURRENT_UPDATE_TIME		100			// Unit : ms

#define BATTERY_KWH             32.235
/*---------------------------------------Variables-----------------------------------------------------*/

extern uint16_t CKWH;
/*---------------------------------------Function Prototypes-------------------------------------------*/

void SOC_Init(void);

void SOC_Update(void);

void SOH_Update(void);

#endif /* APPLICATION_INC_SOC_H_ */
