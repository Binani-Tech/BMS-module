/*
 * @filename	rcc.c
 * @author		SPARKBMS TEAM
 * @date		14-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rcc
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "rcc.h"
#include "mcu_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void RCC_Init(void)
{
	if(HAL_RCC_OscConfig(&OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_RCC_ClockConfig(&ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_RCC_SYSCFG_CLK_ENABLE();
}
