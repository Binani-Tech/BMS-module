/*
 * @filename	soc.c
 * @author		SPARKBMS TEAM
 * @date		03-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		soc
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "soc.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_SOC_s	soc_database = {0};
static DATABASE_CURRENT_s	soc_database_current = {0};
static DATABASE_EEPROM_s	soc_database_eeprom = {0};
static DATABASE_BMS_s		soc_database_bms = {0};

//uint16_t DKWH = 0;
uint16_t CKWH = 0;
uint16_t Cyl_Cnt = 0;

static float calc_soc = 0;

static uint16_t ocvVSsoc[20][2] = {{3139,5},
								   {3220,10},
								   {3237,15},
								   {3265,20},
								   {3290,25},
								   {3302,30},
								   {3304,35},
								   {3304,40},
								   {3305,45},
								   {3306,50},
								   {3307,55},
                                   {3312,60},
								   {3338,65},
								   {3340,70},
								   {3342,75},
								   {3340,80},
								   {3341,85},
								   {3342,90},
								   {3345,95},
								   {3352,100}};


/*-------------------------------------------Function Prototypes---------------------------------------*/

uint8_t calcInitialSOC(uint16_t Voltage);

/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void SOC_Init(void)
{
	uint8_t SOC_INITIAL  = 0;
	DATABASE_VOLTAGE_s	soc_database_voltage = {0};
	DATABASE_EEPROM_s readEEPROM_database = {0};

	readEEPROM_database = EEPROM_ReadAll();

//	BQ_AFE_ReadVoltage();

	DATABASE_READ((void*)(&soc_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&soc_database_voltage), DATABASE_VOLTAGE);
	if(soc_database_bms.bms_state == BMS_STANDBY)
	{
		DATABASE_READ((void*)(&soc_database), DATABASE_SOC);
		DATABASE_READ((void*)(&soc_database_eeprom), DATABASE_EEPROM);

		SOC_INITIAL = calcInitialSOC(soc_database_voltage.avg_voltage);

		soc_database.soc = SOC_INITIAL;
		soc_database.max_soc = SOC_INITIAL;
		soc_database.min_soc = SOC_INITIAL;
		soc_database.cycle = 0;
		calc_soc = ((float)SOC_INITIAL/100);

		if(readEEPROM_database.soc != 0)
		{
			soc_database.soc = readEEPROM_database.soc;
			soc_database_eeprom.soc = soc_database.soc;
		}

		else
		{
			soc_database.soc = SOC_INITIAL;
			soc_database_eeprom.soc = soc_database.soc;
		}

		DATABASE_WRITE((void*)(&soc_database), DATABASE_SOC);
		DATABASE_WRITE((void*)(&soc_database_eeprom), DATABASE_EEPROM);
	}
}

void SOC_Update(void)
{
	DATABASE_READ((void*)(&soc_database_current), DATABASE_CURRENT);
	DATABASE_READ((void*)(&soc_database), DATABASE_SOC);
	DATABASE_READ((void*)(&soc_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&soc_database_eeprom), DATABASE_EEPROM);

	if(soc_database_bms.bms_state == BMS_CHARGE || soc_database_bms.bms_state == BMS_DISCHARGE)
	{
		soc_database_current.current_counter -= ((float)soc_database_current.pack_current*CURRENT_UPDATE_TIME)/(3600*1000); // mAh
		float deltaSOC = ((float)soc_database_current.pack_current*CURRENT_UPDATE_TIME)/(1000*1000);

		if(soc_database_bms.bms_state == BMS_CHARGE)
		{
			soc_database_current.cycle_counter += ((float)soc_database_current.pack_current*CURRENT_UPDATE_TIME)/(3600*1000); // mAh
		}
		else if(soc_database_bms.bms_state == BMS_DISCHARGE)
		{
			soc_database_current.cycle_counter -= ((float)soc_database_current.pack_current*CURRENT_UPDATE_TIME)/(3600*1000); // mAh
		}

		calc_soc += ((deltaSOC)/(BATTERY_CAPACITY*3600));
		soc_database.soc = (uint8_t)(calc_soc*100);
		soc_database_eeprom.soc = (uint8_t)(calc_soc*100);

		if(soc_database.soc > 100){soc_database.soc = soc_database_eeprom.soc = 100;calc_soc = 1;}
		if(soc_database.soc < 0){soc_database.soc = soc_database_eeprom.soc = 0;calc_soc = 0;}

		if(soc_database.max_soc < soc_database.soc) { soc_database.max_soc = soc_database.soc; }
		if(soc_database.min_soc > soc_database.soc) { soc_database.min_soc = soc_database.soc; }

		if(soc_database_current.cycle_counter >= (BATTERY_CAPACITY*2*1000))
		{
			soc_database.cycle++;
			soc_database_eeprom.cycle_count = soc_database.cycle;
			soc_database_current.cycle_counter = 0;
		}

		DATABASE_WRITE((void*)(&soc_database_current), DATABASE_CURRENT);
		DATABASE_WRITE((void*)(&soc_database_eeprom), DATABASE_EEPROM);
		DATABASE_WRITE((void*)(&soc_database), DATABASE_SOC);
	}
	else if(soc_database_bms.bms_state == BMS_ERROR)
	{
		if(soc_database_eeprom.error_id == BMS_CELL_OVER_VOLTAGE)
		{
			soc_database_current.current_counter = BATTERY_CAPACITY*1000;

			soc_database.soc = 100;
			soc_database_eeprom.soc = 100;
			calc_soc = 1;

			if(soc_database.max_soc < soc_database.soc) { soc_database.max_soc = soc_database.soc; }

			DATABASE_WRITE((void*)(&soc_database_current), DATABASE_CURRENT);
			DATABASE_WRITE((void*)(&soc_database_eeprom), DATABASE_EEPROM);
			DATABASE_WRITE((void*)(&soc_database), DATABASE_SOC);
		}
		else if(soc_database_eeprom.error_id == BMS_CELL_UNDER_VOLTAGE)
		{
			soc_database_current.current_counter = 0;

			soc_database.soc = 0;
			soc_database_eeprom.soc = 0;
			calc_soc = 0;

			if(soc_database.min_soc > soc_database.soc) { soc_database.min_soc = soc_database.soc; }

			DATABASE_WRITE((void*)(&soc_database_current), DATABASE_CURRENT);
			DATABASE_WRITE((void*)(&soc_database_eeprom), DATABASE_EEPROM);
			DATABASE_WRITE((void*)(&soc_database), DATABASE_SOC);
		}
	}

	FAULT_SOCMonitor(&soc_database, &soc_database_bms);
}

void SOH_Update(void)
{
	DATABASE_EEPROM_s readEEPROM_database = {0};

	readEEPROM_database = EEPROM_ReadAll();

	DATABASE_READ((void*)(&soc_database_current), DATABASE_CURRENT);
	DATABASE_READ((void*)(&soc_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&soc_database_eeprom), DATABASE_EEPROM);

	CKWH = readEEPROM_database.CKWH;

	Cyl_Cnt = (CKWH)/(BATTERY_KWH);

	uint8_t soh = 100 - (5/1000)*Cyl_Cnt;

	if(soh >= 70 && soh <= 100)
	{
		soc_database_eeprom.soh = soh ;
	}
	DATABASE_WRITE((void*)(&soc_database_eeprom), DATABASE_EEPROM);
}

uint8_t calcInitialSOC(uint16_t Voltage)
{
	uint8_t index = 0;
	uint8_t soc = 0;

	if(Voltage > ocvVSsoc[19][0])
	{
		return 100;
	}
	else if(Voltage < ocvVSsoc[0][0])
	{
		return 0;
	}

	for(uint8_t i=0; i<20; i++)
	{
		if(Voltage < ocvVSsoc[i][0])
		{
			index = i;
			break;
		}
	}

	soc = (uint8_t)(ocvVSsoc[index-1][1] + (((Voltage - ocvVSsoc[index-1][0])*(ocvVSsoc[index][1] - ocvVSsoc[index-1][1]))/(ocvVSsoc[index][0] - ocvVSsoc[index-1][0])));

	return soc;
}
