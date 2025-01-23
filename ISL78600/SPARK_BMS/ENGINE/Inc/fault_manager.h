/*
 * @filename	fault_manager.h
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		fault_manager
 * 
 * @brief		Add the description
 */
#ifndef ENGINE_INC_FAULT_MANAGER_H_
#define ENGINE_INC_FAULT_MANAGER_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "fault_cfg.h"
#include "fault_monitor.h"
#include "contactor.h"
#include "database.h"
#include "eeprom.h"
#include "can.h"
#include "isl78600.h"

/*---------------------------------------Macros--------------------------------------------------------*/

typedef enum
{
	FAULT_CELL_OVER_VOLTAGE 				= 0,
	FAULT_CELL_UNDER_VOLTAGE 				= 1,
	FAULT_PACK_OVER_VOLTAGE 				= 2,
	FAULT_PACK_UNDER_VOLTAGE 				= 3,
	FAULT_CHARGE_OVER_CURRENT 				= 4,
	FAULT_DISCHARGE_OVER_CURRENT 			= 5,
	FAULT_CHARGE_OVER_TEMPERATURE 			= 6,
	FAULT_CHARGE_UNDER_TEMPERATURE 			= 7,
	FAULT_DISCHARGE_OVER_TEMPERATURE 		= 8,
	FAULT_DISCHARGE_UNDER_TEMPERATURE 		= 9,
	FAULT_VOLTAGE_DIFFERENCE 				= 10,
	FAULT_SOC_HIGH 							= 11,
	FAULT_SOC_LOW 							= 12,
	FAULT_SHORT_CIRCUIT 					= 13
}FAULTS_e;

/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t FAULT_ARRAY[16];

/*---------------------------------------Function Prototypes-------------------------------------------*/

void FAULTMANAGER_Voltage(DATABASE_VOLTAGE_s *database);

void FAULTMANAGER_ClearVoltageFlag(DATABASE_VOLTAGE_s *database);

void FAULTMANAGER_Temperature(DATABASE_TEMPERATURE_s *database);

void FAULTMANAGER_ClearTemperatureFlag(DATABASE_TEMPERATURE_s *database);

void FAULTMANAGER_Current(DATABASE_CURRENT_s *database);

void FAULTMANAGER_ClearCurrentFlag(DATABASE_CURRENT_s *database);

void FAULTMANAGER_SOC(DATABASE_SOC_s *database);

void FAULTMANAGER_ClearSOCFlag(DATABASE_SOC_s *database);

uint8_t FAULTMANAGER_CheckFaults(void);

void FAULTMANAGER_ClearFault(void);

#endif /* ENGINE_INC_FAULT_MANAGER_H_ */
