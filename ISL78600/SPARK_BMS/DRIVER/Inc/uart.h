/*
 * @filename	uart.h
 * @author		SPARKBMS TEAM
 * @date		12-Apr-2023
 * @ingroup		DRIVERS
 * @prefix		UART
 * 
 * @brief		Header file for driver of UART
 */
#ifndef DRIVERS_INC_UART_H_
#define DRIVERS_INC_UART_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "uart_cfg.h"
#include "mcu_cfg.h"
#include "afe.h"
#include "eeprom.h"
#include "bq76pl455_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void UART_Init(void);
void UART_AFE_Write(uint8_t *data, uint8_t size, uint8_t timeout);
void UART_AFE_Read(uint8_t *data, uint8_t size, uint8_t timeout);
void UART_EEPROM_Send(uint8_t *data, uint8_t size, uint8_t timeout);
void UART_Check_EEPROM_Request(void);
void UART_BLE_Send(uint8_t *data, uint8_t size, uint8_t timeout);
void UART_HC05_Send(uint8_t *data, uint8_t size, uint8_t timeout);
void UART_BLE_Receive(uint8_t *data, uint8_t size, uint8_t timeout);

#endif /* DRIVERS_INC_UART_H_ */
