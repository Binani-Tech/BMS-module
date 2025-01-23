/*
 * @filename	balancing.h
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		balancing
 * 
 * @brief		Add the description
 */
#ifndef APPLICATION_INC_BALANCING_H_
#define APPLICATION_INC_BALANCING_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "afe.h"
#include "bq76pl455.h"
#include "fault_cfg.h"
#include "database.h"
#include "timer.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void BAL_Check(void);
void BAL_START(void);
void BAL_STOP(void);

#endif /* APPLICATION_INC_BALANCING_H_ */
