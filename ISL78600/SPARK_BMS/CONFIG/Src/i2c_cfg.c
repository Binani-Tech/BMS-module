/*
 * @filename	i2c_cfg.c
 * @author		SPARKBMS TEAM
 * @date		15-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		i2c_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "i2c_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

I2C_HandleTypeDef	i2c_cfg[] = {
		{
				.Instance = I2C1,
				.Init.Timing = 0x00300EAC,		// Fast Mode Plus : 0x00300B29;  Fast Mode : 0X00702991
				.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
				.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE,
				.Init.OwnAddress1 = 0,
				.Init.OwnAddress2 = 0,
				.Init.OwnAddress2Masks = I2C_OA2_NOMASK,
				.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE,
				.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE
		},
		{
				.Instance = I2C2,
				.Init.Timing = 0x00300B29,		// Fast Mode Plus : 0x00300B29;  Fast Mode : 0X00602173
				.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
				.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE,
				.Init.OwnAddress1 = 0,
				.Init.OwnAddress2 = 0,
				.Init.OwnAddress2Masks = I2C_OA2_NOMASK,
				.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE,
				.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE
		}
};

uint8_t i2c_cfg_length = sizeof(i2c_cfg)/sizeof(i2c_cfg[0]);
