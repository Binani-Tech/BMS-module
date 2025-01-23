/*
 * @filename	dma.c
 * @author		SPARKBMS TEAM
 * @date		Apr 14, 2023
 * @ingroup		FOLDER NAME
 * @prefix		dma
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "dma.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void DMA_Init(void)
{
	__HAL_RCC_DMA1_CLK_ENABLE();

	for(uint8_t i=0; i<dma_cfg_length ; i++)
	{
		if(HAL_DMA_Init(&dma_cfg[i]) != HAL_OK)
		{
			Error_Handler();
		}
	}
}
