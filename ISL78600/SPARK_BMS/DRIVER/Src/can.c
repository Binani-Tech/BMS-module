/*
 * @filename	can.c
 * @author		SPARKBMS TEAM
 * @date		04-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		can
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "can.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

uint8_t DataRx[8];
uint8_t can_rxflag = 0;
uint32_t VRX = 0;
uint32_t VRX_STD = 0;
uint32_t TxMailBox;
CAN_TxHeaderTypeDef	can_tx_cfg;
CAN_RxHeaderTypeDef	can_rx_cfg;

uint8_t CAN_Request = 0;
bool read_flag = 0;
//static uint8_t IMD_Data[8] = {0};
bool imd_reflag = 0;

bool Req_MainSeq     = 0;
bool Req_ContDisable = 0;
bool Req_SlowChrSeq  = 0;
bool Req_FastChrSeq  = 0;
bool Req_HVACSeq     = 0;

uint8_t CHR_STATE = 0x11;
/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void CAN1_Init(void)
{
	if(HAL_CAN_Init(&can_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	CAN1_FilterConfig();

//	GPIO_WritePin(GPIO_PIN_CAN1_STB, 0);

	if(HAL_CAN_ActivateNotification(&can_cfg, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_CAN_Start(&can_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
}

void CAN1_FilterConfig(void)
{
	if(HAL_CAN_ConfigFilter(&can_cfg, &can_filter_cfg) != HAL_OK)
	{
		Error_Handler();
	}
}

void CAN1_Rx(void)
{
	CAN_RxHeaderTypeDef	can_rx_cfg;

	if(HAL_CAN_GetRxMessage(&can_cfg, CAN_RX_FIFO0, &can_rx_cfg, DataRx) != HAL_OK)
	{
		Error_Handler();
	}

	VRX = can_rx_cfg.ExtId;
	VRX_STD = can_rx_cfg.StdId;
	can_rxflag = 1;
	if(can_rx_cfg.RTR == CAN_RTR_REMOTE)
	{
		switch(VRX)
		{
			case CAN_FAULTS_1:
				CAN_Send_Fault_1();
				break;

			case CAN_FAULTS_2:
				CAN_Send_Fault_2();
				break;

			case CAN_WARNING_1:
				CAN_Send_Warning_1();
				break;

			case CAN_WARNING_2:
				CAN_Send_Warning_2();
				break;

			case CAN_CONTACTOR_STATUS:
				CAN_Send_Cont_Status();
				break;

			case CAN_BATTERY_SUMMARY:
				CAN_Send_Summary();
				break;

			case CAN_MIN_MAX_VOLTAGE:
				CAN_Send_MinMax_VOLTAGE();
				break;

			case CAN_MIN_MAX_TEMP:
				CAN_Send_MinMax_TEMP();
				break;

			case CAN_PACK_SUMMARY_VOLTAGE:
				CAN_Send_PackSummary_VOLTAGE();
				break;

			case CAN_PACK_SUMMARY_CURRENT:
				CAN_Send_PackSummary_CURRENT();
				break;

			case CAN_PACK_SUMMARY_SOX:
				CAN_Send_PackSummary_SOX();
				break;

//			case CAN_PACK_SUMMARY_POWER:
//				CAN_Send_PackSummary_POWER();
//				break;

//			case CAN_IMD_ID:
//				if(imd_reflag != 0)
//				{
//					CAN_IMD_Send();
//				}
//			    break;

			case CAN_BMS_CHG_MSG:
				 CAN_Send_CHG_MSG();
				 break;

			case CAN_AFE_INIT:
				 WWDG_Init();
				 break;

			case CAN_ALL_MSSG:
				 CAN_Send_MASTER_PACK();
				 break;

			case CAN_MASTER_PACK:
				 CAN_Send_MASTER_PACK();
				 break;

			case CAN_SLAVE_1:
				 CAN_Send_Slave_PACK();
				 break;

			case CAN_SLAVE_2:
				 CAN_Send_Slave_PACK();
				 break;

			case CAN_SLAVE_3:
				 CAN_Send_Slave_PACK();
				 break;

			case CAN_SLAVE_4:
				 CAN_Send_Slave_PACK();
				 break;

			case CAN_SLAVE_5:
				 CAN_Send_Slave_PACK();
				 break;

			case CAN_SLAVE_6:
				 CAN_Send_Slave_PACK();
				 break;

			case CAN_SLAVE_7:
				 CAN_Send_Slave_PACK();
				 break;

			default:
//				CAN_Send_All_Voltages();
//				CAN_Send_All_Temperature();
//				CAN_Send_All_BalancingSummary();
				break;
		}

	}
	else if(can_rx_cfg.RTR == CAN_RTR_DATA)
	{
		switch(VRX)
		{
//		   case CAN_IMD_ID:
//			    IMD_read();
//			    break;

		   case MAIN_CONT_SEQ:
			    CAN_MAIN_SEQ();
			    break;

		   case SLOW_CHR_SEQ:
			    CAN_SLOW_CHR_SEQ();
			    break;

		   case FAST_CHR_SEQ:
			    CAN_FAST_CHR_SEQ();
			    break;

		   case HVAC_ENABLE:
			    CAN_HVAC_ENABLE();
			    break;

		   case CAN_CHR_BIT:
			    CAN_CHR_BIT_SET();
			    break;

		   case CAN_CHG_BMS_MSG:
			    CAN_Rev_CHG_MSG();
			    break;

		   default:
//			   if(VRX > CAN_VOLTAGES_BASE && VRX <= CAN_VOLTAGES_89_92	 )
//				   V_read();
//			   if(VRX > CAN_TEMP_BASE && VRX <= CAN_TEMP_1)
//				   T_read();
//			   if(VRX >= Max_Min_CV_S1 && VRX <= Max_Min_CV_S2)
//				   MaxMin_Voltage_read();
			   break;
		}
	}

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
//	HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
	CAN1_Rx();
//	CAN_Request = 1;
}

void CAN_MAIN_SEQ(void)
{
	if(DataRx[0] == 1)
		Req_MainSeq = 1;
	else if(DataRx[0] == 0)
		Req_MainSeq = 0;
//	Req_ContDisable = 0;
//	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data, &TxMailBox);
}

void CAN_SLOW_CHR_SEQ(void)
{
	if(DataRx[0] == 1)
		Req_SlowChrSeq = 1;

	else if(DataRx[0] == 0)
		Req_SlowChrSeq = 0;
}

void CAN_FAST_CHR_SEQ(void)
{
	if(DataRx[0] == 1)
		Req_FastChrSeq = 1;

	else if(DataRx[0] == 0)
		Req_FastChrSeq = 0;
}

void CAN_HVAC_ENABLE(void)
{
	if(DataRx[0] == 1)
		Req_HVACSeq = 1;

	else if(DataRx[0] == 0)
		Req_HVACSeq = 0;
}

void CAN_MAIN_SEQ_CPL(void)
{
	uint8_t Data = 1;

	can_tx_cfg.DLC = 1;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
	can_tx_cfg.ExtId = MAIN_CONT_SEQ;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data, &TxMailBox);
}

void CAN_SLOW_CHR_SEQ_CPL(void)
{
	uint8_t Data = 1;

	can_tx_cfg.DLC = 1;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
	can_tx_cfg.ExtId = SLOW_CHR_SEQ;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data, &TxMailBox);
}

void CAN_FAST_CHR_SEQ_CPL(void)
{
	uint8_t Data = 1;

	can_tx_cfg.DLC = 1;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
	can_tx_cfg.ExtId = FAST_CHR_SEQ;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data, &TxMailBox);
}

void CAN_HVAC_SEQ_CPL(void)
{
	uint8_t Data = 1;

	can_tx_cfg.DLC = 1;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
	can_tx_cfg.ExtId = HVAC_ENABLE;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data, &TxMailBox);
}

void CAN_Send_Fault_1(void)
{
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090301;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, FAULT_ARRAY, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_Fault_2(void)
{
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090302;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &FAULT_ARRAY[8], &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_Warning_1(void)
{
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090303;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, WARNING_ARRAY, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_Warning_2(void)
{
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090304;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &WARNING_ARRAY[8], &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_Cont_Status(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_CONTACTOR_s	can_database_contactor;

	DATABASE_READ((void*)(&can_database_contactor), DATABASE_CONTACTOR);

	Data[0] = can_database_contactor.CONT_MAIN_PLUS;
	Data[1] = can_database_contactor.CONT_MAIN_MINUS;
	Data[2] = can_database_contactor.CONT_PRECHARGE;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090305;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
}

void CAN_Send_Summary(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_BMS_s	can_database_bms;

	DATABASE_READ((void*)(&can_database_bms), DATABASE_BMS);

	Data[0] = can_database_bms.afe_state;
	Data[1] = can_database_bms.bms_state;
	Data[2] = can_database_bms.cont_state;
	Data[3] = can_database_bms.afe_error;
	Data[4] = can_database_bms.bms_error;
	Data[5] = can_database_bms.balancing_status;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090306;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_MinMax_VOLTAGE(void)
{
	uint8_t Data[8] = {0};

	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_EEPROM_s can_database_eeprom;

	DATABASE_READ((void*)(&can_database_eeprom), DATABASE_EEPROM);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090307;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Data[0] = (uint8_t)((can_database_eeprom.max_voltage & 0XFF00) >> 8);
	Data[1] = (uint8_t)(can_database_eeprom.max_voltage & 0X00FF);
	Data[2] = can_database_eeprom.max_voltage_index;
	Data[3] = (uint8_t)((can_database_eeprom.min_voltage & 0XFF00) >> 8);
	Data[4] = (uint8_t)(can_database_eeprom.min_voltage & 0X00FF);
	Data[5] = can_database_eeprom.min_voltage_index;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_MinMax_TEMP(void)
{
	uint8_t Data[8] = {0};

	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_EEPROM_s can_database_eeprom;

	DATABASE_READ((void*)(&can_database_eeprom), DATABASE_EEPROM);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090308;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Data[0] = (uint8_t)((can_database_eeprom.max_temperature & 0XFF00) >> 8);
	Data[1] = (uint8_t)(can_database_eeprom.max_temperature & 0X00FF);
	Data[2] = can_database_eeprom.max_temperature_index;
	Data[3] = (uint8_t)((can_database_eeprom.min_temperature & 0XFF00) >> 8);
	Data[4] = (uint8_t)(can_database_eeprom.min_temperature & 0X00FF);
	Data[5] = can_database_eeprom.min_temperature_index;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_PackSummary_VOLTAGE(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_EEPROM_s can_database_eeprom;

	DATABASE_READ((void*)(&can_database_eeprom), DATABASE_EEPROM);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090309;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Data[0] = (uint8_t)((can_database_eeprom.pack_voltage & 0XFF000000) >> 24);
	Data[1] = (uint8_t)((can_database_eeprom.pack_voltage & 0X00FF0000) >> 16);
	Data[2] = (uint8_t)((can_database_eeprom.pack_voltage & 0X0000FF00) >> 8);
	Data[3] = (uint8_t)((can_database_eeprom.pack_voltage & 0X000000FF));

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_PackSummary_CURRENT(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_EEPROM_s can_database_eeprom;

	DATABASE_READ((void*)(&can_database_eeprom), DATABASE_EEPROM);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090310;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Data[0] = (uint8_t)((can_database_eeprom.current & 0XFF000000) >> 24);
	Data[1] = (uint8_t)((can_database_eeprom.current & 0X00FF0000) >> 16);
	Data[2] = (uint8_t)((can_database_eeprom.current & 0X0000FF00) >> 8);
	Data[3] = (uint8_t)((can_database_eeprom.current & 0X000000FF));

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_PackSummary_SOX(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_EEPROM_s can_database_eeprom;

	DATABASE_READ((void*)(&can_database_eeprom), DATABASE_EEPROM);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.ExtId = 0X19090311;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Data[0] = can_database_eeprom.soc;
	Data[1] = can_database_eeprom.soh;
	Data[2] = (uint8_t)((can_database_eeprom.cycle_count & 0XFF00) >> 8);
	Data[3] = (uint8_t)(can_database_eeprom.cycle_count & 0X00FF);

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
}

void CAN_Send_MASTER_PACK(void)
{
	uint8_t Data[32] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_VOLTAGE_s can_database_voltage;

	DATABASE_READ((void*)(&can_database_voltage), DATABASE_VOLTAGE);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Unsigned_Data16toData8(Data, can_database_voltage.cell_voltage, 16);
	for(uint8_t i = 0 ; i<4 ; i++)
	{
		can_tx_cfg.ExtId = 0X19090312 + i;

		if(i==0)
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
		else if(i==3)
		{
			while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
		}
		else
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
	}

}

void CAN_Send_Slave_PACK(void)
{
	uint8_t Data[32] = {0};
	uint32_t TxMailBox;

	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_VOLTAGE_s can_database_voltage;

	DATABASE_READ((void*)(&can_database_voltage), DATABASE_VOLTAGE);
    uint8_t j = ((VRX - CAN_SLAVE_1)/4) + 1;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	for(uint8_t i = 0 ; i<4 ; i++)
	{
		can_tx_cfg.ExtId = VRX + i;

		if(i==0)
		{
			Unsigned_Data16toData8(Data, &can_database_voltage.cell_voltage[16*j], 16);
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
		}
		else if(i==3)
		{
			while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
		}
		else
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
	}

}

void CAN_Send_MASTER_TEMP(void)
{
	uint8_t Data[16] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_TEMPERATURE_s can_database_temperature;

	DATABASE_READ((void*)(&can_database_temperature), DATABASE_TEMPERATURE);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	Data16toData8(Data, can_database_temperature.pack_temperature, 8);
	for(uint8_t i = 0 ; i<2 ; i++)
	{
		can_tx_cfg.ExtId = 0X19090360 + i;

		if(i==0)
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
		else
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
	}

}

void CAN_Send_SLAVE_TEMP(void)
{
	uint8_t Data[16] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_TEMPERATURE_s can_database_temperature;
	uint8_t j = VRX - CAN_SLAVE_TEMPERATURES_1 + 1 ;

	DATABASE_READ((void*)(&can_database_temperature), DATABASE_TEMPERATURE);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	for(uint8_t i = 0 ; i<2 ; i++)
	{
		can_tx_cfg.ExtId = CAN_SLAVE_TEMPERATURES_1 + i;

		if(i==0)
		{
			Data16toData8(Data, &can_database_temperature.pack_temperature[4*j], 8);
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
		}
		else if(i==3)
			while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
		else
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
	}

}

void CAN_SendAll(void)
{
	CAN_Send_Fault_1();
	CAN_Send_Fault_2();
	CAN_Send_Warning_1();
	CAN_Send_Warning_2();
	CAN_Send_Cont_Status();
	CAN_Send_Summary();
	CAN_Send_MinMax_VOLTAGE();
	CAN_Send_MinMax_VOLTAGE();
//	CAN_Send_ALL_Voltage();
//	CAN_Send_ALL_Temp();
//	CAN_Send_ALL_BalancingSummary();
}

void CAN_Send_ALL_Voltage(void)
{
	for(uint8_t i = 0 ; i<12 ; i++)
	{
		VRX = can_rx_cfg.ExtId = (CAN_MASTER_PACK + i*4);
		if(i==0)
		{
			CAN_Send_MASTER_PACK();
		}
		else
		{
			CAN_Send_Slave_PACK();
		}
	}
}

void CAN_Send_ALL_Temp(void)
{
	for(uint8_t i = 0 ; i<12 ; i++)
	{
		if(i==0)
		{
			can_rx_cfg.ExtId = CAN_MASTER_TEMPERATURES;
			CAN_Send_MASTER_TEMP();
		}
		else
		{
			VRX = can_rx_cfg.ExtId = CAN_SLAVE_TEMPERATURES_1 + i*2;
			CAN_Send_SLAVE_TEMP();
		}
	}
}

void CAN_Send_ALL_BalancingSummary(void)
{
	for(uint8_t i = 0 ; i<12 ; i++)
	{
		can_rx_cfg.ExtId = (CAN_MASTER_BALANCING_STATE + i*2);
		CAN_Send_BalancingSummary();
	}
}

void CAN_Send_BalancingSummary(void)
{
	uint8_t Data[192] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_VOLTAGE_s can_database_voltage;

	DATABASE_READ((void*)(&can_database_voltage), DATABASE_VOLTAGE);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	uint8_t k = can_rx_cfg.ExtId - CAN_MASTER_BALANCING_STATE;
	for(uint8_t i=0; i<192; i++)
	{
		Data[i] = can_database_voltage.cell_balancing_status[i];
	}

	for(uint8_t j = 0 ; j<2 ; j++)
	{
		can_tx_cfg.ExtId = 0X19090388 + j + k;

		if(j == 0)
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);
		else
		{
			HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[8*j], &TxMailBox);
			while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));
		}
	}

}

void CAN_Send_MODULE_VOLTAGE(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_VOLTAGE_s can_database_voltage;

	DATABASE_READ((void*)(&can_database_voltage), DATABASE_VOLTAGE);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;

	uint8_t j = VRX - CAN_MODULE_VOLTAGE;

	can_tx_cfg.ExtId = CAN_MODULE_VOLTAGE + j;

	Data[0] = (uint8_t)((can_database_voltage.module_voltage[j] & 0XFF000000) >> 24);
	Data[1] = (uint8_t)((can_database_voltage.module_voltage[j] & 0X00FF0000) >> 16);
	Data[2] = (uint8_t)((can_database_voltage.module_voltage[j] & 0X0000FF00) >> 8);
	Data[3] = (uint8_t)((can_database_voltage.module_voltage[j] & 0X000000FF));

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);

	while(HAL_CAN_IsTxMessagePending(&can_cfg, TxMailBox));

}

void CAN_Send_Module_TEMP(void)
{
	uint8_t Data[16] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;
	DATABASE_TEMPERATURE_s can_database_temperature;

	DATABASE_READ((void*)(&can_database_temperature), DATABASE_TEMPERATURE);

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
	uint8_t i = VRX - CAN_MASTER_TEMPERATURES;
	can_tx_cfg.ExtId = CAN_MASTER_TEMPERATURES + i;

	Data16toData8(Data, &can_database_temperature.pack_temperature[i*4], 4);

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, &Data[4*i], &TxMailBox);
}

void CAN_Send_CHG_MSG(void)
{
	uint8_t Data[8] = {0};
	uint32_t TxMailBox;
	CAN_TxHeaderTypeDef	can_tx_cfg;

	can_tx_cfg.DLC = 8;
	can_tx_cfg.IDE = CAN_ID_EXT;
	can_tx_cfg.RTR = CAN_RTR_DATA;
	can_tx_cfg.ExtId = CAN_BMS_CHG_MSG;

	uint16_t POV_Limit = POV_MOL/100;
	uint16_t PUV_Limit = PUV_MOL/100;

	Data[0] =  (uint8_t)((POV_Limit & 0xFF00) >> 8);
	Data[1] =  (uint8_t)(POV_Limit & 0x00FF);
	Data[2] =  (uint8_t)((PUV_Limit & 0xFF00) >> 8);
	Data[3] =  (uint8_t)(PUV_Limit & 0x00FF);
	Data[4] =  CHR_STATE;
	Data[5] =  0x00;

	HAL_CAN_AddTxMessage(&can_cfg, &can_tx_cfg, Data, &TxMailBox);

}

void CAN_CHR_BIT_SET(void)
{
	CHR_STATE = DataRx[1];
}

void CAN_Rev_CHG_MSG(void)
{
	DATABASE_CHR_s can_database_chr;

	DATABASE_READ((void*)(&can_database_chr), DATABASE_CHR);

	can_database_chr.CHR_Voltage = ((DataRx[0] << 8) |  DataRx[1]);
	can_database_chr.CHR_Current = ((DataRx[2] << 8) |  DataRx[3]);
	can_database_chr.CHR_Temp = DataRx[7] + 40;

}

void Unsigned_Data16toData8(uint8_t *Data8, uint16_t *Data16, uint8_t Data16_Len)
{
	uint8_t cnt = 0;
	for(uint8_t i=0; i<Data16_Len; i++)
	{
		Data8[cnt] = (uint8_t)((Data16[i] & 0XFF00) >> 8);
		cnt++;
		Data8[cnt] = (uint8_t)((Data16[i] & 0X00FF));
		cnt++;
	}

}

void Data16toData8(uint8_t *Data8, int16_t *Data16, uint8_t Data16_Len)
{
	uint8_t cnt = 0;
	for(uint8_t i=0; i<Data16_Len; i++)
	{
		Data8[cnt] = (uint8_t)((Data16[i] & 0XFF00) >> 8);
		cnt++;
		Data8[cnt] = (uint8_t)((Data16[i] & 0X00FF));
		cnt++;
	}
}
