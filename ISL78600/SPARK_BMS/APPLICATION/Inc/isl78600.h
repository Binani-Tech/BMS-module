/*
 * @filename	isl78600.h
 * @author		SPARKBMS TEAM
 * @date		May 25, 2023
 * @ingroup		FOLDER NAME
 * @prefix		isl78600
 * 
 * @brief		Add the description
 */
#ifndef APPLICATION_INC_ISL78600_H_
#define APPLICATION_INC_ISL78600_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "database.h"
#include "gpio.h"
#include "contactor.h"
#include "balancing.h"
#include "fault_monitor.h"
#include "timer.h"
#include "shortcircuit.h"
#include "adc.h"
#include "adc_exp.h"
#include "wwdg_cfg.h"
#include "soc.h"
#include "ble.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define NO_ERROR	0
#define ERROR	 	1

/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t short_circuit;

/*---------------------------------------Function Prototypes-------------------------------------------*/

void ISL_AFE_Init(void);

void ISL_AFE_ReadVoltage(void);

void ISL_AFE_ReadTemperature(void);

void CURRENT_Read(uint16_t *rawADC);

void ISO_VOLTAGE_Read(void);

uint8_t ISL_AFE_CheckError(void);

void ISL_AFE_GETState(void);

int32_t movingAvg(int32_t *ptrArrNumbers, int32_t *ptrSum, uint8_t len, int32_t nextNum);

int32_t movingAvg1(int32_t *ptrArrNumbers, int32_t *ptrSum, uint8_t len, int32_t nextNum);

void TEMP_ADC_Read(uint16_t *rawADC, int16_t *temperature);

#endif /* APPLICATION_INC_ISL78600_H_ */
