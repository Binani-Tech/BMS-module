/*
 * wwdg_cfg.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Welcome
 */

/*---------------------------------------Includes------------------------------------------------------*/

#include "wwdg_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/
/*
 * @brief
 * @arguments
 * @retvar
 */

WWDG_HandleTypeDef	hwwdg_cfg = {
		.Instance = WWDG,
		.Init.Prescaler = WWDG_PRESCALER_8,
		.Init.Window = 101,
		.Init.Counter = 103,
		.Init.EWIMode = WWDG_EWI_ENABLE,
};

IWDG_HandleTypeDef	hiwdg_cfg = {
		.Instance = IWDG,
		.Init.Prescaler = IWDG_PRESCALER_8,
		.Init.Window = 4095,
		.Init.Reload = 240,
};

void IWDG_Init(void)
{
	if (HAL_IWDG_Init(&hiwdg_cfg) != HAL_OK)
	{
		Error_Handler();
	}
}

void WWDG_Init(void)
{
	if (HAL_WWDG_Init(&hwwdg_cfg) != HAL_OK)
	{
		Error_Handler();
	}
}



