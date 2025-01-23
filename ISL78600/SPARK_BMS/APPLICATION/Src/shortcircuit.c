/*
 * @filename	shortcircuit.c
 * @author		SPARKBMS TEAM
 * @date		01-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		shortcircuit
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "shortcircuit.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_BMS_s sc_database_bms = {0};
static DATABASE_EEPROM_s sc_database_eeprom = {0};
static uint16_t short_circuit_counter = 0;
/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void SHORTCIRCUIT_FaultManager(int32_t *Current)
{
	GPIO_WritePin(GPIO_PIN_LED, 1);
	CONT_StateRequest(CONT_ERROR);
	DATABASE_READ((void*)(&sc_database_eeprom), DATABASE_EEPROM);
	sc_database_eeprom.error_id = BMS_SHORT_CIRCUIT;
	sc_database_eeprom.current = *Current;
	DATABASE_WRITE((void*)(&sc_database_eeprom), DATABASE_EEPROM);
//	EEPROM_Write();
}

void SHORTCIRCUIT_ClearFault(int32_t *Current)
{
	if(*Current < SC_MSL)
	{
		short_circuit_counter++;
		if(short_circuit_counter > (SC_MSL_DELAY*10/4))
		{
			CONT_StateRequest(CONT_NORMAL);
			DATABASE_READ((void*)(&sc_database_bms), DATABASE_BMS);
			sc_database_bms.bms_error = BMS_NO_ERR;
			sc_database_bms.bms_state = BMS_STANDBY;
			DATABASE_WRITE((void*)(&sc_database_bms), DATABASE_BMS);
			DATABASE_READ((void*)(&sc_database_eeprom), DATABASE_EEPROM);
			sc_database_eeprom.error_id = BMS_NO_ERR;
			sc_database_eeprom.current = *Current;
			DATABASE_WRITE((void*)(&sc_database_eeprom), DATABASE_EEPROM);
//			EEPROM_Write();
			GPIO_WritePin(GPIO_PIN_LED, 0);
			short_circuit = 0;
			short_circuit_counter = 0;
		}
	}
}
