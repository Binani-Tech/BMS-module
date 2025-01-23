/*
 * @filename	isl78600.c
 * @author		SPARKBMS TEAM
 * @date		May 25, 2023
 * @ingroup		FOLDER NAME
 * @prefix		isl78600
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "isl78600.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_VOLTAGE_s	isl_database_voltage = {0};
static DATABASE_BMS_s	isl_database_bms = {0};
static DATABASE_TEMPERATURE_s	isl_database_temperature = {0};
static DATABASE_EEPROM_s	isl_database_eeprom = {0};
static DATABASE_CURRENT_s	isl_current_database = {0};

uint8_t len = 10;
static int32_t currentArray[10];
static int32_t LcurrentArray[10];
static int32_t sum = 0;
static int32_t Lsum = 0;

uint8_t short_circuit = 0;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void ISL_AFE_Init(void)
{
	DATABASE_READ((void*)(&isl_database_bms), DATABASE_BMS);

	if(isl_database_bms.afe_state == AFE_SHUTDOWN && isl_database_bms.bms_state == BMS_IDLE)
	{
//		AFE_WakeUp();
//		AFE_Identification();

		isl_database_bms.afe_state = AFE_IDLE;
		DATABASE_WRITE((void*)(&isl_database_bms), DATABASE_BMS);

//		ISL_AFE_Config();
//		ISL_AFE_OV_Config();
//		ISL_AFE_UV_Config();
//		ISL_AFE_ClearAllFault();

		isl_database_bms.afe_state = AFE_ACTIVE;
		DATABASE_WRITE((void*)(&isl_database_bms), DATABASE_BMS);

//		if(ISL_AFE_CheckError() == NO_ERROR)
		{
			CONT_StateRequest(CONT_NORMAL);

			DATABASE_READ((void*)(&isl_database_bms), DATABASE_BMS);
			isl_database_bms.bms_state = BMS_STANDBY;
			DATABASE_WRITE((void*)(&isl_database_bms), DATABASE_BMS);
		}
	}
	else
	{
		Error_Handler();
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */




/*
 * @brief
 * @arguments
 * @retvar
 */

void ISL_AFE_ReadVoltage(void)
{
//	uint16_t Cell_Voltage[BMS_NO_OF_CELLS] = {0};
//	uint32_t Pack_Voltage = 0;
	uint32_t sum = 0;
	uint16_t maxV,minV;
	uint8_t maxVIndex = 0;
	uint8_t minVIndex = 0;

	DATABASE_READ((void*)(&isl_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&isl_database_eeprom), DATABASE_EEPROM);
	DATABASE_READ((void*)(&isl_current_database), DATABASE_CURRENT);
	// For checking purpose condition is kept to bms_state == BMS_IDLE otherwise it should be
	// bms_state != BMS_IDLE
	if(isl_database_bms.bms_state != BMS_IDLE)
	{
//		AFE_ScanVoltages();
//		TIMER_Delay_ms(1);
//		AFE_ReadAllVoltages(Cell_Voltage);
//		AFE_ReadTotalPackVoltage(NO_OF_DAISY_STACK, &Pack_Voltage);

		DATABASE_READ((void*)(&isl_database_voltage), DATABASE_VOLTAGE);

		maxV = isl_database_voltage.S1_max_voltage;
		minV = isl_database_voltage.S1_min_voltage;

		if(maxV < isl_database_voltage.S2_max_voltage)
		{
			maxV = isl_database_voltage.S2_max_voltage;
		}

		if(minV > isl_database_voltage.S2_min_voltage)
		{
			minV = isl_database_voltage.S2_min_voltage;
		}

		for(uint8_t i = 0; i < BMS_NO_OF_CELLS; i++)
		{
//			if(Cell_Voltage[i] != 0)
//			{
			    isl_database_eeprom.cell_voltage[i] = isl_database_voltage.cell_voltage[i];
				sum = sum + isl_database_voltage.cell_voltage[i];

				if(i == 47)
				{
					isl_database_voltage.S1_voltage = sum;
				}

				else if(i == 95)
				{
					isl_database_voltage.S2_voltage = sum - isl_database_voltage.S1_voltage;
				}
//			}
		}

		isl_database_voltage.avg_voltage = (uint16_t)(sum/BMS_NO_OF_CELLS);

		isl_database_voltage.sum_voltage = sum;
		isl_database_eeprom.pack_voltage = sum;

		isl_database_voltage.max_voltage = maxV;
		isl_database_eeprom.max_voltage = maxV;
		isl_database_voltage.max_voltage_index = maxVIndex;
		isl_database_eeprom.max_voltage_index = maxVIndex;

		isl_database_voltage.min_voltage = minV;
		isl_database_eeprom.min_voltage = minV;
		isl_database_voltage.min_voltage_index = minVIndex;
		isl_database_eeprom.min_voltage_index = minVIndex;

		isl_database_voltage.diff_voltage = maxV - minV;

		/**************CURRENT UPDATE TO EEPROM****************/
		isl_database_eeprom.current = isl_current_database.pack_current;
		/******************************************************/

		isl_current_database.power = (sum*isl_current_database.pack_current)/(1000*1000);

		DATABASE_WRITE((void*)(&isl_database_voltage), DATABASE_VOLTAGE);
		DATABASE_WRITE((void*)(&isl_database_eeprom), DATABASE_EEPROM);
		DATABASE_WRITE((void*)(&isl_database_bms), DATABASE_BMS);
	}

	FAULT_VoltageMonitor(&isl_database_voltage, &isl_database_bms);
	TIMER_Delay_ms(1);
	FAULT_CurrentMonitor(&isl_current_database, &isl_database_bms);
	TIMER_Delay_ms(1);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void ISL_AFE_ReadTemperature(void)
{
//	int16_t AllTemperatures[BMS_NO_OF_TEMPS];
	int16_t maxT,minT;
	uint8_t maxTIndex = 0;
	uint8_t minTIndex = 0;
	int32_t sum = 0;
	int16_t Vout = 0;
	int16_t R_NTC = 0;

	DATABASE_READ((void*)(&isl_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&isl_database_eeprom), DATABASE_EEPROM);

	//Change to bms_state != BMS_IDLE
	if(isl_database_bms.bms_state != BMS_IDLE)
	{
		DATABASE_READ((void*)(&isl_database_temperature), DATABASE_TEMPERATURE);

		maxT = isl_database_temperature.pack_temperature[0];
		minT = isl_database_temperature.pack_temperature[0];

		for(uint8_t i=0; i<BMS_NO_OF_TEMPS; i++)
		{
			isl_database_eeprom.temperature[i] = isl_database_temperature.pack_temperature[i];
			sum = sum + isl_database_temperature.pack_temperature[i];

			if(maxT < isl_database_temperature.pack_temperature[i])
			{
				maxT = isl_database_temperature.pack_temperature[i];
				maxTIndex = i;
			}

			if(minT > isl_database_temperature.pack_temperature[i])
			{
				minT = isl_database_temperature.pack_temperature[i];
				minTIndex = i;
			}
		}

		isl_database_temperature.avg_temperature = sum/BMS_NO_OF_TEMPS;

		isl_database_temperature.max_temperature = maxT;
		isl_database_eeprom.max_temperature = maxT;
		isl_database_temperature.max_temperature_index = maxTIndex;
		isl_database_eeprom.max_temperature_index = maxTIndex;

		isl_database_temperature.min_temperature = minT;
		isl_database_eeprom.min_temperature = minT;
		isl_database_temperature.min_temperature_index = minTIndex;
		isl_database_eeprom.min_temperature_index = minTIndex;

		Vout = ((rawADC[11]*3327)/4095);
		R_NTC = (Vout * 10000)/(2500 - Vout);
		isl_database_temperature.pcb_temperature = ((298*3700)/(298*log((float)R_NTC/10000)+3700)) - 273;
		isl_database_eeprom.pcb_temperature = isl_database_temperature.pcb_temperature;

		DATABASE_WRITE((void*)(&isl_database_temperature), DATABASE_TEMPERATURE);
		DATABASE_WRITE((void*)(&isl_database_eeprom), DATABASE_EEPROM);
		DATABASE_WRITE((void*)(&isl_database_bms), DATABASE_BMS);

	}

	FAULT_TemperatureMonitor(&isl_database_temperature, &isl_database_bms);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void CURRENT_Read(uint16_t *rawADC)
{
	int32_t Vout , lVout;
	int32_t Vhall , lVhall;
	int32_t current = 0 , Lcurrent = 0;

	Vout = (rawADC[0]*3315)/4095;        // Vout = Hall High
	lVout = (rawADC[1]*3315)/4095;       // lVout = Hall Low
//	current = (Vout - 1610)*1000/20;

//	if(Vout < 1550)
//	Vhall = ((Vout*3707)/2706) + 97;
//	else
	Vhall = ((Vout*3707)/2706);

	lVhall = ((lVout*3707)/2706) + 81;

//	current = (Vhall - 2490)*100;
//	current = ((2500 - Vhall)*5*1000/20)-2850;

	current = ((Vhall - 2500)*1000/4);

	Lcurrent = ((lVhall - 2500)*10000/267);        //((lVhall - 2500)*1000/26.7);

	current = (-1)*((movingAvg(currentArray, &sum, len, current)));
//
	Lcurrent = (-1)*(movingAvg1(LcurrentArray, &Lsum, len, Lcurrent));

	DATABASE_READ((void*)(&isl_current_database), DATABASE_CURRENT);
	DATABASE_READ((void*)(&isl_database_eeprom), DATABASE_EEPROM);
	DATABASE_READ((void*)(&isl_database_bms), DATABASE_BMS);

	if(Lcurrent < 75000 && Lcurrent > (-75000))
	{
		isl_current_database.pack_current = Lcurrent;
		current = Lcurrent;
	}
	else
	{
		isl_current_database.pack_current = current;
	}

	DATABASE_WRITE((void*)(&isl_current_database), DATABASE_CURRENT);

	if(current > SC_MSL && short_circuit == 0 )
	{
		SHORTCIRCUIT_FaultManager(&current);
		short_circuit = 1;
	}

	if(short_circuit == 1)
	{
		SHORTCIRCUIT_ClearFault(&current);
	}

	if(isl_database_bms.bms_state == BMS_CHARGE)
	{
		CKWH += (isl_database_eeprom.pack_voltage*current*CURRENT_UPDATE_TIME)/(3600);
	}
}

//void ISO_VOLTAGE_Read(void)
//{
//	uint16_t isoVout[3] = {0};
//	for(uint8_t i=0; i < NO_OF_ISO_VOL; i++)
//	{
//		isoVout[i] = (rawADC[i+13]*3217)/4095;
//		isl_database_voltage.iso_pack_voltage[i] = isoVout[i];
//	}
//}

/*
 * @brief
 * @arguments
 * @retvar
 */

void ISL_AFE_GETState(void)
{
	DATABASE_READ((void*)(&isl_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&isl_database_voltage), DATABASE_VOLTAGE);
	DATABASE_READ((void*)(&isl_current_database), DATABASE_CURRENT);
	if(isl_database_bms.bms_state != BMS_ERROR)
	{
		if(isl_current_database.pack_current < -5000)
		{
			isl_database_bms.bms_state = BMS_DISCHARGE;
			isl_database_voltage.r_power = BATTERY_WH - isl_current_database.power;
			if(isl_database_voltage.r_power <= 0)
			{
				isl_database_voltage.r_power = 0;
			}
		}
		else if(isl_current_database.pack_current > 5000)
		{
			isl_database_bms.bms_state = BMS_CHARGE;
			isl_database_voltage.r_power = isl_current_database.power;
			if(isl_database_voltage.r_power >= BATTERY_WH)
			{
				isl_database_voltage.r_power = BATTERY_WH;
			}
		}
		else
		{
			isl_database_bms.bms_state = BMS_STANDBY;
		}
	}

	DATABASE_WRITE((void*)(&isl_database_bms), DATABASE_BMS);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

int32_t movingAvg(int32_t *ptrArrNumbers, int32_t *ptrSum, uint8_t len, int32_t nextNum)
{
	static uint8_t pos  = 0;
	//Subtract the oldest number from the prev sum, add the new number
	*ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
	//Assign the nextNum to the position in the array
	ptrArrNumbers[pos] = nextNum;
	//increment the position
	pos++;
	if(pos == len)
	{
		pos = 0;
	}
	//return the average
	return (*ptrSum/len);
}

int32_t movingAvg1(int32_t *ptrArrNumbers, int32_t *ptrSum, uint8_t len, int32_t nextNum)
{
	static uint8_t pos  = 0;
	//Subtract the oldest number from the prev sum, add the new number
	*ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
	//Assign the nextNum to the position in the array
	ptrArrNumbers[pos] = nextNum;
	//increment the position
	pos++;
	if(pos == len)
	{
		pos = 0;
	}
	//return the average
	return (*ptrSum/len);
}

void TEMP_ADC_Read(uint16_t *rawADC, int16_t *temperature)
{
	int16_t Vout = 0;
	int16_t R_NTC = 0;

	for(uint8_t i=0; i < NO_OF_ADC_TEMPS; i++)
	{
		Vout = (rawADC[i+2]*3323)/4095;
		R_NTC = (Vout * 10000)/(2500 - Vout);
		temperature[i] = ((298*3700)/(298*log((float)R_NTC/10000)+3700)) - 273;
	}
}
