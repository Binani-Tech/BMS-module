/*
 * @filename	fault_manager.c
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		fault_manager
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "fault_manager.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_ERROR_s	fm_database_error = {0};
static DATABASE_BMS_s fm_database_bms = {0};
static DATABASE_EEPROM_s fm_database_eeprom = {0};

uint8_t FAULT_ARRAY[16] = {0};

static uint8_t current_error_count = 0;
static uint8_t temperature_error_count = 0;
static uint8_t voltage_error_count = 0;
bool check;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void FAULTMANAGER_Voltage(DATABASE_VOLTAGE_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_state != BMS_IDLE)
	{
			DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);

			/* Cell Over Voltage Error */
			if(fm_database_error.error_flag_ROL.cell_over_voltage == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_VOLTAGE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.cov_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.cell_over_voltage == FAULT || fm_database_error.error_flag_MSL.cell_over_voltage == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_CELL_OVER_VOLTAGE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_CELL_OVER_VOLTAGE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_CELL_OVER_VOLTAGE] = FAULT;
					voltage_error_count++;
					fm_database_eeprom.error_id = BMS_CELL_OVER_VOLTAGE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.cov_release_counter = 0;
				fm_database_error.error_release_counter_MSL.cov_release_counter = 0;
			}


			/* Pack Over Voltage Error */
			if(fm_database_error.error_flag_ROL.pack_over_voltage == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_VOLTAGE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.pov_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.pack_over_voltage == FAULT || fm_database_error.error_flag_MSL.pack_over_voltage == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_PACK_OVER_VOLTAGE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_PACK_OVER_VOLTAGE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_PACK_OVER_VOLTAGE] = FAULT;
					voltage_error_count++;
					fm_database_eeprom.error_id = BMS_PACK_OVER_VOLTAGE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.pov_release_counter = 0;
				fm_database_error.error_release_counter_MSL.pov_release_counter = 0;
			}

			/* Voltage Difference Error */
			if(fm_database_error.error_flag_ROL.voltage_difference == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_VOLTAGE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.cvd_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.voltage_difference == FAULT || fm_database_error.error_flag_MSL.voltage_difference == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_VOLTAGE_DIFFERENCE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_VOLTAGE_DIFFERENCE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_VOLTAGE_DIFFERENCE] = FAULT;
					voltage_error_count++;
					fm_database_eeprom.error_id = BMS_VOLTAGE_DIFFERENCE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.cvd_release_counter = 0;
				fm_database_error.error_release_counter_MSL.cvd_release_counter = 0;
			}

			/* Cell Under Voltage Error */
			if(fm_database_error.error_flag_ROL.cell_under_voltage == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_VOLTAGE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.cuv_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.cell_under_voltage == FAULT || fm_database_error.error_flag_MSL.cell_under_voltage == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_CELL_UNDER_VOLTAGE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_CELL_UNDER_VOLTAGE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_CELL_UNDER_VOLTAGE] = FAULT;
					voltage_error_count++;
					fm_database_eeprom.error_id = BMS_CELL_UNDER_VOLTAGE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					////EEPROM_Write();
				}
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.cuv_release_counter = 0;
				fm_database_error.error_release_counter_MSL.cuv_release_counter = 0;
			}

			/* Pack Under Voltage Error */
			if(fm_database_error.error_flag_ROL.pack_under_voltage == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_VOLTAGE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.puv_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.pack_under_voltage == FAULT || fm_database_error.error_flag_MSL.pack_under_voltage == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_PACK_UNDER_VOLTAGE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_PACK_UNDER_VOLTAGE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_PACK_UNDER_VOLTAGE] = FAULT;
					voltage_error_count++;
					fm_database_eeprom.error_id = BMS_PACK_UNDER_VOLTAGE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();

				}
				FAULTMANAGER_ClearVoltageFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.puv_release_counter = 0;
				fm_database_error.error_release_counter_MSL.puv_release_counter = 0;
			}

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);

	}
}


void FAULTMANAGER_ClearVoltageFlag(DATABASE_VOLTAGE_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_error_source.ERROR_VOLTAGE == FAULT)
	{
		DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
		DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Cell Over Voltage Release */
		if(fm_database_error.error_flag_ROL.cell_over_voltage == FAULT)
		{
			if(database->max_voltage < COV_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.cov_release_counter++;
				if(fm_database_error.error_release_counter_ROL.cov_release_counter > (COV_ROL_R_DELAY/VOLTAGE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_CELL_OVER_VOLTAGE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.cell_over_voltage = NO_FAULT;
						WARNING_ARRAY[FAULT_CELL_OVER_VOLTAGE] = NO_FAULT;
						voltage_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.cell_over_voltage == FAULT)
			{
				if(database->max_voltage < COV_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.cov_release_counter++;
					if(fm_database_error.error_release_counter_MOL.cov_release_counter > (COV_MOL_R_DELAY/VOLTAGE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.cell_over_voltage = NO_FAULT;
						FAULT_ARRAY[FAULT_CELL_OVER_VOLTAGE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.cov_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();

		}

		if(fm_database_error.error_flag_MSL.cell_over_voltage == FAULT)
		{
			if(database->max_voltage < COV_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.cov_release_counter++;
				if(fm_database_error.error_release_counter_MSL.cov_release_counter > (COV_MSL_R_DELAY/VOLTAGE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.cell_over_voltage = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.cov_release_counter = 0;
			}
		}
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Pack Over Voltage Error */
		if(fm_database_error.error_flag_ROL.pack_over_voltage == FAULT)
		{
			if(database->sum_voltage < POV_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.pov_release_counter++;
				if(fm_database_error.error_release_counter_ROL.pov_release_counter > (POV_ROL_R_DELAY/VOLTAGE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_PACK_OVER_VOLTAGE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.pack_over_voltage = NO_FAULT;
						WARNING_ARRAY[FAULT_PACK_OVER_VOLTAGE] = NO_FAULT;
						voltage_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.pack_over_voltage == FAULT)
			{
				if(database->sum_voltage < POV_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.pov_release_counter++;
					if(fm_database_error.error_release_counter_MOL.pov_release_counter > (POV_MOL_R_DELAY/VOLTAGE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.pack_over_voltage = NO_FAULT;
						FAULT_ARRAY[FAULT_PACK_OVER_VOLTAGE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.pov_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.pack_over_voltage == FAULT)
		{
			if(database->sum_voltage < POV_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.pov_release_counter++;
				if(fm_database_error.error_release_counter_MSL.pov_release_counter > (POV_MSL_R_DELAY/VOLTAGE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.pack_over_voltage = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.pov_release_counter = 0;
			}
		}
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Voltage Difference Error */
		if(fm_database_error.error_flag_ROL.voltage_difference == FAULT)
		{
			if(database->diff_voltage < CVD_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.cvd_release_counter++;
				if(fm_database_error.error_release_counter_ROL.cvd_release_counter > (CVD_ROL_R_DELAY/VOLTAGE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_VOLTAGE_DIFFERENCE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.voltage_difference = NO_FAULT;
						WARNING_ARRAY[FAULT_VOLTAGE_DIFFERENCE] = NO_FAULT;
						voltage_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.voltage_difference == FAULT)
			{
				if(database->diff_voltage < CVD_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.cvd_release_counter++;
					if(fm_database_error.error_release_counter_MOL.cvd_release_counter > (CVD_MOL_R_DELAY/VOLTAGE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.voltage_difference = NO_FAULT;
						FAULT_ARRAY[FAULT_VOLTAGE_DIFFERENCE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.cvd_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.voltage_difference == FAULT)
		{
			if(database->diff_voltage < CVD_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.cvd_release_counter++;
				if(fm_database_error.error_release_counter_MSL.cvd_release_counter > (CVD_MSL_R_DELAY/VOLTAGE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.voltage_difference = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.cvd_release_counter = 0;
			}
		}

		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Cell Under Voltage Error */
		if(fm_database_error.error_flag_ROL.cell_under_voltage == FAULT)
		{
			if(database->min_voltage > CUV_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.cuv_release_counter++;
				if(fm_database_error.error_release_counter_ROL.cuv_release_counter > (CUV_ROL_R_DELAY/VOLTAGE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_CELL_UNDER_VOLTAGE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.cell_under_voltage = NO_FAULT;
						WARNING_ARRAY[FAULT_CELL_UNDER_VOLTAGE] = NO_FAULT;
						voltage_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.cell_under_voltage == FAULT)
			{
				if(database->min_voltage > CUV_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.cuv_release_counter++;
					if(fm_database_error.error_release_counter_MOL.cuv_release_counter > (CUV_MOL_R_DELAY/VOLTAGE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.cell_under_voltage = NO_FAULT;
						FAULT_ARRAY[FAULT_CELL_UNDER_VOLTAGE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.cuv_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.cell_under_voltage == FAULT)
		{
			if(database->min_voltage > CUV_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.cuv_release_counter++;
				if(fm_database_error.error_release_counter_MSL.cuv_release_counter > (CUV_MSL_R_DELAY/VOLTAGE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.cell_under_voltage = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.cuv_release_counter = 0;
			}
		}

		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Pack Under Voltage Error */
		if(fm_database_error.error_flag_ROL.pack_under_voltage == FAULT)
		{
			if(database->sum_voltage > PUV_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.puv_release_counter++;
				if(fm_database_error.error_release_counter_ROL.puv_release_counter > (PUV_ROL_R_DELAY/VOLTAGE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_PACK_UNDER_VOLTAGE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.pack_under_voltage = NO_FAULT;
						WARNING_ARRAY[FAULT_PACK_UNDER_VOLTAGE] = NO_FAULT;
						voltage_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.pack_under_voltage == FAULT)
			{
				if(database->sum_voltage > PUV_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.puv_release_counter++;
					if(fm_database_error.error_release_counter_MOL.puv_release_counter > (PUV_MOL_R_DELAY/VOLTAGE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.pack_under_voltage = NO_FAULT;
						FAULT_ARRAY[FAULT_PACK_UNDER_VOLTAGE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.puv_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.pack_under_voltage == FAULT)
		{
			if(database->sum_voltage > PUV_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.puv_release_counter++;
				if(fm_database_error.error_release_counter_MSL.puv_release_counter > (PUV_MSL_R_DELAY/VOLTAGE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.pack_under_voltage = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.puv_release_counter = 0;
			}
		}

		if(voltage_error_count == 0) { fm_database_bms.bms_error_source.ERROR_VOLTAGE = NO_FAULT; }

		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
		DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);

	}
}

void FAULTMANAGER_Temperature(DATABASE_TEMPERATURE_s *database)
{
	DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_state != BMS_IDLE)
	{
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		if(fm_database_bms.bms_state != BMS_DISCHARGE)
		{
			DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);

			/* Charge Over Temperature Error */
			if(fm_database_error.error_flag_ROL.charge_over_temperature == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_TEMPERATURE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.otc_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.charge_over_temperature == FAULT || fm_database_error.error_flag_MSL.charge_over_temperature == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_CHARGE_OVER_TEMPERATURE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_CHARGE_OVER_TEMPERATURE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_CHARGE_OVER_TEMPERATURE] = FAULT;
					temperature_error_count++;
					fm_database_eeprom.error_id = BMS_CHARGE_OVER_TEMPERATURE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				GPIO_TogglePin(GPIO_PIN_BUZZER);
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.otc_release_counter = 0;
				fm_database_error.error_release_counter_MSL.otc_release_counter = 0;
			}

			/* Charge Under Temperature Error */
			if(fm_database_error.error_flag_ROL.charge_under_temperature == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_TEMPERATURE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.utc_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.charge_under_temperature == FAULT || fm_database_error.error_flag_MSL.charge_under_temperature == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_CHARGE_UNDER_TEMPERATURE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_CHARGE_UNDER_TEMPERATURE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_CHARGE_UNDER_TEMPERATURE] = FAULT;
					temperature_error_count++;
					fm_database_eeprom.error_id = BMS_CHARGE_UNDER_TEMPERATURE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.utc_release_counter = 0;
				fm_database_error.error_release_counter_MSL.utc_release_counter = 0;
			}


			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
		}
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		if(fm_database_bms.bms_state != BMS_CHARGE)
		{
			DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);

			/* Discharge Over Temperature Error */
			if(fm_database_error.error_flag_ROL.discharge_over_temperature == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_TEMPERATURE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.otd_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.discharge_over_temperature == FAULT || fm_database_error.error_flag_MSL.discharge_over_temperature == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_DISCHARGE_OVER_TEMPERATURE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_DISCHARGE_OVER_TEMPERATURE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_DISCHARGE_OVER_TEMPERATURE] = FAULT;
					temperature_error_count++;
					fm_database_eeprom.error_id = BMS_DISCHARGE_OVER_TEMPERATURE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				GPIO_TogglePin(GPIO_PIN_BUZZER);
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.otd_release_counter = 0;
				fm_database_error.error_release_counter_MSL.otd_release_counter = 0;
			}

			/* Discharge Under Temperature Error */
			if(fm_database_error.error_flag_ROL.discharge_under_temperature == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_TEMPERATURE = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.utd_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.discharge_under_temperature == FAULT || fm_database_error.error_flag_MSL.discharge_under_temperature == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error = BMS_DISCHARGE_UNDER_TEMPERATURE;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_DISCHARGE_UNDER_TEMPERATURE] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					FAULT_ARRAY[FAULT_DISCHARGE_UNDER_TEMPERATURE] = FAULT;
					temperature_error_count++;
					fm_database_eeprom.error_id = BMS_DISCHARGE_UNDER_TEMPERATURE;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearTemperatureFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.utd_release_counter = 0;
				fm_database_error.error_release_counter_MSL.utd_release_counter = 0;
			}

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
		}
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
	}
}

void FAULTMANAGER_ClearTemperatureFlag(DATABASE_TEMPERATURE_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_error_source.ERROR_TEMPERATURE == FAULT)
	{
		DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
		DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Charge Over Temperature Error */
		if(fm_database_error.error_flag_ROL.charge_over_temperature == FAULT)
		{
			if(database->max_temperature < OTC_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.otc_release_counter++;
				if(fm_database_error.error_release_counter_ROL.otc_release_counter > (OTC_ROL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_CHARGE_OVER_TEMPERATURE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.charge_over_temperature = NO_FAULT;
						WARNING_ARRAY[FAULT_CHARGE_OVER_TEMPERATURE] = NO_FAULT;
						temperature_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.charge_over_temperature == FAULT)
			{
				if(database->max_temperature < OTC_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.otc_release_counter++;
					if(fm_database_error.error_release_counter_MOL.otc_release_counter > (OTC_MOL_R_DELAY/TEMPERATURE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.charge_over_temperature = NO_FAULT;
						FAULT_ARRAY[FAULT_CHARGE_OVER_TEMPERATURE] = NO_FAULT;
						GPIO_WritePin(GPIO_PIN_BUZZER, 0);
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.otc_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.charge_over_temperature == FAULT)
		{
			if(database->max_temperature < OTC_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.otc_release_counter++;
				if(fm_database_error.error_release_counter_MSL.otc_release_counter > (OTC_MSL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.charge_over_temperature = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.otc_release_counter = 0;
			}
		}

		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Charge Under Temperature Error */
		if(fm_database_error.error_flag_ROL.charge_under_temperature== FAULT)
		{
			if(database->min_temperature > UTC_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.utc_release_counter++;
				if(fm_database_error.error_release_counter_ROL.utc_release_counter > (UTC_ROL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_CHARGE_UNDER_TEMPERATURE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.charge_under_temperature = NO_FAULT;
						WARNING_ARRAY[FAULT_CHARGE_UNDER_TEMPERATURE] = NO_FAULT;
						temperature_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.charge_under_temperature == FAULT)
			{
				if(database->min_temperature > UTC_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.utc_release_counter++;
					if(fm_database_error.error_release_counter_MOL.utc_release_counter > (UTC_MOL_R_DELAY/TEMPERATURE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.charge_under_temperature = NO_FAULT;
						FAULT_ARRAY[FAULT_CHARGE_UNDER_TEMPERATURE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.utc_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.charge_under_temperature == FAULT)
		{
			if(database->min_temperature > UTC_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.utc_release_counter++;
				if(fm_database_error.error_release_counter_MSL.utc_release_counter > (UTC_MSL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.charge_under_temperature = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.utc_release_counter = 0;
			}
		}

		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Discharge Over Temperature Error */
		if(fm_database_error.error_flag_ROL.discharge_over_temperature == FAULT)
		{
			if(database->max_temperature < OTD_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.otd_release_counter++;
				if(fm_database_error.error_release_counter_ROL.otd_release_counter > (OTD_ROL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_DISCHARGE_OVER_TEMPERATURE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.discharge_over_temperature = NO_FAULT;
						WARNING_ARRAY[FAULT_DISCHARGE_OVER_TEMPERATURE] = NO_FAULT;
						temperature_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.discharge_over_temperature == FAULT)
			{
				if(database->max_temperature < OTD_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.otd_release_counter++;
					if(fm_database_error.error_release_counter_MOL.otd_release_counter > (OTD_MOL_R_DELAY/TEMPERATURE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.discharge_over_temperature = NO_FAULT;
						FAULT_ARRAY[FAULT_DISCHARGE_OVER_TEMPERATURE] = NO_FAULT;
						GPIO_WritePin(GPIO_PIN_BUZZER, 0);
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.otd_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.discharge_over_temperature == FAULT)
		{
			if(database->max_temperature < OTD_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.otd_release_counter++;
				if(fm_database_error.error_release_counter_MSL.otd_release_counter > (OTD_MSL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.discharge_over_temperature = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.otd_release_counter = 0;
			}
		}

		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/* Discharge Under Temperature Error */
		if(fm_database_error.error_flag_ROL.discharge_under_temperature== FAULT)
		{
			if(database->min_temperature > UTD_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.utd_release_counter++;
				if(fm_database_error.error_release_counter_ROL.utd_release_counter > (UTD_ROL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_DISCHARGE_UNDER_TEMPERATURE] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.discharge_under_temperature = NO_FAULT;
						WARNING_ARRAY[FAULT_DISCHARGE_UNDER_TEMPERATURE] = NO_FAULT;
						temperature_error_count--;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}

			if(fm_database_error.error_flag_MOL.discharge_under_temperature == FAULT)
			{
				if(database->min_temperature > UTD_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.utd_release_counter++;
					if(fm_database_error.error_release_counter_MOL.utd_release_counter > (UTD_MOL_R_DELAY/TEMPERATURE_SAMPLING))
					{
						fm_database_error.error_flag_MOL.discharge_under_temperature = NO_FAULT;
						FAULT_ARRAY[FAULT_DISCHARGE_UNDER_TEMPERATURE] = NO_FAULT;
						FAULTMANAGER_ClearFault();
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.utd_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_MSL.discharge_under_temperature == FAULT)
		{
			if(database->min_temperature > UTD_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.utd_release_counter++;
				if(fm_database_error.error_release_counter_MSL.utd_release_counter > (UTD_MSL_R_DELAY/TEMPERATURE_SAMPLING))
				{
					fm_database_error.error_flag_MSL.discharge_under_temperature = NO_FAULT;
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.utd_release_counter = 0;
			}
		}
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		if(temperature_error_count == 0) { fm_database_bms.bms_error_source.ERROR_TEMPERATURE = NO_FAULT; }

		DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
		DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
	}
}


void FAULTMANAGER_Current(DATABASE_CURRENT_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_state != BMS_IDLE)
	{
		if(fm_database_bms.bms_state != BMS_CHARGE)
		{
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
			DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
			/* Discharge Over Current Fault */
			if(fm_database_error.error_flag_ROL.discharge_over_current == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_CURRENT = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearCurrentFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.ocd_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.discharge_over_current == FAULT || fm_database_error.error_flag_MSL.discharge_over_current == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error_source.ERROR_CURRENT = FAULT;
				fm_database_bms.bms_error = BMS_DISCHARGE_OVER_CURRENT;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					FAULT_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] = FAULT;
					current_error_count = 1;
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					fm_database_eeprom.error_id = BMS_DISCHARGE_OVER_CURRENT;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearCurrentFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.ocd_release_counter = 0;
				fm_database_error.error_release_counter_MSL.ocd_release_counter = 0;
			}

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);

/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		}

		if(fm_database_bms.bms_state != BMS_DISCHARGE)
		{
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
			DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
			/* Charge Over Current Error */
			if(fm_database_error.error_flag_ROL.charge_over_current == FAULT)
			{
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);
				fm_database_bms.bms_error_source.ERROR_CURRENT = FAULT;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				FAULTMANAGER_ClearCurrentFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.occ_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.charge_over_current == FAULT || fm_database_error.error_flag_MSL.charge_over_current == FAULT)
			{
				DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
				fm_database_bms.bms_error_source.ERROR_CURRENT = FAULT;
				fm_database_bms.bms_error = BMS_CHARGE_OVER_CURRENT;
				fm_database_bms.bms_state = BMS_ERROR;
				DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
				GPIO_WritePin(GPIO_PIN_FAULT_LED, 0);

				if(FAULT_ARRAY[FAULT_CHARGE_OVER_CURRENT] != FAULT)
				{
					CONT_StateRequest(CONT_ERROR);
					FAULT_ARRAY[FAULT_CHARGE_OVER_CURRENT] = FAULT;
					current_error_count = 1;;
					DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					fm_database_eeprom.error_id = BMS_CHARGE_OVER_CURRENT;
					DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);
					//EEPROM_Write();
				}
				FAULTMANAGER_ClearCurrentFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.occ_release_counter = 0;
				fm_database_error.error_release_counter_MSL.occ_release_counter = 0;
			}

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
		}

		if(short_circuit == 1)
		{
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
			DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

			fm_database_bms.bms_error = BMS_SHORT_CIRCUIT;
			fm_database_bms.bms_state = BMS_ERROR;
			FAULT_ARRAY[FAULT_SHORT_CIRCUIT] = FAULT;
			WARNING_ARRAY[FAULT_SHORT_CIRCUIT] = FAULT;
			fm_database_error.error_flag_MOL.short_circuit = FAULT;
//			CAN_Send_Fault_1();
//			CAN_Send_Fault_2();
//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
			DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
		}
		else if(short_circuit == 0)
		{
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);

			fm_database_error.error_flag_MOL.short_circuit = NO_FAULT;
			FAULT_ARRAY[FAULT_SHORT_CIRCUIT] = NO_FAULT;
			WARNING_ARRAY[FAULT_SHORT_CIRCUIT] = NO_FAULT;

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
		}

	}
}

void FAULTMANAGER_ClearCurrentFlag(DATABASE_CURRENT_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_error_source.ERROR_CURRENT == FAULT)
	{
		DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);
		DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

		/* Discharge Over Current Error */
		if(fm_database_error.error_flag_ROL.discharge_over_current == FAULT)
		{
			if(database->pack_current > OCD_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.ocd_release_counter++;
				if(fm_database_error.error_release_counter_ROL.ocd_release_counter > (OCD_ROL_R_DELAY/CURRENT_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.discharge_over_current = NO_FAULT;
						WARNING_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] = NO_FAULT;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}
		}

		if(fm_database_error.error_flag_MOL.discharge_over_current == FAULT)
		{
			if(database->pack_current > OCD_MOL_R)
			{
				fm_database_error.error_release_counter_MOL.ocd_release_counter++;
				if(fm_database_error.error_release_counter_MOL.ocd_release_counter > (OCD_MOL_R_DELAY/CURRENT_SAMPLING))
				{
					fm_database_error.error_flag_MOL.discharge_over_current = NO_FAULT;
					FAULT_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] = NO_FAULT;
					current_error_count = 0;
					FAULTMANAGER_ClearFault();
				}
			}
			else
			{
				fm_database_error.error_release_counter_MOL.ocd_release_counter = 0;
			}
		}

		if(fm_database_error.error_flag_MSL.discharge_over_current == FAULT)
		{
			if(database->pack_current > OCD_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.ocd_release_counter++;
				if(fm_database_error.error_release_counter_MSL.ocd_release_counter > (OCD_MSL_R_DELAY/CURRENT_SAMPLING))
				{
					fm_database_error.error_flag_MSL.discharge_over_current = NO_FAULT;
					FAULT_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] = NO_FAULT;
					FAULTMANAGER_ClearFault();
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.ocd_release_counter = 0;
			}
		}

		/* Charge Over Current Error */
		if(fm_database_error.error_flag_ROL.charge_over_current == FAULT)
		{
			if(database->pack_current < OCC_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.occ_release_counter++;
				if(fm_database_error.error_release_counter_ROL.occ_release_counter > (OCC_ROL_R_DELAY/CURRENT_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_CHARGE_OVER_CURRENT] == FAULT)
					{
						fm_database_error.error_flag_ROL.charge_over_current = NO_FAULT;
						WARNING_ARRAY[FAULT_CHARGE_OVER_CURRENT] = NO_FAULT;
						GPIO_WritePin(GPIO_PIN_FAULT_LED, 1);
					}
				}
			}
		}

		if(fm_database_error.error_flag_MOL.charge_over_current == FAULT)
		{
			if(database->pack_current < OCC_MOL_R)
			{
				fm_database_error.error_release_counter_MOL.occ_release_counter++;
				if(fm_database_error.error_release_counter_MOL.occ_release_counter > (OCC_MOL_R_DELAY/CURRENT_SAMPLING))
				{
					fm_database_error.error_flag_MOL.charge_over_current = NO_FAULT;
					FAULT_ARRAY[FAULT_CHARGE_OVER_CURRENT] = NO_FAULT;
					current_error_count = 0;
					FAULTMANAGER_ClearFault();
				}
			}
			else
			{
				fm_database_error.error_release_counter_MOL.occ_release_counter = 0;
			}
		}

		if(fm_database_error.error_flag_MSL.charge_over_current == FAULT)
		{
			if(database->pack_current < OCC_MSL_R)
			{
				fm_database_error.error_release_counter_MSL.occ_release_counter++;
				if(fm_database_error.error_release_counter_MSL.occ_release_counter > (OCC_MSL_R_DELAY/CURRENT_SAMPLING))
				{
					fm_database_error.error_flag_MSL.charge_over_current = NO_FAULT;
					FAULT_ARRAY[FAULT_CHARGE_OVER_CURRENT] = NO_FAULT;
					FAULTMANAGER_ClearFault();
				}
			}
			else
			{
				fm_database_error.error_release_counter_MSL.occ_release_counter = 0;
			}
		}

		if(current_error_count == 0) { fm_database_bms.bms_error_source.ERROR_CURRENT = NO_FAULT; }
		else { fm_database_bms.bms_error_source.ERROR_CURRENT = FAULT; }

		DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
		DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
	}
}

void FAULTMANAGER_SOC(DATABASE_SOC_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_state != BMS_IDLE)
	{
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
			DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);

			/* SOC High Error */
			if(fm_database_error.error_flag_ROL.soc_high == FAULT)
			{
				FAULTMANAGER_ClearSOCFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.soch_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.soc_high == FAULT)
			{
				FAULT_ARRAY[FAULT_SOC_HIGH] = FAULT;
				FAULTMANAGER_ClearSOCFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.soch_release_counter = 0;
			}

			/* SOC Low Error */
			if(fm_database_error.error_flag_ROL.soc_low == FAULT)
			{
				FAULTMANAGER_ClearSOCFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_ROL.socl_release_counter = 0;
			}

			if(fm_database_error.error_flag_MOL.soc_low == FAULT || fm_database_error.error_flag_MSL.soc_low == FAULT)
			{
				FAULT_ARRAY[FAULT_SOC_LOW] = FAULT;
				FAULTMANAGER_ClearSOCFlag(database);
			}
			else
			{
				fm_database_error.error_release_counter_MOL.socl_release_counter = 0;
			}

			DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
	}
}

void FAULTMANAGER_ClearSOCFlag(DATABASE_SOC_s *database)
{
	DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);

	if(fm_database_bms.bms_state != BMS_IDLE)
	{
		/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
		DATABASE_READ((void*)(&fm_database_error), DATABASE_ERROR);

		if(fm_database_error.error_flag_ROL.soc_high == FAULT)
		{
			if(database->soc < SOCH_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.soch_release_counter++;
				if(fm_database_error.error_release_counter_ROL.soch_release_counter > (SOCH_ROL_R_DELAY/SOC_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_SOC_HIGH] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.soc_high = NO_FAULT;
						WARNING_ARRAY[FAULT_SOC_HIGH] = NO_FAULT;
					}
				}
			}

			if(fm_database_error.error_flag_MOL.soc_high == FAULT)
			{
				if(database->soc < SOCH_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.soch_release_counter++;
					if(fm_database_error.error_release_counter_MOL.soch_release_counter > (SOCH_MOL_R_DELAY/SOC_SAMPLING))
					{
						fm_database_error.error_flag_MOL.soc_high = NO_FAULT;
						FAULT_ARRAY[FAULT_SOC_HIGH] = NO_FAULT;
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.soch_release_counter = 0;
				}

//				CAN_Send_Fault_1();
//				CAN_Send_Fault_2();
			}

//			CAN_Send_Warning_1();
//			CAN_Send_Warning_2();
		}

		if(fm_database_error.error_flag_ROL.soc_low == FAULT)
		{
			if(database->soc > SOCL_ROL_R)
			{
				fm_database_error.error_release_counter_ROL.socl_release_counter++;
				if(fm_database_error.error_release_counter_ROL.socl_release_counter > (SOCL_ROL_R_DELAY/SOC_SAMPLING))
				{
					if(FAULT_ARRAY[FAULT_SOC_LOW] == NO_FAULT)
					{
						fm_database_error.error_flag_ROL.soc_low = NO_FAULT;
						WARNING_ARRAY[FAULT_SOC_LOW] = NO_FAULT;
					}
				}
			}

			if(fm_database_error.error_flag_MOL.soc_low == FAULT)
			{
				if(database->soc > SOCL_MOL_R)
				{
					fm_database_error.error_release_counter_MOL.socl_release_counter++;
					if(fm_database_error.error_release_counter_MOL.socl_release_counter > (SOCL_MOL_R_DELAY/SOC_SAMPLING))
					{
						fm_database_error.error_flag_MOL.soc_low = NO_FAULT;
						FAULT_ARRAY[FAULT_SOC_LOW] = NO_FAULT;
					}
				}
				else
				{
					fm_database_error.error_release_counter_MOL.socl_release_counter = 0;
				}

//				CAN_Send_Fault();
			}

//			CAN_Send_Warning();
		}

		DATABASE_WRITE((void*)(&fm_database_error), DATABASE_ERROR);
	}
}

void FAULTMANAGER_ClearFault(void)
{
	if(FAULTMANAGER_CheckFaults() == NO_FAULT) {
		DATABASE_READ((void*)(&fm_database_bms), DATABASE_BMS);
		DATABASE_READ((void*)(&fm_database_eeprom), DATABASE_EEPROM);
		fm_database_bms.bms_error = BMS_NO_ERR;
		fm_database_bms.bms_state = BMS_STANDBY;
		fm_database_eeprom.error_id = BMS_NO_ERR;

		DATABASE_WRITE((void*)(&fm_database_bms), DATABASE_BMS);
		DATABASE_WRITE((void*)(&fm_database_eeprom), DATABASE_EEPROM);

		CONT_StateRequest(CONT_NORMAL);
		//EEPROM_Write();
	}
}

uint8_t FAULTMANAGER_CheckFaults(void)
{
	uint8_t fault_count = 0;

	for(uint8_t i=0; i<11; i++)
	{
		if(FAULT_ARRAY[i] == FAULT){ fault_count++; }
	}

	if(fault_count == NO_FAULT){ return NO_FAULT; }
	else{ return FAULT; }
}
