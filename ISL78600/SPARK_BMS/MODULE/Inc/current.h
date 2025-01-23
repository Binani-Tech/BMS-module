/*
 * @filename	current.h
 * @author		SPARKBMS TEAM
 * @date		22-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		current
 * 
 * @brief		Add the description
 */
#ifndef MODULES_INC_CURRENT_H_
#define MODULES_INC_CURRENT_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "dma.h"
#include "adc.h"
#include "isl78600.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void CURRENT_StartRead(void);

#endif /* MODULES_INC_CURRENT_H_ */
