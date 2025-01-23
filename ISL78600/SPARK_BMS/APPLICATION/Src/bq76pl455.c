/*
 * @filename	bq76pl455.c
 * @author		SPARKBMS TEAM
 * @date		21-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		bq76pl455
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "bq76pl455.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_VOLTAGE_s	bq_database_voltage = {0};
static DATABASE_BMS_s	bq_database_bms = {0};
static DATABASE_TEMPERATURE_s	bq_database_temperature = {0};
static DATABASE_EEPROM_s	bq_database_eeprom = {0};
static DATABASE_CURRENT_s	bq_current_database = {0};

uint8_t len = 20;
static int32_t currentArray[20];
static int32_t LcurrentArray[20];
static int32_t sum = 0;
static int32_t sum2 = 0;
uint64_t chg_ah = 0;
uint64_t dichg_ah = 0;

uint8_t short_circuit = 0;
bool SOC_INIT = 0;
uint8_t scnt = 0;

//static uint16_t Pre_Adc = 0;
/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

uint16_t BQ_AFE_ReadSerialNo(void)
{
	union{
		uint8_t AFE_Response[2];
		uint16_t value;
	}AFE_ReadData;

	AFE_ReadReg(BQ_ADDR, 198, AFE_ReadData.AFE_Response, 2, 10);

	return AFE_ReadData.value;
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void BQ_AFE_Init(void)
{
	DATABASE_READ((void*)(&bq_database_bms), DATABASE_BMS);

//	if(bq_database_bms.afe_state == AFE_SHUTDOWN && bq_database_bms.bms_state == BMS_IDLE)
	{
		GPIO_WritePin(GPIO_PIN_AFE_UART_EN,SET);

		AFE_Wakeup();

		bq_database_bms.afe_state = AFE_IDLE;
		DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);

		BQ_AFE_Config();
		BQ_AFE_OV_Config();
		BQ_AFE_UV_Config();
		BQ_AFE_ClearAllFault();

		bq_database_bms.afe_state = AFE_ACTIVE;
		DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);

//		if(BQ_AFE_CheckError() == NO_ERROR)
		{
//			CONT_StateRequest(CONT_NORMAL);

			DATABASE_READ((void*)(&bq_database_bms), DATABASE_BMS);
			bq_database_bms.bms_state = BMS_STANDBY;
			DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
		}
	}
//	else
//	{
//		Error_Handler();
//	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void BQ_AFE_ReadVoltage(void)
{
	uint8_t AFE_RESPONSE[(NO_OF_CELLS_PER_STACK*2) + 3];
	uint8_t read = 0;
	uint16_t Cell_ADC[NO_OF_CELLS_PER_STACK];
	uint16_t maxV,minV;
	uint16_t md_maxV,md_minV;
	uint8_t md_maxVIndex = 0;
	uint8_t md_minVIndex = 0;
	uint8_t maxVIndex = 0;
	uint8_t minVIndex = 0;
	uint32_t sum = 0;
	uint32_t mod_sum = 0;
	uint8_t cell_index = 0;

	DATABASE_READ((void*)(&bq_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&bq_database_eeprom), DATABASE_EEPROM);
	// For checking purpose condition is kept to bms_state == BMS_IDLE otherwise it should be
	// bms_state != BMS_IDLE
	if(bq_database_bms.bms_state != BMS_IDLE && bq_database_bms.balancing_status == BAL_OFF)
	{
		for(uint8_t Address = 0; Address < NO_OF_DAISY_STACK; Address++)
		{
			AFE_WriteReg(Address, 2, 0X00FFFF0000, 5, FRMWRT_SGL_R);
			read = AFE_WaitRespFrame(AFE_RESPONSE, 35, 0);

			if(read == 32)
			{
				if(Address%2 == 0)
				{
					uint8_t cnt = 1;

					for(uint8_t i=0; i<NO_OF_CELLS_PER_STACK; i++)
					{
						Cell_ADC[i] = (AFE_RESPONSE[cnt] << 8) | (AFE_RESPONSE[cnt+1] & 0XFF);
						bq_database_voltage.cell_voltage[cell_index] = ((Cell_ADC[i]*5*1000)/65535);
						bq_database_eeprom.cell_voltage[cell_index] = bq_database_voltage.cell_voltage[cell_index];
						sum = sum + bq_database_voltage.cell_voltage[cell_index];
						mod_sum = mod_sum + bq_database_voltage.cell_voltage[cell_index];
						cell_index++;
						cnt = cnt+2;
					}
					bq_database_voltage.module_voltage[Address] = mod_sum;
					mod_sum = 0;
				}

				else
				{
					uint8_t cnt = 3;

					for(uint8_t i=0; i<(NO_OF_CELLS_PER_STACK-1); i++)
					{
						Cell_ADC[i] = (AFE_RESPONSE[cnt] << 8) | (AFE_RESPONSE[cnt+1] & 0XFF);
						bq_database_voltage.cell_voltage[cell_index] = ((Cell_ADC[i]*5*1000)/65535);
						bq_database_eeprom.cell_voltage[cell_index] = bq_database_voltage.cell_voltage[cell_index];
						sum = sum + bq_database_voltage.cell_voltage[cell_index];
						mod_sum = mod_sum + bq_database_voltage.cell_voltage[cell_index];
						cell_index++;
						cnt = cnt+2;
					}
					bq_database_voltage.module_voltage[Address] = mod_sum;
					mod_sum = 0;
				}
			}
		}

		bq_database_voltage.avg_voltage = sum/BMS_NO_OF_CELLS;
		bq_database_voltage.sum_voltage = sum;
		bq_database_eeprom.pack_voltage = sum;

		sum = 0;

		HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);

		maxV = bq_database_voltage.cell_voltage[0];
		minV = bq_database_voltage.cell_voltage[0];

		for(uint8_t i=1; i<BMS_NO_OF_CELLS; i++)
		{
			if(maxV < bq_database_voltage.cell_voltage[i])
			{
				maxV = bq_database_voltage.cell_voltage[i];
				maxVIndex = i;
			}

			if(minV > bq_database_voltage.cell_voltage[i])
			{
				minV = bq_database_voltage.cell_voltage[i];
				minVIndex = i;
			}
		}

		bq_database_voltage.max_voltage = maxV;
		bq_database_eeprom.max_voltage = maxV;
		bq_database_voltage.max_voltage_index = maxVIndex;
		bq_database_eeprom.max_voltage_index = maxVIndex;

		bq_database_voltage.min_voltage = minV;
		bq_database_eeprom.min_voltage = minV;
		bq_database_voltage.min_voltage_index = minVIndex;
		bq_database_eeprom.min_voltage_index = minVIndex;

		bq_database_voltage.diff_voltage = maxV - minV;

		/* -------------------------------- */
		md_maxV = bq_database_voltage.module_voltage[0];
		md_minV = bq_database_voltage.module_voltage[0];

		for(uint8_t i=1; i<NO_OF_DAISY_STACK; i++)
		{
			if(md_maxV < bq_database_voltage.module_voltage[i])
			{
				md_maxV = bq_database_voltage.module_voltage[i];
				md_maxVIndex = i;
			}

			if(md_minV > bq_database_voltage.module_voltage[i])
			{
				md_minV = bq_database_voltage.module_voltage[i];
				md_minVIndex = i;
			}
		}
		bq_database_voltage.module_max_voltage = md_maxV;
		bq_database_voltage.module_max_voltage_index = md_maxVIndex;

		bq_database_voltage.module_min_voltage = md_minV;
		bq_database_voltage.module_min_voltage_index = md_minVIndex;

		bq_database_voltage.module_diff_voltage = md_maxV - md_minV;

		/**************CURRENT UPDATE TO EEPROM****************/
		bq_database_eeprom.current = bq_current_database.pack_current;
		/******************************************************/

		DATABASE_WRITE((void*)(&bq_database_voltage), DATABASE_VOLTAGE);
		DATABASE_WRITE((void*)(&bq_database_eeprom), DATABASE_EEPROM);
		DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);

		if(minV > 2500 && SOC_INIT == 0)
		{
			scnt++;
			if(scnt == 30)
			{
				SOC_Init();
				SOC_INIT = 1;
				scnt = 0;
			}
		}
		if(SOC_INIT == 1)
		{
			SOC_Update();
			SOC_INIT = 1;
		}
	}

//	FAULT_VoltageMonitor(&bq_database_voltage, &bq_database_bms);
//	TIMER_Delay_ms(2);
//	FAULT_CurrentMonitor(&bq_current_database, &bq_database_bms);

	GPIO_TogglePin(GPIO_PIN_LED);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void BQ_AFE_ReadTemperature(void)
{
	uint8_t AFE_RESPONSE[(NO_OF_TEMPS_PER_STACK*2) + 3];
	uint8_t read = 0;
	uint16_t Vout = 0;
	uint16_t R_NTC = 0;
	uint8_t temp_index = 0;
	uint16_t Temp_ADC[NO_OF_TEMPS_PER_STACK];
	int16_t maxT,minT;
	uint8_t maxTIndex = 0;
	uint8_t minTIndex = 0;
	uint32_t sum = 0;

	DATABASE_READ((void*)(&bq_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&bq_database_eeprom), DATABASE_EEPROM);

	//Change to bms_state != BMS_IDLE
	if(bq_database_bms.bms_state != BMS_IDLE)
	{

		for(uint8_t Address = 0; Address < NO_OF_DAISY_STACK; Address++)
		{
			AFE_WriteReg(Address, 2, 0X000000FF00, 5, FRMWRT_SGL_R);
			read = AFE_WaitRespFrame(AFE_RESPONSE, 19,0);

			if(read == 16)
			{
				uint8_t cnt = 3;
				for(uint8_t i=0; i<NO_OF_TEMPS_PER_STACK; i++)
				{
					Temp_ADC[i] = (AFE_RESPONSE[cnt] << 8) | (AFE_RESPONSE[cnt+1] & 0XFF);
					Vout = ((Temp_ADC[i]*5345)/65535);
					if(Vout != 5345)
						R_NTC = (Vout * 10000)/(5345 - Vout);
					bq_database_temperature.pack_temperature[temp_index] = ((298*3700)/(298*log((float)R_NTC/10000)+3700)) - 273;
					bq_database_eeprom.temperature[temp_index] = bq_database_temperature.pack_temperature[temp_index];
					sum = sum + bq_database_temperature.pack_temperature[temp_index];
					temp_index++;
					cnt = cnt+2;
				}
			}
		}

		bq_database_temperature.avg_temperature = sum/BMS_NO_OF_TEMPS;

		sum = 0;

		maxT = bq_database_temperature.pack_temperature[0];
		minT = bq_database_temperature.pack_temperature[0];

		for(uint8_t i=1; i<BMS_NO_OF_TEMPS; i++)
		{
			if(maxT < bq_database_temperature.pack_temperature[i])
			{
				maxT = bq_database_temperature.pack_temperature[i];
				maxTIndex = i;
			}

			if(minT > bq_database_temperature.pack_temperature[i])
			{
				minT = bq_database_temperature.pack_temperature[i];
				minTIndex = i;
			}
		}

		bq_database_temperature.max_temperature = maxT;
		bq_database_eeprom.max_temperature = maxT;
		bq_database_temperature.max_temperature_index = maxTIndex;
		bq_database_eeprom.max_temperature_index = maxTIndex;

		bq_database_temperature.min_temperature = minT;
		bq_database_eeprom.min_temperature = minT;
		bq_database_temperature.min_temperature_index = minTIndex;
		bq_database_eeprom.min_temperature_index = minTIndex;

		DATABASE_WRITE((void*)(&bq_database_temperature), DATABASE_TEMPERATURE);
		DATABASE_WRITE((void*)(&bq_database_eeprom), DATABASE_EEPROM);
		DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
	}

//	FAULT_TemperatureMonitor(&bq_database_temperature, &bq_database_bms);

//	GPIO_TogglePin(GPIO_PIN_LED2);
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

	Vout = (rawADC[0]*3315)/4095;
	lVout = (rawADC[1]*3315)/4095;
//	current = (Vout - 1610)*1000/20;

//	Vhall = ((Vout*3707)/2706) + 35 ;
//	current = ((Vhall - 2460)*1000/22);

	Vhall = ((Vout*3707)/2706) + 57;
	lVhall = ((lVout*3707)/2706) + 57;

	current = (Vhall - 2500)*1000/20;
	Lcurrent = ((lVhall - 2500)*1000/20);

	current = movingAvg(currentArray, &sum, len, current);

	Lcurrent = movingAvg(LcurrentArray, &sum2, len, Lcurrent);

	DATABASE_READ((void*)(&bq_current_database), DATABASE_CURRENT);

	if(Lcurrent > -100000 && Lcurrent < 100000)
	{
		bq_current_database.pack_current = Lcurrent;
	}
	else
	{
		bq_current_database.pack_current = current;
	}

	DATABASE_WRITE((void*)(&bq_current_database), DATABASE_CURRENT);

	if((current > SC_MSL || Lcurrent > SC_MSL) && short_circuit == 0 )
	{
		SHORTCIRCUIT_FaultManager(&current);
		short_circuit = 1;
	}

	if(short_circuit == 1)
	{
		SHORTCIRCUIT_ClearFault(&current);
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

uint8_t BQ_AFE_CheckError(void)
{
	uint16_t Fault_Summary;
	uint8_t cnt = 15;
	AFE_ReadReg(BQ_ADDR, 82, &Fault_Summary, 2, 10);

	if(Fault_Summary != 0)
	{
		for(uint8_t i=0; i<10; i++)
		{
			if((Fault_Summary >> cnt) == 1)
			{
				Fault_Summary = (Fault_Summary & ~(1<<cnt));

				switch(i)
				{
					case 0:
						bq_database_bms.afe_error = AFE_UV_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 1:
						bq_database_bms.afe_error = AFE_OV_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 2:
						bq_database_bms.afe_error = AFE_AUXUV_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 3:
						bq_database_bms.afe_error = AFE_AUXOV_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 4:
						bq_database_bms.afe_error = AFE_CMPUV_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 5:
						bq_database_bms.afe_error = AFE_CMPOV_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 6:
						bq_database_bms.afe_error = AFE_COMM_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 7:
						bq_database_bms.afe_error = AFE_SYS_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 8:
						bq_database_bms.afe_error = AFE_CHIP_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;

					case 9:
						bq_database_bms.afe_error = AFE_GPI_FAULT_SUM;
						DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
						break;
				}

			}

			cnt--;
		}
		TIMER_Delay_ms(3);
		return ERROR;
	}
	else
	{
		bq_database_bms.afe_error = AFE_NO_ERR;
		DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
		TIMER_Delay_ms(3);
		return NO_ERROR;
	}

}

void BQ_AFE_GETState(void)
{
	DATABASE_READ((void*)(&bq_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&bq_current_database), DATABASE_CURRENT);
	if(bq_database_bms.bms_state != BMS_ERROR)
	{
		if(bq_current_database.pack_current < -4000)
		{
			bq_database_bms.bms_state = BMS_DISCHARGE;
		}
		else if(bq_current_database.pack_current > 4000)
		{
			bq_database_bms.bms_state = BMS_CHARGE;
		}
		else
		{
			bq_database_bms.bms_state = BMS_STANDBY;
		}
	}

	DATABASE_WRITE((void*)(&bq_database_bms), DATABASE_BMS);
}


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
