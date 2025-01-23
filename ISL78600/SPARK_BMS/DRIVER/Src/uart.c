/*
 * @filename	uart.c
 * @author		SPARKBMS TEAM
 * @date		12-Apr-2023
 * @ingroup		DRIVERS
 * @prefix		UART
 *
 * @brief		Driver of UART
 * 
 * This module implements the configuration of UART Driver based on UART_Config files. Currently, UART
 * is used for the communication with the BQ76PL455 AFE as well as with the PC Software for user
 * configuration (Need to be implemented later).
 *
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "uart.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

uint8_t Rcvd_Data[2] = {0};

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void UART_Init(void)
{
	for(uint8_t i = 0; i < uart_cfg_length; i++)
	{
		HAL_UART_Init(&uart_cfg[i]);
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void UART_AFE_Write(uint8_t *data, uint8_t size, uint8_t timeout)
{
	if(size>0)
	{
		HAL_UART_Transmit(&uart_cfg[0], data , size, timeout);
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void UART_AFE_Read(uint8_t *data, uint8_t size, uint8_t timeout)
{
	HAL_UART_Receive(&uart_cfg[0], data, size, timeout);
	if ((data[0]+1)!=(size-3))
	{
		AFE_WriteReg(BQ_ADDR, 81, 0X10, 1, FRMWRT_SGL_NR);
		AFE_WriteReg(BQ_ADDR, 81, 0X08, 1, FRMWRT_SGL_NR);
		AFE_Wakeup();
		HAL_Delay(5);
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void UART_EEPROM_Send(uint8_t *data, uint8_t size, uint8_t timeout)
{
	if(size>0)
	{
		HAL_UART_Transmit(&uart_cfg[1], data , size, timeout);
	}
}

void UART_Check_EEPROM_Request(void)
{
	HAL_UART_Receive_IT(&uart_cfg[1],Rcvd_Data, 2);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint16_t data = 0;
	data = (Rcvd_Data[0] << 8) | Rcvd_Data[1];

	if(data == 1909)
	{
		EEPROM_ReadFlag = 1;
	}
}

void UART_BLE_Send(uint8_t *data, uint8_t size, uint8_t timeout)
{
	if(size>0)
	{
		HAL_UART_Transmit(&uart_cfg[1], data , size, timeout);
	}
}

void UART_HC05_Send(uint8_t *data, uint8_t size, uint8_t timeout)
{
	if(size>0)
	{
		HAL_UART_Transmit(&uart_cfg[1], data , size, timeout);
	}
}

void UART_BLE_Receive(uint8_t *data, uint8_t size, uint8_t timeout)
{
	HAL_UART_Receive(&uart_cfg[1], data, size, timeout);
}
