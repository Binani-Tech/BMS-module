/*
 * @filename	nvic.c
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		nvic
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "nvic.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void NVIC_Init(void)
{
	for(uint8_t i=0; i<nvic_cfg_length; i++)
	{
		if(nvic_cfg[i].priority <= MAX_PRIORITY_VALUE && nvic_cfg[i].IRQ_No < (MAX_NUMBER_OF_NVIC_POSITION + 1))
		{
			HAL_NVIC_SetPriority(nvic_cfg[i].IRQ_No, nvic_cfg[i].priority, nvic_cfg[i].subpriority);
		}

		if(nvic_cfg[i].state == NVIC_ENABLE)
		{
			HAL_NVIC_EnableIRQ(nvic_cfg[i].IRQ_No);
		}
	}
}
