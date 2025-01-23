/*
 * @filename	shortcircuit.h
 * @author		SPARKBMS TEAM
 * @date		01-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		shortcircuit
 * 
 * @brief		Add the description
 */
#ifndef APPLICATION_INC_SHORTCIRCUIT_H_
#define APPLICATION_INC_SHORTCIRCUIT_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "database.h"
#include "fault_cfg.h"
#include "contactor.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t short_circuit;

/*---------------------------------------Function Prototypes-------------------------------------------*/

void SHORTCIRCUIT_FaultManager(int32_t *Current);

void SHORTCIRCUIT_ClearFault(int32_t *Current);

#endif /* APPLICATION_INC_SHORTCIRCUIT_H_ */
