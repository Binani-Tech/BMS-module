/*
 * @filename	ble.h
 * @author		SPARKBMS TEAM
 * @date		31-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		ble
 * 
 * @brief		Add the description
 */
#ifndef MODULES_INC_BLE_H_
#define MODULES_INC_BLE_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "uart.h"
#include "database.h"
#include "fault_cfg.h"
#include "fault_manager.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

extern char sparkViewResponse;

#define UART_BUFFER_SIZE 20

typedef struct
{
	unsigned char buffer[UART_BUFFER_SIZE];
	uint8_t head;
	uint8_t tail;
}ring_buffer;

typedef enum
{
	HOME = 0,
	LIVEDATA,
	DATABASE,
	ROL,
	MOL,
	MSL,
	GENERAL
}PAGE_ID_e;

typedef enum
{
	DATA = 0,
	REQUEST
}UART_MSSG_e;

typedef enum
{
	NO_OF_CELL,
	NO_OF_TEMP,
	BAL_VOLTAGE,
	BAL_DIFFVOLT,
	BAL_CURRENT,
	BAL_STOPVOLT
}GENERAL_e;

typedef enum
{
	COV,
	COV_Delay,
	COVR,
	COVR_Delay,
	CUV,
	CUV_Delay,
	CUVR,
	CUVR_Delay,
	OCC,
	OCC_Delay,
	OCCR,
	OCCR_Delay,
	OCD,
	OCD_Delay,
	OCDR,
	OCDR_Delay,
	OTC,
	OTC_Delay,
	OTCR,
	OTCR_Delay,
	UTC,
	UTC_Delay,
	UTCR,
	UTCR_Delay,
	OTD,
	OTD_Delay,
	OTDR,
	OTDR_Delay,
	UTD,
	UTD_Delay,
	UTDR,
	UTDR_Delay,
	CVD,
	CVD_Delay,
	CVDR,
	CVDR_Delay,
	SOCH,
	SOCH_Delay,
	SOCHR,
	SOCHR_Delay,
	SOCL,
	SOCL_Delay,
	SOCLR,
	SOCLR_Delay
}CONFIG_PARAM_e;


typedef struct
{
	uint8_t pageID;
	uint8_t mssgReq;
	uint8_t parameterID;
	uint8_t dataLen;
	int32_t data;
}BLEDATA_s;

/*---------------------------------------Function Prototypes-------------------------------------------*/

void BLE_Init(void);
void BLESparkViewInit(void);
void BLECheckSparkViewRequest(void);
void clear_buffer(void);

void UART_Send_Current(int32_t current,int32_t lcurrent);
void UART_Send_Index(void);
void UART_Send_ALLData(void);

void Data8toAscii2(uint8_t *Data8,uint8_t size,uint8_t *dData);
void postProcessingData(char *RcvdData);

void Uart_isr (UART_HandleTypeDef *huart);

void sendSparkViewHome(void);
void sendSparkViewLive(void);
void sendSparkViewDatabase(void);

void sendSparkViewGeneralConfig(void);
void sendSparkViewMSLConfig(void);
void sendSparkViewMOLConfig(void);
void sendSparkViewROLConfig(void);

void updateSparkViewGeneralConfig(void);
void updateSparkViewMSLConfig(void);
void updateSparkViewMOLConfig(void);
void updateSparkViewROLConfig(void);


#endif /* MODULES_INC_BLE_H_ */
