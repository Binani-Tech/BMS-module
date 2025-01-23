/*
 * @filename	i2c.c
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		i2c
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "i2c.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void I2C_Init(void)
{
	for(uint8_t i=0; i<i2c_cfg_length; i++)
	{
		if(HAL_I2C_Init(&i2c_cfg[i]) != HAL_OK)
		{
			Error_Handler();
		}

		/* Configure the Analog Filter */

		if (HAL_I2CEx_ConfigAnalogFilter(&i2c_cfg[i], I2C_ANALOGFILTER_ENABLE) != HAL_OK)
		{
			Error_Handler();
		}

		/* Configure the Digital Filter */

		if (HAL_I2CEx_ConfigDigitalFilter(&i2c_cfg[i], 0) != HAL_OK)
		{
			Error_Handler();
		}
	}

}
