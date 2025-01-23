/*
 * wwdg_cfg.h
 *
 *  Created on: Apr 2, 2024
 *      Author: Welcome
 */

#ifndef CONFIG_INC_WWDG_CFG_H_
#define CONFIG_INC_WWDG_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern WWDG_HandleTypeDef	hwwdg_cfg;

extern IWDG_HandleTypeDef hiwdg_cfg;

void IWDG_Init(void);
void WWDG_Init(void);

#endif /* CONFIG_INC_WWDG_CFG_H_ */


