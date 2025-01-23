/*
 * @filename	fault_cfg.c
 * @author		SPARKBMS TEAM
 * @date		11-Aug-2023
 * @ingroup		FOLDER NAME
 * @prefix		fault_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "fault_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/
static DATABASE_BMS_s	fault_database_bms = {0};
static DATABASE_TEMPERATURE_s	fault_database_temperature = {0};
static DATABASE_SOC_s	fault_database_soc = {0};

uint8_t NO_OF_CELLS = 124;

uint8_t NO_OF_TEMPS = 32;

uint16_t VOLTAGE_SAMPLING =	100;			// milli second
uint16_t CURRENT_SAMPLING = 100;			// milli second
uint16_t TEMPERATURE_SAMPLING = 1000;		// milli second
uint16_t SOC_SAMPLING = 100;				// milli second


/* Cell OverVoltage Configuration */

uint16_t COV_ROL = 3550;
uint16_t COV_MOL = 3600;
uint16_t COV_MSL = 3625;

uint16_t COV_ROL_DELAY = 3000;
uint16_t COV_MOL_DELAY = 3000;
uint16_t COV_MSL_DELAY = 0;

uint16_t COV_ROL_R = 3525;
uint16_t COV_MOL_R = 3590;
uint16_t COV_MSL_R = 3615;

uint16_t COV_ROL_R_DELAY = 5000;
uint16_t COV_MOL_R_DELAY = 5000;
uint16_t COV_MSL_R_DELAY = 5000;

/* Cell UnderVoltage Configuration */

uint16_t CUV_ROL = 2850;
uint16_t CUV_MOL = 2800;
uint16_t CUV_MSL = 2750;

uint16_t CUV_ROL_DELAY = 3000;
uint16_t CUV_MOL_DELAY = 3000;
uint16_t CUV_MSL_DELAY = 0;

uint16_t CUV_ROL_R = 2875;
uint16_t CUV_MOL_R = 2810;
uint16_t CUV_MSL_R = 2780;

uint16_t CUV_ROL_R_DELAY = 5000;
uint16_t CUV_MOL_R_DELAY = 5000;
uint16_t CUV_MSL_R_DELAY = 5000;

/* Pack OverVoltage Configuration */

uint32_t POV_ROL = 454400;
uint32_t POV_MOL = 460800;
uint32_t POV_MSL = 464000;

uint16_t POV_ROL_DELAY = 3000;
uint16_t POV_MOL_DELAY = 3000;
uint16_t POV_MSL_DELAY = 0;

uint32_t POV_ROL_R = 451200;
uint32_t POV_MOL_R = 459520;
uint32_t POV_MSL_R = 462720;

uint16_t POV_ROL_R_DELAY = 10000;
uint16_t POV_MOL_R_DELAY = 60000;
uint16_t POV_MSL_R_DELAY = 6000;

/* Pack UnderVoltage Configuration */

uint32_t PUV_ROL = 364800;
uint32_t PUV_MOL = 358400;
uint32_t PUV_MSL = 352000;

uint16_t PUV_ROL_DELAY = 3000;
uint16_t PUV_MOL_DELAY = 3000;
uint16_t PUV_MSL_DELAY = 0;

uint32_t PUV_ROL_R = 368000;
uint32_t PUV_MOL_R = 359680;
uint32_t PUV_MSL_R = 355840;

uint16_t PUV_ROL_R_DELAY = 10000;
uint16_t PUV_MOL_R_DELAY = 10000;
uint16_t PUV_MSL_R_DELAY = 2000;

/* Over Current Charge Configuration */

int32_t OCC_ROL = 105000;//-5500;
int32_t OCC_MOL = 110000;//-6000;
int32_t OCC_MSL = 120000;//-6500;

uint16_t OCC_ROL_DELAY = 60000;
uint16_t OCC_MOL_DELAY = 30000;
uint16_t OCC_MSL_DELAY = 5000;

int32_t OCC_ROL_R = 20000;//-5000;
int32_t OCC_MOL_R = 40000;//-5500;
int32_t OCC_MSL_R = 45000;//-6000;

uint16_t OCC_ROL_R_DELAY = 5000;
uint16_t OCC_MOL_R_DELAY = 5000;
uint16_t OCC_MSL_R_DELAY = 5000;

/* Over Current Discharge Configuration */

int32_t OCD_ROL = -105000;//5500;
int32_t OCD_MOL = -200000;//6000;
int32_t OCD_MSL = -205000;//6500;

uint16_t OCD_ROL_DELAY = 60000;
uint16_t OCD_MOL_DELAY = 30000;
uint16_t OCD_MSL_DELAY = 5000;

int32_t OCD_ROL_R = -50000;//5500;
int32_t OCD_MOL_R = -80000;//6000;
int32_t OCD_MSL_R = -100000;//6500;

uint16_t OCD_ROL_R_DELAY = 5000;
uint16_t OCD_MOL_R_DELAY = 5000;
uint16_t OCD_MSL_R_DELAY = 5000;

/* Over Temperature Charge Configuration */

int16_t OTC_ROL = 45;
int16_t OTC_MOL = 55;
int16_t OTC_MSL = 60;

uint16_t OTC_ROL_DELAY = 5000;
uint16_t OTC_MOL_DELAY = 5000;
uint16_t OTC_MSL_DELAY = 0;

int16_t OTC_ROL_R = 40;
int16_t OTC_MOL_R = 50;
int16_t OTC_MSL_R = 55;

uint16_t OTC_ROL_R_DELAY = 5000;
uint16_t OTC_MOL_R_DELAY = 5000;
uint16_t OTC_MSL_R_DELAY = 5000;


/* Under Temperature Charge Configuration */

int16_t UTC_ROL = 10;
int16_t UTC_MOL = 1;
int16_t UTC_MSL = 0;

uint16_t UTC_ROL_DELAY = 5000;
uint16_t UTC_MOL_DELAY = 5000;
uint16_t UTC_MSL_DELAY = 0;

int16_t UTC_ROL_R = 25;
int16_t UTC_MOL_R = 20;
int16_t UTC_MSL_R = 15;

uint16_t UTC_ROL_R_DELAY = 3000;
uint16_t UTC_MOL_R_DELAY = 3000;
uint16_t UTC_MSL_R_DELAY = 3000;


/* Over Temperature Discharge Configuration */

int16_t OTD_ROL = 45;
int16_t OTD_MOL = 55;
int16_t OTD_MSL = 60;

uint16_t OTD_ROL_DELAY = 5000;
uint16_t OTD_MOL_DELAY = 5000;
uint16_t OTD_MSL_DELAY = 0;

int16_t OTD_ROL_R = 40;
int16_t OTD_MOL_R = 50;
int16_t OTD_MSL_R = 55;

uint16_t OTD_ROL_R_DELAY = 5000;
uint16_t OTD_MOL_R_DELAY = 5000;
uint16_t OTD_MSL_R_DELAY = 5000;

/* Under Temperature Discharge Configuration */

int16_t UTD_ROL = 10;
int16_t UTD_MOL = 1;
int16_t UTD_MSL = 0;

uint16_t UTD_ROL_DELAY = 5000;
uint16_t UTD_MOL_DELAY = 5000;
uint16_t UTD_MSL_DELAY = 0;

int16_t UTD_ROL_R = 20;
int16_t UTD_MOL_R = 15;
int16_t UTD_MSL_R = 10;

uint16_t UTD_ROL_R_DELAY = 3000;
uint16_t UTD_MOL_R_DELAY = 5000;
uint16_t UTD_MSL_R_DELAY = 5000;

/* Passive Balancing Configuration */

uint16_t PB_BV = 4100;
uint16_t PB_BDIFFV = 50;
int16_t PB_BC = -1000;
uint16_t PB_BSV = 3800;

/* Voltage Difference Configuration */

uint16_t CVD_ROL = 150;//1000;
uint16_t CVD_MOL = 500;//1100;
uint16_t CVD_MSL = 550;//1200;

uint16_t CVD_ROL_DELAY = 5000;
uint16_t CVD_MOL_DELAY = 5000;
uint16_t CVD_MSL_DELAY = 0;

uint16_t CVD_ROL_R = 125;//1000;
uint16_t CVD_MOL_R = 480;//1100;
uint16_t CVD_MSL_R = 500;//1200;

uint16_t CVD_ROL_R_DELAY = 5000;
uint16_t CVD_MOL_R_DELAY = 5000;
uint16_t CVD_MSL_R_DELAY = 5000;

/* SOC High Configuration */


uint8_t SOCH_ROL = 90;
uint8_t SOCH_MOL = 100;

uint16_t SOCH_ROL_DELAY = 1000;
uint16_t SOCH_MOL_DELAY = 1000;

uint8_t SOCH_ROL_R = 90;
uint8_t SOCH_MOL_R = 95;

uint16_t SOCH_ROL_R_DELAY = 1000;
uint16_t SOCH_MOL_R_DELAY = 1000;


/* SOC Low Configuration */

uint8_t SOCL_ROL = 10;
uint8_t SOCL_MOL = 5;

uint16_t SOCL_ROL_DELAY = 1000;
uint16_t SOCL_MOL_DELAY = 1000;

uint8_t SOCL_ROL_R = 10;
uint8_t SOCL_MOL_R = 5;

uint16_t SOCL_ROL_R_DELAY = 1000;
uint16_t SOCL_MOL_R_DELAY = 1000;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/
void fault_CurrentConfig(void)
{
	DATABASE_READ((void*)(&fault_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&fault_database_soc), DATABASE_SOC);
	DATABASE_READ((void*)(&fault_database_temperature), DATABASE_TEMPERATURE);

	if(fault_database_bms.bms_state == BMS_DISCHARGE)
	{
		if((fault_database_temperature.min_temperature >= 25) && (fault_database_soc.soc >=20))
		{
			OCD_ROL = -105000;
			OCD_MOL = -200000;
			OCD_MSL = -205000;

			OCD_ROL_R = -50000;
			OCD_MOL_R = -80000;
			OCD_MSL_R = -100000;
		}
		else if(fault_database_temperature.min_temperature < 25)
		{
			if(fault_database_soc.soc >= 20)
			{
				 OCD_ROL = -50000;
				 OCD_MOL = -58800;
				 OCD_MSL = -60000;

				 OCD_ROL_R = -45000;
				 OCD_MOL_R = -50000;
				 OCD_MSL_R = -55000;
			}

			else if(fault_database_soc.soc > 10 && fault_database_soc.soc < 20)
			{
				 OCD_ROL = -45000;
				 OCD_MOL = -52500;
				 OCD_MSL = -55000;

				 OCD_ROL_R = -40000;
				 OCD_MOL_R = -45000;
				 OCD_MSL_R = -50000;
			}

			else
			{
				 OCD_ROL = -20000;
				 OCD_MOL = -26250;
				 OCD_MSL = -30000;

				 OCD_ROL_R = -15000;
				 OCD_MOL_R = -20000;
				 OCD_MSL_R = -25000;
			}

		}
		else if(fault_database_soc.soc < 20)
		{
			if(fault_database_soc.soc > 10)
			{
				 OCD_ROL = -70000;
				 OCD_MOL = -78750;
				 OCD_MSL = -80000;

				 OCD_ROL_R = -65000;
				 OCD_MOL_R = -70000;
				 OCD_MSL_R = -75000;
			}
			else
			{
				 OCD_ROL = -35000;
				 OCD_MOL = -39900;
				 OCD_MSL = -45000;

				 OCD_ROL_R = -30000;
				 OCD_MOL_R = -35000;
				 OCD_MSL_R = -40000;
			}

		}
	}
	else if(fault_database_bms.bms_state == BMS_CHARGE)
	{
		if((fault_database_temperature.min_temperature >= 25) && (fault_database_soc.soc <=90))
		{
			 OCC_ROL = 100000;
			 OCC_MOL = 105000;
			 OCC_MSL = 120000;

			 OCC_ROL_R = 20000;
			 OCC_MOL_R = 40000;
			 OCC_MSL_R = 45000;
		}
		else if(fault_database_temperature.min_temperature < 25)
		{
			if(fault_database_soc.soc <= 95)
			{
				 OCC_ROL = 25000;
				 OCC_MOL = 55000;
				 OCC_MSL = 60000;

				 OCC_ROL_R = 10000;
				 OCC_MOL_R = 15000;
				 OCC_MSL_R = 20000;
			}
			else
			{
				 OCC_ROL = 10000;
				 OCC_MOL = 12600;
				 OCC_MSL = 15000;

				 OCC_ROL_R = 80000;
				 OCC_MOL_R = 10000;
				 OCC_MSL_R = 12000;
			}
		}
		if((fault_database_temperature.min_temperature >= 25) && (fault_database_soc.soc >= 90))
		{
			 OCC_ROL = 25000;
			 OCC_MOL = 55000;
			 OCC_MSL = 60000;

			 OCC_ROL_R = 30000;
			 OCC_MOL_R = 38000;
			 OCC_MSL_R = 40000;
		}
	}
}
/*
 * @brief
 * @arguments
 * @retvar
 */
