/*
 * @filename	current.c
 * @author		SPARKBMS TEAM
 * @date		22-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		current
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "current.h"
#include "adc_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void CURRENT_StartRead(void)
{
	HAL_ADC_Start_DMA(&adc_cfg, (uint32_t*)rawADC, ADC_NO_OF_CONVERSION);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
//	GPIO_WritePin(GPIO_PIN_LED4, 1);
	CURRENT_Read(rawADC);
}
