/*
 * @filename	dma_cfg.c
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		dma_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "dma_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

DMA_HandleTypeDef	dma_cfg[] = {
		{
				.Instance = DMA1_Channel1,
				.Init.Request = DMA_REQUEST_0,
				.Init.Mode = DMA_CIRCULAR,
				.Init.Direction = DMA_PERIPH_TO_MEMORY,
				.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD,
				.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD,
				.Init.PeriphInc = DMA_PINC_DISABLE,
				.Init.MemInc = DMA_MINC_ENABLE,
				.Init.Priority = DMA_PRIORITY_LOW
		}
};

uint8_t dma_cfg_length = sizeof(dma_cfg)/sizeof(dma_cfg[0]);
