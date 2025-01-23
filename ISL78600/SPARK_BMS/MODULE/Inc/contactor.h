/*
 * @filename	contactor.h
 * @author		SPARKBMS TEAM
 * @date		21-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		contactor
 * 
 * @brief		Add the description
 */
#ifndef MODULES_INC_CONTACTOR_H_
#define MODULES_INC_CONTACTOR_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "timer.h"
#include "database.h"
#include "gpio.h"
#include "fault_manager.h"
#include "can.h"

/*---------------------------------------Macros--------------------------------------------------------*/



/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t Delay_req;
extern bool cont_errorFlag;
extern bool cont_init;

/*---------------------------------------Function Prototypes-------------------------------------------*/

void CONT_Init(void);

void CONT_StateRequest(CONTACTOR_STATE_e state);

void CONT_DCDC(CONTACTOR_STATE_e state);

void Seq_Check(void);

void CONT_MainSequence(void);
void CONT_StopSequence(void);

void CONT_Slow_CHR_Seq(void);
void CONT_SlowChr_Disable(void);

void CONT_Fast_CHR_Seq(void);
void CONT_FastChr_Disable(void);

void CONT_HVAC_Seq(void);
void CONT_HVAC_Disable(void);

void CONT_REQ_Open(void);

void CONT_MainSequence(void);

void CONT_StopSequence(void);

void CONT_Dealy(void);

void ERROR_Dealy(void);

void CONT_Open(GPIO_PINs cont_name);

void CONT_Close(GPIO_PINs cont_name);

#endif /* MODULES_INC_CONTACTOR_H_ */
