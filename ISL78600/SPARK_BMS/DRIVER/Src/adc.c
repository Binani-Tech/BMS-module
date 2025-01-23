/*
 * @filename	adc.c
 * @author		SPARKBMS TEAM
 * @date		Apr 14, 2023
 * @ingroup		FOLDER NAME
 * @prefix		adc
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "adc.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

uint16_t rawADC[ADC_NO_OF_CONVERSION] = {0};

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void ADC_Init(void)
{
	if(HAL_ADC_Init(&adc_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	for(uint8_t i=0; i<adc_channel_cfg_length; i++)
	{
		if(HAL_ADC_ConfigChannel(&adc_cfg, &adc_channel_cfg[i]) != HAL_OK)
		{
			Error_Handler();
		}
	}
}

