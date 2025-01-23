/*
 * @filename	fault_monitor.h
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		fault_monitor
 * 
 * @brief		Add the description
 */
#ifndef APPLICATION_INC_FAULT_MONITOR_H_
#define APPLICATION_INC_FAULT_MONITOR_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "fault_cfg.h"
#include "database.h"
#include "fault_manager.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t WARNING_ARRAY[16];

/*---------------------------------------Function Prototypes-------------------------------------------*/

void FAULT_VoltageMonitor(DATABASE_VOLTAGE_s *database, DATABASE_BMS_s *database_bms);

void FAULT_TemperatureMonitor(DATABASE_TEMPERATURE_s *database, DATABASE_BMS_s *database_bms);

void FAULT_CurrentMonitor(DATABASE_CURRENT_s *database, DATABASE_BMS_s *database_bms);

void FAULT_SOCMonitor(DATABASE_SOC_s *database, DATABASE_BMS_s *database_bms);

#endif /* APPLICATION_INC_FAULT_MONITOR_H_ */
