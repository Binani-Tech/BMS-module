/*
 * @filename	fault_monitor.c
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		fault_monitor
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "fault_monitor.h"
#include "fault_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_ERROR_s	fmon_database_error = {0};

uint8_t WARNING_ARRAY[16] = {0};

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void FAULT_VoltageMonitor(DATABASE_VOLTAGE_s *database, DATABASE_BMS_s *database_bms)
{
	if(database_bms->bms_state != BMS_IDLE)
	{
		DATABASE_READ((void*)(&fmon_database_error), DATABASE_ERROR);

		/* Cell Over Voltage Error */
		if (database->max_voltage > COV_ROL)
		{
			fmon_database_error.error_counter_ROL.cov_counter++;
			if(fmon_database_error.error_counter_ROL.cov_counter > (COV_ROL_DELAY/VOLTAGE_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.cell_over_voltage = FAULT;
				WARNING_ARRAY[FAULT_CELL_OVER_VOLTAGE] = FAULT;
			}

			if(database->max_voltage > COV_MOL)
			{
				fmon_database_error.error_counter_MOL.cov_counter++;
				if(fmon_database_error.error_counter_MOL.cov_counter > (COV_MOL_DELAY/VOLTAGE_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.cell_over_voltage = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.cov_counter = 0;
			}

			if(database->max_voltage > COV_MSL)
			{
				fmon_database_error.error_flag_ROL.cell_over_voltage = FAULT;
				fmon_database_error.error_flag_MOL.cell_over_voltage = FAULT;
				fmon_database_error.error_flag_MSL.cell_over_voltage = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.cov_counter = 0;
			fmon_database_error.error_counter_MOL.cov_counter = 0;
		}

		/* Pack Over Voltage Error */
		if(database->sum_voltage > POV_ROL)
		{
			fmon_database_error.error_counter_ROL.pov_counter ++;
			if(fmon_database_error.error_counter_ROL.pov_counter > (POV_ROL_DELAY/VOLTAGE_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.pack_over_voltage = FAULT;
				WARNING_ARRAY[FAULT_PACK_OVER_VOLTAGE] = FAULT;
			}

			if(database->sum_voltage > POV_MOL)
			{
				fmon_database_error.error_counter_MOL.pov_counter++;
				if(fmon_database_error.error_counter_MOL.pov_counter > (POV_MOL_DELAY/VOLTAGE_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.pack_over_voltage = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.pov_counter = 0;
			}

			if(database->sum_voltage > POV_MSL)
			{
				fmon_database_error.error_flag_ROL.pack_over_voltage = FAULT;
				fmon_database_error.error_flag_MOL.pack_over_voltage = FAULT;
				fmon_database_error.error_flag_MSL.pack_over_voltage = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.pov_counter = 0;
			fmon_database_error.error_counter_MOL.pov_counter = 0;
		}

		/* Cell Voltage Difference Error */
		if(database->diff_voltage > CVD_ROL)
		{
			fmon_database_error.error_counter_ROL.cvd_counter++;
			if(fmon_database_error.error_counter_ROL.cvd_counter > (CVD_ROL_DELAY/VOLTAGE_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.voltage_difference = FAULT;
				WARNING_ARRAY[FAULT_VOLTAGE_DIFFERENCE] = FAULT;
			}

			if(database->diff_voltage > CVD_MOL)
			{
				fmon_database_error.error_counter_MOL.cvd_counter++;
				if(fmon_database_error.error_counter_MOL.cvd_counter > (CVD_MOL_DELAY/VOLTAGE_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.voltage_difference = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.cvd_counter = 0;
			}

			if(database->diff_voltage > CVD_MSL)
			{
				fmon_database_error.error_flag_ROL.voltage_difference = FAULT;
				fmon_database_error.error_flag_MOL.voltage_difference = FAULT;
				fmon_database_error.error_flag_MSL.voltage_difference = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.cvd_counter = 0;
			fmon_database_error.error_counter_MOL.cvd_counter = 0;
		}

		/* Cell Under Voltage Error */
		if (database->min_voltage < CUV_ROL)
		{
			fmon_database_error.error_counter_ROL.cuv_counter++;
			if(fmon_database_error.error_counter_ROL.cuv_counter > (CUV_ROL_DELAY/VOLTAGE_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.cell_under_voltage = FAULT;
				WARNING_ARRAY[FAULT_CELL_UNDER_VOLTAGE] = FAULT;
			}

			if(database->min_voltage < CUV_MOL)
			{
				fmon_database_error.error_counter_MOL.cuv_counter++;
				if(fmon_database_error.error_counter_MOL.cuv_counter > (CUV_MOL_DELAY/VOLTAGE_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.cell_under_voltage = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.cuv_counter = 0;
			}

			if(database->min_voltage < CUV_MSL)
			{
				fmon_database_error.error_flag_ROL.cell_under_voltage = FAULT;
				fmon_database_error.error_flag_MOL.cell_under_voltage = FAULT;
				fmon_database_error.error_flag_MSL.cell_under_voltage = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.cuv_counter = 0;
			fmon_database_error.error_counter_MOL.cuv_counter = 0;
		}

		/* Pack Under Voltage Error */
		if(database->sum_voltage < PUV_ROL)
		{
			fmon_database_error.error_counter_ROL.puv_counter ++;
			if(fmon_database_error.error_counter_ROL.puv_counter > (PUV_ROL_DELAY/VOLTAGE_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.pack_under_voltage = FAULT;
				WARNING_ARRAY[FAULT_PACK_UNDER_VOLTAGE] = FAULT;
			}

			if(database->sum_voltage < PUV_MOL)
			{
				fmon_database_error.error_counter_MOL.puv_counter++;
				if(fmon_database_error.error_counter_MOL.puv_counter > (PUV_MOL_DELAY/VOLTAGE_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.pack_under_voltage = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.puv_counter = 0;
			}

			if(database->sum_voltage < PUV_MSL)
			{
				fmon_database_error.error_flag_ROL.pack_under_voltage = FAULT;
				fmon_database_error.error_flag_MOL.pack_under_voltage = FAULT;
				fmon_database_error.error_flag_MSL.pack_under_voltage = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.puv_counter = 0;
			fmon_database_error.error_counter_MOL.puv_counter = 0;
		}

		DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);

		FAULTMANAGER_Voltage(database);

	}

}

void FAULT_TemperatureMonitor(DATABASE_TEMPERATURE_s *database, DATABASE_BMS_s *database_bms)
{
	if(database_bms->bms_state != BMS_IDLE)
	{
		if(database_bms->bms_state != BMS_DISCHARGE)
		{
			DATABASE_READ((void*)(&fmon_database_error), DATABASE_ERROR);

			/* Over Temperature Charge */
			if(database->max_temperature > OTC_ROL)
			{
				fmon_database_error.error_counter_ROL.otc_counter++;
				if(fmon_database_error.error_counter_ROL.otc_counter > (OTC_ROL_DELAY/TEMPERATURE_SAMPLING))
				{
					fmon_database_error.error_flag_ROL.charge_over_temperature = FAULT;
					WARNING_ARRAY[FAULT_CHARGE_OVER_TEMPERATURE] = FAULT;
				}

				if(database->max_temperature > OTC_MOL)
				{
					fmon_database_error.error_counter_MOL.otc_counter++;
					if(fmon_database_error.error_counter_MOL.otc_counter > (OTC_MOL_DELAY/TEMPERATURE_SAMPLING))
					{
						fmon_database_error.error_flag_MOL.charge_over_temperature = FAULT;
					}
				}
				else
				{
					fmon_database_error.error_counter_MOL.otc_counter = 0;
				}

				if(database->max_temperature > OTC_MSL)
				{
					fmon_database_error.error_flag_ROL.charge_over_temperature = FAULT;
					fmon_database_error.error_flag_MOL.charge_over_temperature = FAULT;
					fmon_database_error.error_flag_MSL.charge_over_temperature = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_ROL.otc_counter = 0;
				fmon_database_error.error_counter_MOL.otc_counter = 0;
			}

			/* Under Temperature Charge */
			if(database->min_temperature < UTC_ROL)
			{
				fmon_database_error.error_counter_ROL.utc_counter++;
				if(fmon_database_error.error_counter_ROL.utc_counter > (UTC_ROL_DELAY/TEMPERATURE_SAMPLING))
				{
					fmon_database_error.error_flag_ROL.charge_under_temperature = FAULT;
					WARNING_ARRAY[FAULT_CHARGE_UNDER_TEMPERATURE] = FAULT;
				}

				if(database->min_temperature < UTC_MOL)
				{
					fmon_database_error.error_counter_MOL.utc_counter++;
					if(fmon_database_error.error_counter_MOL.utc_counter > (UTC_MOL_DELAY/TEMPERATURE_SAMPLING))
					{
						fmon_database_error.error_flag_MOL.charge_under_temperature = FAULT;
					}
				}
				else
				{
					fmon_database_error.error_counter_MOL.utc_counter = 0;
				}

				if(database->min_temperature < UTC_MSL)
				{
					fmon_database_error.error_flag_ROL.charge_under_temperature = FAULT;
					fmon_database_error.error_flag_MOL.charge_under_temperature = FAULT;
					fmon_database_error.error_flag_MSL.charge_under_temperature = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_ROL.utc_counter = 0;
				fmon_database_error.error_counter_MOL.utc_counter = 0;
			}

			DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);
		}

		if(database_bms->bms_state != BMS_CHARGE)
		{
			DATABASE_READ((void*)(&fmon_database_error), DATABASE_ERROR);

			/* Over Temperature Discharge */
			if(database->max_temperature > OTD_ROL)
			{
				fmon_database_error.error_counter_ROL.otd_counter++;
				if(fmon_database_error.error_counter_ROL.otd_counter > (OTD_ROL_DELAY/TEMPERATURE_SAMPLING))
				{
					fmon_database_error.error_flag_ROL.discharge_over_temperature = FAULT;
					WARNING_ARRAY[FAULT_DISCHARGE_OVER_TEMPERATURE] = FAULT;
				}

				if(database->max_temperature > OTD_MOL)
				{
					fmon_database_error.error_counter_MOL.otd_counter++;
					if(fmon_database_error.error_counter_MOL.otd_counter > (OTD_MOL_DELAY/TEMPERATURE_SAMPLING))
					{
						fmon_database_error.error_flag_MOL.discharge_over_temperature = FAULT;
					}
				}
				else
				{
					fmon_database_error.error_counter_MOL.otd_counter = 0;
				}

				if(database->max_temperature > OTD_MSL)
				{
					fmon_database_error.error_flag_ROL.discharge_over_temperature = FAULT;
					fmon_database_error.error_flag_MOL.discharge_over_temperature = FAULT;
					fmon_database_error.error_flag_MSL.discharge_over_temperature = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_ROL.otd_counter = 0;
				fmon_database_error.error_counter_MOL.otd_counter = 0;
			}

			/* Under Temperature Discharge */
			if(database->min_temperature < UTD_ROL)
			{
				fmon_database_error.error_counter_ROL.utd_counter++;
				if(fmon_database_error.error_counter_ROL.utd_counter > (UTD_ROL_DELAY/TEMPERATURE_SAMPLING))
				{
					fmon_database_error.error_flag_ROL.discharge_under_temperature = FAULT;
					WARNING_ARRAY[FAULT_DISCHARGE_UNDER_TEMPERATURE] = FAULT;
				}

				if(database->min_temperature < UTD_MOL)
				{
					fmon_database_error.error_counter_MOL.utd_counter++;
					if(fmon_database_error.error_counter_MOL.utd_counter > (UTD_MOL_DELAY/TEMPERATURE_SAMPLING))
					{
						fmon_database_error.error_flag_MOL.discharge_under_temperature = FAULT;
					}
				}
				else
				{
					fmon_database_error.error_counter_MOL.utd_counter = 0;
				}

				if(database->min_temperature < UTD_MSL)
				{
					fmon_database_error.error_flag_ROL.discharge_under_temperature = FAULT;
					fmon_database_error.error_flag_MOL.discharge_under_temperature = FAULT;
					fmon_database_error.error_flag_MSL.discharge_under_temperature = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_ROL.utd_counter = 0;
				fmon_database_error.error_counter_MOL.utd_counter = 0;
			}

			DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);
		}

		FAULTMANAGER_Temperature(database);
	}
}

void FAULT_CurrentMonitor(DATABASE_CURRENT_s *database, DATABASE_BMS_s *database_bms)
{
	if (database_bms->bms_state != BMS_DISCHARGE)
	{
		DATABASE_READ((void*)(&fmon_database_error), DATABASE_ERROR);

		if(database->pack_current > OCC_ROL)
		{
			fmon_database_error.error_counter_ROL.occ_counter++;
			if(fmon_database_error.error_counter_ROL.occ_counter > (OCC_ROL_DELAY/CURRENT_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.charge_over_current = FAULT;
				WARNING_ARRAY[FAULT_CHARGE_OVER_CURRENT] = FAULT;
			}

			if(database->pack_current > OCC_MOL)
			{
				fmon_database_error.error_counter_MOL.occ_counter++;
				if(fmon_database_error.error_counter_MOL.occ_counter > (OCC_MOL_DELAY/CURRENT_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.charge_over_current = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.occ_counter = 0;
			}

			if(database->pack_current > OCC_MSL)
			{
				fmon_database_error.error_flag_ROL.charge_over_current = FAULT;
				fmon_database_error.error_flag_MOL.charge_over_current = FAULT;
				fmon_database_error.error_flag_MSL.charge_over_current = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.occ_counter = 0;
			fmon_database_error.error_counter_MOL.occ_counter = 0;
		}

		DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);
	}

	if (database_bms->bms_state != BMS_CHARGE)
	{
		DATABASE_READ((void*)(&fmon_database_error), DATABASE_ERROR);

		if(database->pack_current < OCD_ROL)
		{
			fmon_database_error.error_counter_ROL.ocd_counter++;
			if(fmon_database_error.error_counter_ROL.ocd_counter > (OCD_ROL_DELAY/CURRENT_SAMPLING))
			{
				fmon_database_error.error_flag_ROL.discharge_over_current = FAULT;
				WARNING_ARRAY[FAULT_DISCHARGE_OVER_CURRENT] = FAULT;
			}

			if(database->pack_current < OCD_MOL)
			{
				fmon_database_error.error_counter_MOL.ocd_counter++;
				if(fmon_database_error.error_counter_MOL.ocd_counter > (OCD_MOL_DELAY/CURRENT_SAMPLING))
				{
					fmon_database_error.error_flag_MOL.discharge_over_current = FAULT;
				}
			}
			else
			{
				fmon_database_error.error_counter_MOL.ocd_counter = 0;
			}

			if(database->pack_current < OCD_MSL)
			{
				fmon_database_error.error_flag_ROL.discharge_over_current = FAULT;
				fmon_database_error.error_flag_MOL.discharge_over_current = FAULT;
				fmon_database_error.error_flag_MSL.discharge_over_current = FAULT;
			}
		}
		else
		{
			fmon_database_error.error_counter_ROL.ocd_counter = 0;
			fmon_database_error.error_counter_MOL.ocd_counter = 0;
		}

		DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);
	}

	FAULTMANAGER_Current(database);
}

void FAULT_SOCMonitor(DATABASE_SOC_s *database, DATABASE_BMS_s *database_bms)
{
	if(database_bms->bms_state != BMS_IDLE)
	{
		if(database_bms->bms_state != BMS_DISCHARGE)
		{
			DATABASE_READ((void*)(&fmon_database_error), DATABASE_ERROR);

			/* SOC_High */
			if(database->soc > SOCH_ROL)
			{
				fmon_database_error.error_counter_ROL.soch_counter++;
				if(fmon_database_error.error_counter_ROL.soch_counter > (SOCH_ROL_DELAY/SOC_SAMPLING))
				{
					fmon_database_error.error_flag_ROL.soc_high = FAULT;
					WARNING_ARRAY[FAULT_SOC_HIGH] = FAULT;
				}

				if(database->soc >= SOCH_MOL)
				{
					fmon_database_error.error_counter_MOL.soch_counter++;
					if(fmon_database_error.error_counter_MOL.soch_counter > (SOCH_MOL_DELAY/SOC_SAMPLING))
					{
						fmon_database_error.error_flag_MOL.soc_high = FAULT;
					}
				}
				else
				{
					fmon_database_error.error_counter_MOL.soch_counter = 0;
				}

			}
			else
			{
				fmon_database_error.error_counter_ROL.soch_counter = 0;
				fmon_database_error.error_counter_MOL.soch_counter = 0;
			}

			DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);
		}

		if(database_bms->bms_state != BMS_CHARGE)
		{
			/* SOC_High */
			if(database->soc < SOCL_ROL)
			{
				fmon_database_error.error_counter_ROL.socl_counter++;
				if(fmon_database_error.error_counter_ROL.socl_counter > (SOCL_ROL_DELAY/SOC_SAMPLING))
				{
					fmon_database_error.error_flag_ROL.soc_low = FAULT;
					WARNING_ARRAY[FAULT_SOC_LOW] = FAULT;
				}

				if(database->soc <= SOCL_MOL)
				{
					fmon_database_error.error_counter_MOL.socl_counter++;
					if(fmon_database_error.error_counter_MOL.socl_counter > (SOCL_MOL_DELAY/SOC_SAMPLING))
					{
						fmon_database_error.error_flag_MOL.soc_low = FAULT;
					}
				}
				else
				{
					fmon_database_error.error_counter_MOL.socl_counter = 0;
				}
			}
			else
			{
				fmon_database_error.error_counter_ROL.socl_counter = 0;
				fmon_database_error.error_counter_MOL.socl_counter = 0;
			}

			DATABASE_WRITE((void*)(&fmon_database_error), DATABASE_ERROR);
		}

		FAULTMANAGER_SOC(database);
	}
}
