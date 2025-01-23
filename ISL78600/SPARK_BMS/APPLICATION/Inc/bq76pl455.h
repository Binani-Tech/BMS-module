/*
 * @filename	bq76pl455.h
 * @author		SPARKBMS TEAM
 * @date		21-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		bq76pl455
 * 
 * @brief		Add the description
 */
#ifndef MODULES_INC_BQ76PL455_H_
#define MODULES_INC_BQ76PL455_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "bq76pl455_cfg.h"
#include "database.h"
#include "gpio.h"
#include "contactor.h"
#include "balancing.h"
#include "fault_monitor.h"
#include "timer.h"
#include "shortcircuit.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define NO_ERROR	0
#define ERROR	 	1

#define DISCRETE_LPF	 1
#define ALPHA	 	    0.167

/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

uint16_t BQ_AFE_ReadSerialNo(void);

void BQ_AFE_Init(void);

void BQ_AFE_ReadVoltage(void);

void BQ_AFE_ReadTemperature(void);

void CURRENT_Read(uint16_t *rawADC);

uint8_t BQ_AFE_CheckError(void);

int32_t movingAvg(int32_t *ptrArrNumbers, int32_t *ptrSum, uint8_t len, int32_t nextNum);

void BQ_AFE_GETState(void);

#endif /* MODULES_INC_BQ76PL455_H_ */
