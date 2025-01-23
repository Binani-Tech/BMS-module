/*
 * @filename	ble.c
 * @author		SPARKBMS TEAM
 * @date		31-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		ble
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "ble.h"
#include <stdio.h>
#include "eeprom.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/
uint8_t TxData[8];
uint8_t SOC = 100;

char buffer[1000];
static char bmsSerialNo[] = "SIBMS16S50A0001";

char Data[UART_BUFFER_SIZE];
char finalData[UART_BUFFER_SIZE];

BLEDATA_s bleData = {0};

ring_buffer rx_buffer = { { 0 }, 0, 0};
ring_buffer tx_buffer = { { 0 }, 0, 0};

ring_buffer *_rx_buffer;
ring_buffer *_tx_buffer;

static int cnt = 0;

/*-------------------------------------------Function Prototypes---------------------------------------*/

void Ringbuf_init(void);
void store_char(unsigned char c, ring_buffer *buffer);
int IsDataAvailable(void);
void Uart_read(char data[]);

/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void BLE_Init(void)
{
	char com1[] = "AT\r\n";
	char resp1[10];
	char resp1check[] = "AT\r\r\nOK\r\n";

	UART_BLE_Send((uint8_t*)com1, strlen(com1) , 20);
	UART_BLE_Receive((uint8_t*)resp1, sizeof(resp1), 20);

	if (strstr(resp1, resp1check) != NULL) {
//		GPIO_WritePin(GPIO_PIN_LED3, 1);
	}
	else {
//		GPIO_WritePin(GPIO_PIN_LED3, 0);
		UART_BLE_Send((uint8_t*)com1, strlen(com1) , 20);
		UART_BLE_Receive((uint8_t*)resp1, sizeof(resp1), 20);
	}

	//create service and characteristic
	char com3off[] = "AT+NWBTBLEPWR=0\r\n";
	char resp3off[22];
	UART_BLE_Send((uint8_t*)com3off, strlen(com3off) , 20);
	UART_BLE_Receive((uint8_t*)resp3off, sizeof(resp3off), 20);

	char servicecom[] = "AT+NWBLEPSRV=0,\"0x1808\",2,1\r\n";
	char respsercom[100];
	UART_BLE_Send((uint8_t*)servicecom, strlen(servicecom) , 20);
	UART_BLE_Receive((uint8_t*)respsercom, sizeof(respsercom), 20);

	char charcom[] = "AT+NWBLEPCRT=0,1,\"0x9999\",0,2,4\r\n";
	char respcharcom[100];
	UART_BLE_Send((uint8_t*)charcom, strlen(charcom) , 20);
	UART_BLE_Receive((uint8_t*)respcharcom, sizeof(respcharcom), 20);

	char serencom[] = "AT+NWBLEPSTR=0,1\r\n";
	char serenresp[100];
	UART_BLE_Send((uint8_t*)serencom, strlen(serencom) , 20);
	UART_BLE_Receive((uint8_t*)serenresp, sizeof(serenresp), 20);

	// TURN ON BLUETOOTH
	char com3[] = "AT+NWBTBLEPWR=1\r\n";
	char resp3[22];
	UART_BLE_Send((uint8_t*)com3, strlen(com3) , 20);
	UART_BLE_Receive((uint8_t*)resp3, sizeof(resp3), 20);
}

/*
 * @brief
 * @arguments
 * @retvar
 */
void UART_Send_Current(int32_t current,int32_t lcurrent)
{
	char com_dummy[20];
	char com_buffer[40];

	sprintf(com_dummy,"%ld",current);
	strcat(com_buffer,com_dummy);

	sprintf(com_dummy,"%ld",lcurrent);
	strcat(com_buffer,com_dummy);

	sprintf(com_dummy,"\n\r");
	strcat(com_buffer,com_dummy);

	UART_BLE_Send((uint8_t*)com_buffer, strlen(com_buffer) , 50);
}

void UART_Send_Index(void)
{
	char com_dummy[20];

	clear_buffer();

	for(uint8_t i = 1 ; i<97 ; i++)
	{
		sprintf(com_dummy,"CV_%d,",i);
		strcat(buffer,com_dummy);
		if(i%24 == 0)
		{
			UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 255);
			clear_buffer();
		}
	}
	for(uint8_t i = 1 ; i<9 ; i++)
	{
		sprintf(com_dummy,"T_%d,",i);
		strcat(buffer,com_dummy);
	}
	sprintf(com_dummy,"MinV,MaxV,");
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"PackVolatge,");
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"PackCurrentm,SOC,");
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"Cont_Status\n\r");
	strcat(buffer,com_dummy);

	UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 50);
}

void UART_Send_ALLData(void)
{
	TIMER7_Start();
	uart_flag = 1;

	DATABASE_SOC_s	uart_soc_database;
	DATABASE_VOLTAGE_s	uart_database_voltage;
	DATABASE_CURRENT_s	uart_database_current;
	DATABASE_CONTACTOR_s  uart_database_contactor;
	DATABASE_TEMPERATURE_s	uart_database_temperature;

	DATABASE_READ((void*)(&uart_soc_database), DATABASE_SOC);
	DATABASE_READ((void*)(&uart_database_voltage), DATABASE_VOLTAGE);
	DATABASE_READ((void*)(&uart_database_current), DATABASE_CURRENT);
	DATABASE_READ((void*)(&uart_database_contactor), DATABASE_CONTACTOR);
	DATABASE_READ((void*)(&uart_database_temperature), DATABASE_TEMPERATURE);

	char com_dummy[20];

	clear_buffer();

	for(uint8_t i = 0 ; i<BMS_NO_OF_CELLS ; i++)
	{
		sprintf(com_dummy,"%d,",uart_database_voltage.cell_voltage[i]);
		strcat(buffer,com_dummy);
		if(i%24 == 0)
		{
			UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 255);
			clear_buffer();
		}
	}

	for(uint8_t i = 0 ; i<256-BMS_NO_OF_CELLS ; i++)
	{
		sprintf(com_dummy,"0,");
		strcat(buffer,com_dummy);
		if(i%24 == 0)
		{
			UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 255);
			clear_buffer();
		}
	}
	for(uint8_t i = 0 ; i<BMS_NO_OF_TEMPS ; i++)
	{
		sprintf(com_dummy,"%d,",uart_database_temperature.pack_temperature[i]);
		strcat(buffer,com_dummy);
		if(i%20 == 0)
		{
			UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 255);
			clear_buffer();
		}
	}

	for(uint8_t i = 0 ; i<128-BMS_NO_OF_TEMPS ; i++)
	{
		sprintf(com_dummy,"0,");
		strcat(buffer,com_dummy);
		if(i%20 == 0)
		{
			UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 255);
			clear_buffer();
		}
	}

	UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 50);
	clear_buffer();

	sprintf(com_dummy,"%ld,",uart_database_voltage.sum_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%ld,",uart_database_current.pack_current);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",uart_database_voltage.max_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",uart_database_voltage.min_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",uart_database_temperature.max_temperature);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",uart_database_temperature.min_temperature);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",uart_database_temperature.max_temperature);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",uart_soc_database.soc);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"\n\r");
	strcat(buffer,com_dummy);

	UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 50);
	uart_flag = 0;
	uart_rst = 0;
	TIMER7_Stop();

}

void BLESparkViewInit(void)
{
	Ringbuf_init();
}

void BLECheckSparkViewRequest(void)
{
	if(!IsDataAvailable()==0)
	{
		Uart_read(Data);

	}
	else
	{
		memcpy(finalData,Data,cnt);
		postProcessingData(finalData);
		memset(Data, '\0', sizeof(Data));
		cnt = 0;
	}
}

void sendSparkViewHome(void)
{
	DATABASE_EEPROM_s	ble_database_eeprom = {0};
	DATABASE_READ((void*)&ble_database_eeprom, DATABASE_EEPROM);

	//	char com4[30];
	char com_dummy[20];
	uint16_t fault_code = 0;

	clear_buffer();

	sprintf(com_dummy,"%s,",bmsSerialNo);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.soc);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%ld,",ble_database_eeprom.pack_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%ld,",ble_database_eeprom.current);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.charge_mos);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.discharge_mos);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"0,");
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.max_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",(ble_database_eeprom.max_voltage_index + 1));
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.min_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",(ble_database_eeprom.min_voltage_index + 1));
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.max_temperature);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",(ble_database_eeprom.max_temperature_index + 1));
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",ble_database_eeprom.min_temperature);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%d,",(ble_database_eeprom.min_temperature_index + 1));
	strcat(buffer,com_dummy);

	for(uint8_t i=0;i<16;i++)
	{
		fault_code |= (FAULT_ARRAY[i] << i);
	}

	sprintf(com_dummy,"%d,",fault_code);
	strcat(buffer,com_dummy);


	//	sprintf(com4,"AT+NWBLEPSEND=0,0,0,1,%d\r\n", sizeof(buffer));
	//
	//	UART_BLE_Send((uint8_t*)com4, strlen(com4) , 100);
	UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 50);
}

void sendSparkViewLive(void)
{
	DATABASE_EEPROM_s	ble_database_eeprom = {0};
	DATABASE_READ((void*)&ble_database_eeprom, DATABASE_EEPROM);

	//	char com4[30];
	char com_dummy[20];

	clear_buffer();

	for(uint8_t i=0; i<16; i++)
	{
		if(i < NO_OF_CELLS)
		{
			sprintf(com_dummy,"%d,",ble_database_eeprom.cell_voltage[i]);
			strcat(buffer,com_dummy);
		}
		else
		{
			sprintf(com_dummy,"-,");
			strcat(buffer,com_dummy);
		}
	}

	for(uint8_t i=0; i<8; i++)
	{
		if(i < NO_OF_TEMPS)
		{
			sprintf(com_dummy,"%d,",ble_database_eeprom.temperature[i]);
			strcat(buffer,com_dummy);
		}
		else
		{
			sprintf(com_dummy,"-,");
			strcat(buffer,com_dummy);
		}
	}

	sprintf(com_dummy,"%d,",ble_database_eeprom.pcb_temperature);			// PCB Temperature Dummy
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%ld,",ble_database_eeprom.pack_voltage);
	strcat(buffer,com_dummy);

	sprintf(com_dummy,"%ld,",ble_database_eeprom.current);
	strcat(buffer,com_dummy);

//	sprintf(com4,"AT+NWBLEPSEND=0,0,0,1,%d\r\n", sizeof(buffer));
//
//	UART_BLE_Send((uint8_t*)com4, strlen(com4) , 100);
	UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 50);
}

void sendSparkViewDatabase(void)
{
	DATABASE_EEPROM_s readEEPROM_database = {0};

	//	char com4[30];
	char com_dummy[20];

	clear_buffer();

	readEEPROM_database = EEPROM_ReadAll();
	if(EEPROM_ReadFlag != 0)
	{
		sprintf(com_dummy,"%d-%d-%d %d:%d:%d,",readEEPROM_database.timestamp.day,readEEPROM_database.timestamp.month,readEEPROM_database.timestamp.year,
				readEEPROM_database.timestamp.hour,readEEPROM_database.timestamp.minute,readEEPROM_database.timestamp.second);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.error_id);
		strcat(buffer,com_dummy);

		for(uint8_t i=0; i<16; i++)
		{
			sprintf(com_dummy,"%d,",readEEPROM_database.cell_voltage[i]);
			strcat(buffer,com_dummy);
		}

		for(uint8_t i=0; i<8; i++)
		{
			sprintf(com_dummy,"%d,",readEEPROM_database.temperature[i]);
			strcat(buffer,com_dummy);
		}

		sprintf(com_dummy,"%ld,",readEEPROM_database.current);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%ld,",readEEPROM_database.pack_voltage);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.soc);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.soh);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.cycle_count);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.max_voltage);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.max_voltage_index);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.min_voltage);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.min_voltage_index);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.max_temperature);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.max_temperature_index);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.min_temperature);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.min_temperature_index);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.charge_mos);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"%d,",readEEPROM_database.discharge_mos);
		strcat(buffer,com_dummy);

		sprintf(com_dummy,"0,");
		strcat(buffer,com_dummy);

	//	sprintf(com4,"AT+NWBLEPSEND=0,0,0,1,%d\r\n", sizeof(buffer));
	//
	//	UART_BLE_Send((uint8_t*)com4, strlen(com4) , 100);
		UART_BLE_Send((uint8_t*)buffer, strlen(buffer) , 50);
	}

}

void sendSparkViewGeneralConfig(void)
{
	clear_buffer();

	sprintf(buffer,"%d,%d,%d,%d,%d,%d",NO_OF_CELLS,NO_OF_TEMPS,PB_BV,PB_BDIFFV,PB_BC,PB_BSV);
	UART_BLE_Send((uint8_t*)buffer, strlen(buffer), 50);
}

void sendSparkViewMSLConfig(void)
{
	clear_buffer();

	sprintf(buffer,"%d,%d,%d,%d,%d,%d,%d,%d,%ld,%d,%ld,%d,%ld,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			COV_MSL,COV_MSL_DELAY,COV_MSL_R,COV_MSL_R_DELAY,CUV_MSL,CUV_MSL_DELAY,CUV_MSL_R,CUV_MSL_R_DELAY,
			OCC_MSL,OCC_MSL_DELAY,OCC_MSL_R,OCC_MSL_R_DELAY,OCD_MSL,OCD_MSL_DELAY,OCD_MSL_R,OCD_MSL_R_DELAY,
			OTC_MSL,OTC_MSL_DELAY,OTC_MSL_R,OTC_MSL_R_DELAY,UTC_MSL,UTC_MSL_DELAY,UTC_MSL_R,UTC_MSL_R_DELAY,
			OTD_MSL,OTD_MSL_DELAY,OTD_MSL_R,OTD_MSL_R_DELAY,UTD_MSL,UTD_MSL_DELAY,UTD_MSL_R,UTD_MSL_R_DELAY,
			CVD_MSL,CVD_MSL_DELAY,CVD_MSL_R,CVD_MSL_R_DELAY);

	UART_BLE_Send((uint8_t*)buffer, strlen(buffer), 50);
}

void sendSparkViewMOLConfig(void)
{
	clear_buffer();

	sprintf(buffer,"%d,%d,%d,%d,%d,%d,%d,%d,%ld,%d,%ld,%d,%ld,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			COV_MOL,COV_MOL_DELAY,COV_MOL_R,COV_MOL_R_DELAY,CUV_MOL,CUV_MOL_DELAY,CUV_MOL_R,CUV_MOL_R_DELAY,
			OCC_MOL,OCC_MOL_DELAY,OCC_MOL_R,OCC_MOL_R_DELAY,OCD_MOL,OCD_MOL_DELAY,OCD_MOL_R,OCD_MOL_R_DELAY,
			OTC_MOL,OTC_MOL_DELAY,OTC_MOL_R,OTC_MOL_R_DELAY,UTC_MOL,UTC_MOL_DELAY,UTC_MOL_R,UTC_MOL_R_DELAY,
			OTD_MOL,OTD_MOL_DELAY,OTD_MOL_R,OTD_MOL_R_DELAY,UTD_MOL,UTD_MOL_DELAY,UTD_MOL_R,UTD_MOL_R_DELAY,
			CVD_MOL,CVD_MOL_DELAY,CVD_MOL_R,CVD_MOL_R_DELAY,
			SOCH_MOL,SOCH_MOL_DELAY,SOCH_MOL_R,SOCH_MOL_R_DELAY,SOCL_MOL,SOCL_MOL_DELAY,SOCL_MOL_R,SOCL_MOL_R_DELAY);

	UART_BLE_Send((uint8_t*)buffer, strlen(buffer), 50);
}

void sendSparkViewROLConfig(void)
{
	clear_buffer();

	sprintf(buffer,"%d,%d,%d,%d,%d,%d,%d,%d,%ld,%d,%ld,%d,%ld,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				COV_ROL,COV_ROL_DELAY,COV_ROL_R,COV_ROL_R_DELAY,CUV_ROL,CUV_ROL_DELAY,CUV_ROL_R,CUV_ROL_R_DELAY,
				OCC_ROL,OCC_ROL_DELAY,OCC_ROL_R,OCC_ROL_R_DELAY,OCD_ROL,OCD_ROL_DELAY,OCD_ROL_R,OCD_ROL_R_DELAY,
				OTC_ROL,OTC_ROL_DELAY,OTC_ROL_R,OTC_ROL_R_DELAY,UTC_ROL,UTC_ROL_DELAY,UTC_ROL_R,UTC_ROL_R_DELAY,
				OTD_ROL,OTD_ROL_DELAY,OTD_ROL_R,OTD_ROL_R_DELAY,UTD_ROL,UTD_ROL_DELAY,UTD_ROL_R,UTD_ROL_R_DELAY,
				CVD_ROL,CVD_ROL_DELAY,CVD_ROL_R,CVD_ROL_R_DELAY,
				SOCH_ROL,SOCH_ROL_DELAY,SOCH_ROL_R,SOCH_ROL_R_DELAY,SOCL_ROL,SOCL_ROL_DELAY,SOCL_ROL_R,SOCL_ROL_R_DELAY);

	UART_BLE_Send((uint8_t*)buffer, strlen(buffer), 50);
}

void updateSparkViewGeneralConfig(void)
{
	switch(bleData.parameterID)
	{
	case NO_OF_CELL:
		NO_OF_CELLS = (uint8_t)bleData.data;
		break;

	case NO_OF_TEMP:
		NO_OF_TEMPS = (uint8_t)bleData.data;
		break;

	case BAL_VOLTAGE:
		PB_BV = (uint16_t)bleData.data;
		break;

	case BAL_DIFFVOLT:
		PB_BDIFFV = (uint16_t)bleData.data;
		break;

	case BAL_CURRENT:
		PB_BC = (int16_t)bleData.data;
		break;

	case BAL_STOPVOLT:
		PB_BSV = (uint16_t)bleData.data;
		break;
	}

	sendSparkViewGeneralConfig();
}

void updateSparkViewMSLConfig(void)
{
	switch(bleData.parameterID)
	{
	case COV:
		COV_MSL = (uint16_t)bleData.data;
		break;

	case COV_Delay:
		COV_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case COVR:
		COV_MSL_R = (uint16_t)bleData.data;
		break;

	case COVR_Delay:
		COV_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case CUV:
		CUV_MSL = (uint16_t)bleData.data;
		break;

	case CUV_Delay:
		CUV_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case CUVR:
		CUV_MSL_R = (uint16_t)bleData.data;
		break;

	case CUVR_Delay:
		CUV_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OCC:
		OCC_MSL = (int32_t)bleData.data;
		break;

	case OCC_Delay:
		OCC_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case OCCR:
		OCC_MSL_R = (int32_t)bleData.data;
		break;

	case OCCR_Delay:
		OCC_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OCD:
		OCD_MSL = (int32_t)bleData.data;
		break;

	case OCD_Delay:
		OCD_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case OCDR:
		OCD_MSL_R = (int32_t)bleData.data;
		break;

	case OCDR_Delay:
		OCD_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OTC:
		OTC_MSL = (int16_t)bleData.data;
		break;

	case OTC_Delay:
		OTC_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case OTCR:
		OTC_MSL_R = (int16_t)bleData.data;
		break;

	case OTCR_Delay:
		OTC_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case UTC:
		UTC_MSL = (int16_t)bleData.data;
		break;

	case UTC_Delay:
		UTC_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case UTCR:
		UTC_MSL_R = (int16_t)bleData.data;
		break;

	case UTCR_Delay:
		UTC_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OTD:
		OTD_MSL = (int16_t)bleData.data;
		break;

	case OTD_Delay:
		OTD_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case OTDR:
		OTD_MSL_R = (int16_t)bleData.data;
		break;

	case OTDR_Delay:
		OTD_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case UTD:
		UTD_MSL = (int16_t)bleData.data;
		break;

	case UTD_Delay:
		UTD_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case UTDR:
		UTD_MSL_R = (int16_t)bleData.data;
		break;

	case UTDR_Delay:
		UTD_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	case CVD:
		CVD_MSL = (uint16_t)bleData.data;
		break;

	case CVD_Delay:
		CVD_MSL_DELAY = (uint16_t)bleData.data;
		break;

	case CVDR:
		CVD_MSL_R = (uint16_t)bleData.data;
		break;

	case CVDR_Delay:
		CVD_MSL_R_DELAY = (uint16_t)bleData.data;
		break;

	}

	sendSparkViewMSLConfig();
}

void updateSparkViewMOLConfig(void)
{
	switch(bleData.parameterID)
	{
	case COV:
		COV_MOL = (uint16_t)bleData.data;
		break;

	case COV_Delay:
		COV_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case COVR:
		COV_MOL_R = (uint16_t)bleData.data;
		break;

	case COVR_Delay:
		COV_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case CUV:
		CUV_MOL = (uint16_t)bleData.data;
		break;

	case CUV_Delay:
		CUV_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case CUVR:
		CUV_MOL_R = (uint16_t)bleData.data;
		break;

	case CUVR_Delay:
		CUV_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OCC:
		OCC_MOL = (int32_t)bleData.data;
		break;

	case OCC_Delay:
		OCC_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case OCCR:
		OCC_MOL_R = (int32_t)bleData.data;
		break;

	case OCCR_Delay:
		OCC_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OCD:
		OCD_MOL = (int32_t)bleData.data;
		break;

	case OCD_Delay:
		OCD_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case OCDR:
		OCD_MOL_R = (int32_t)bleData.data;
		break;

	case OCDR_Delay:
		OCD_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OTC:
		OTC_MOL = (int16_t)bleData.data;
		break;

	case OTC_Delay:
		OTC_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case OTCR:
		OTC_MOL_R = (int16_t)bleData.data;
		break;

	case OTCR_Delay:
		OTC_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case UTC:
		UTC_MOL = (int16_t)bleData.data;
		break;

	case UTC_Delay:
		UTC_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case UTCR:
		UTC_MOL_R = (int16_t)bleData.data;
		break;

	case UTCR_Delay:
		UTC_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OTD:
		OTD_MOL = (int16_t)bleData.data;
		break;

	case OTD_Delay:
		OTD_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case OTDR:
		OTD_MOL_R = (int16_t)bleData.data;
		break;

	case OTDR_Delay:
		OTD_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case UTD:
		UTD_MOL = (int16_t)bleData.data;
		break;

	case UTD_Delay:
		UTD_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case UTDR:
		UTD_MOL_R = (int16_t)bleData.data;
		break;

	case UTDR_Delay:
		UTD_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case CVD:
		CVD_MOL = (uint16_t)bleData.data;
		break;

	case CVD_Delay:
		CVD_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case CVDR:
		CVD_MOL_R = (uint16_t)bleData.data;
		break;

	case CVDR_Delay:
		CVD_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case SOCH:
		SOCH_MOL = (uint8_t)bleData.data;
		break;

	case SOCH_Delay:
		SOCH_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case SOCHR:
		SOCH_MOL_R = (uint8_t)bleData.data;
		break;

	case SOCHR_Delay:
		SOCH_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	case SOCL:
		SOCL_MOL = (uint8_t)bleData.data;
		break;

	case SOCL_Delay:
		SOCL_MOL_DELAY = (uint16_t)bleData.data;
		break;

	case SOCLR:
		SOCL_MOL_R = (uint8_t)bleData.data;
		break;

	case SOCLR_Delay:
		SOCL_MOL_R_DELAY = (uint16_t)bleData.data;
		break;

	}

	sendSparkViewMOLConfig();
}

void updateSparkViewROLConfig(void)
{
	switch(bleData.parameterID)
	{
	case COV:
		COV_ROL = (uint16_t)bleData.data;
		break;

	case COV_Delay:
		COV_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case COVR:
		COV_ROL_R = (uint16_t)bleData.data;
		break;

	case COVR_Delay:
		COV_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case CUV:
		CUV_ROL = (uint16_t)bleData.data;
		break;

	case CUV_Delay:
		CUV_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case CUVR:
		CUV_ROL_R = (uint16_t)bleData.data;
		break;

	case CUVR_Delay:
		CUV_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OCC:
		OCC_ROL = (int32_t)bleData.data;
		break;

	case OCC_Delay:
		OCC_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case OCCR:
		OCC_ROL_R = (int32_t)bleData.data;
		break;

	case OCCR_Delay:
		OCC_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OCD:
		OCD_ROL = (int32_t)bleData.data;
		break;

	case OCD_Delay:
		OCD_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case OCDR:
		OCD_ROL_R = (int32_t)bleData.data;
		break;

	case OCDR_Delay:
		OCD_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OTC:
		OTC_ROL = (int16_t)bleData.data;
		break;

	case OTC_Delay:
		OTC_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case OTCR:
		OTC_ROL_R = (int16_t)bleData.data;
		break;

	case OTCR_Delay:
		OTC_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case UTC:
		UTC_ROL = (int16_t)bleData.data;
		break;

	case UTC_Delay:
		UTC_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case UTCR:
		UTC_ROL_R = (int16_t)bleData.data;
		break;

	case UTCR_Delay:
		UTC_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case OTD:
		OTD_ROL = (int16_t)bleData.data;
		break;

	case OTD_Delay:
		OTD_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case OTDR:
		OTD_ROL_R = (int16_t)bleData.data;
		break;

	case OTDR_Delay:
		OTD_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case UTD:
		UTD_ROL = (int16_t)bleData.data;
		break;

	case UTD_Delay:
		UTD_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case UTDR:
		UTD_ROL_R = (int16_t)bleData.data;
		break;

	case UTDR_Delay:
		UTD_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case CVD:
		CVD_ROL = (uint16_t)bleData.data;
		break;

	case CVD_Delay:
		CVD_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case CVDR:
		CVD_ROL_R = (uint16_t)bleData.data;
		break;

	case CVDR_Delay:
		CVD_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case SOCH:
		SOCH_ROL = (uint8_t)bleData.data;
		break;

	case SOCH_Delay:
		SOCH_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case SOCHR:
		SOCH_ROL_R = (uint8_t)bleData.data;
		break;

	case SOCHR_Delay:
		SOCH_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	case SOCL:
		SOCL_ROL = (uint8_t)bleData.data;
		break;

	case SOCL_Delay:
		SOCL_ROL_DELAY = (uint16_t)bleData.data;
		break;

	case SOCLR:
		SOCL_ROL_R = (uint8_t)bleData.data;
		break;

	case SOCLR_Delay:
		SOCL_ROL_R_DELAY = (uint16_t)bleData.data;
		break;

	}

	sendSparkViewROLConfig();
}

void postProcessingData(char *RcvdData)
{
	uint8_t dataStartBit = 5;
	uint8_t negDataStartBit = 6;
	uint8_t negFlag = 0;
	int32_t data = 0;
	bleData.pageID = (RcvdData[0] - '0');
	bleData.mssgReq = (RcvdData[1] - '0');
	if(bleData.mssgReq == 0)
	{
		bleData.parameterID = (RcvdData[2] - '0')*10 + (RcvdData[3] - '0');

		if((RcvdData[dataStartBit] - '0') >= 0)
		{
			bleData.dataLen = (RcvdData[4] - '0');
			negFlag = 0;
		}
		else
		{
			bleData.dataLen = (RcvdData[4] - '0') - 1;
			negFlag = 1;
		}

		if(negFlag == 0)
		{
			for(uint8_t i =0; i<bleData.dataLen; i++)
			{
				data += (RcvdData[dataStartBit] - '0')*pow(10,(bleData.dataLen - i - 1));
				dataStartBit++;
			}
		}
		else if(negFlag == 1)
		{
			for(uint8_t i =0; i<bleData.dataLen; i++)
			{
				data += (RcvdData[negDataStartBit] - '0')*pow(10,(bleData.dataLen - i - 1));
				negDataStartBit++;
			}
			data = data*-1;
		}



		bleData.data = data;
		switch (bleData.pageID)
		{
			case GENERAL:
				updateSparkViewGeneralConfig();
				break;

			case MSL:
				updateSparkViewMSLConfig();
				break;

			case MOL:
				updateSparkViewMOLConfig();
				break;

			case ROL:
				updateSparkViewROLConfig();
				break;
		}

	}
	else
	{
		bleData.parameterID = 0;
		bleData.dataLen = 0;
		bleData.data = 0;
		switch (bleData.pageID)
		{
			case GENERAL:
				sendSparkViewGeneralConfig();
				EEPROM_ReadFlag = 1;
				break;

			case MSL:
				sendSparkViewMSLConfig();
				break;

			case MOL:
				sendSparkViewMOLConfig();
				break;

			case ROL:
				sendSparkViewROLConfig();
				break;

			case HOME:
				sendSparkViewHome();
				EEPROM_ReadFlag = 1;
				break;

			case LIVEDATA:
				sendSparkViewLive();
				EEPROM_ReadFlag = 1;
				break;

			case DATABASE:
				if(EEPROM_ReadFlag != 0)
				{
					sendSparkViewDatabase();
				}
				break;
		}
	}

}

void Ringbuf_init(void)
{
	_rx_buffer = &rx_buffer;
	_tx_buffer = &tx_buffer;

	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
//	__HAL_UART_ENABLE_IT(&uart_cfg[1], UART_IT_ERR);

	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&uart_cfg[0], UART_IT_RXNE);
}

void store_char(unsigned char c, ring_buffer *buffer)
{
	int i = (unsigned int)(buffer->head + 1) % UART_BUFFER_SIZE;

	if(i != buffer->tail) {
		buffer->buffer[buffer->head] = c;
		buffer->head = i;
	}
}

int IsDataAvailable(void)
{
	return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % UART_BUFFER_SIZE;
}

void Uart_isr (UART_HandleTypeDef *huart)
{
//	uint32_t isrflags   = READ_REG(huart->Instance->ISR);
	uint32_t cr1its     = READ_REG(huart->Instance->CR1);

	/* if DR is not empty and the Rx Int is enabled */
	if (((huart->Instance->ISR & USART_ISR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
	{
		/******************
		 *  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun
		 *          error) and IDLE (Idle line detected) flags are cleared by software
		 *          sequence: a read operation to USART_SR register followed by a read
		 *          operation to USART_DR register.
		 * @note   RXNE flag can be also cleared by a read to the USART_DR register.
		 * @note   TC flag can be also cleared by software sequence: a read operation to
		 *          USART_SR register followed by a write operation to USART_DR register.
		 * @note   TXE flag is cleared only by a write to the USART_DR register.

		 *********************/
		huart->Instance->ISR;                       /* Read status register */
		unsigned char c = huart->Instance->RDR;     /* Read data register */
		store_char (c, _rx_buffer);  // store data in buffer
		return;
	}

	/*If interrupt is caused due to Transmit Data Register Empty */
	if (((huart->Instance->ISR & USART_ISR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
	{
		if(tx_buffer.head == tx_buffer.tail)
		{
			// Buffer empty, so disable interrupts
			__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

		}

		else
		{
			// There is more data in the output buffer. Send the next byte
			unsigned char c = tx_buffer.buffer[tx_buffer.tail];
			tx_buffer.tail = (tx_buffer.tail + 1) % UART_BUFFER_SIZE;

			/******************
			 *  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun
			 *          error) and IDLE (Idle line detected) flags are cleared by software
			 *          sequence: a read operation to USART_SR register followed by a read
			 *          operation to USART_DR register.
			 * @note   RXNE flag can be also cleared by a read to the USART_DR register.
			 * @note   TC flag can be also cleared by software sequence: a read operation to
			 *          USART_SR register followed by a write operation to USART_DR register.
			 * @note   TXE flag is cleared only by a write to the USART_DR register.

			 *********************/

			huart->Instance->ISR;
			huart->Instance->RDR = c;

		}
		return;
	}
}

void Uart_read(char data[])
{
	if(!(_rx_buffer->head == _rx_buffer->tail))
	{
		data[cnt] = _rx_buffer->buffer[_rx_buffer->tail];
		_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;
		cnt++;
	}
}

void clear_buffer(void)
{
	for (int i=0; i<1000; i++) buffer[i] = '\0';
}
