/*
 * @filename	spi.c
 * @author		SPARKBMS TEAM
 * @date		May 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		spi
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "spi.h"
#include "gpio.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void SPI_Init(void)
{
	for(uint8_t i=0; i<spi_cfg_length; i++)
	{
		if(HAL_SPI_Init(&spi_cfg[i]) != HAL_OK)
		{
			Error_Handler();
		}
	}
}

void SPI_CS_Low(void)
{
	GPIO_WritePin(GPIO_PIN_AFE_SPI2_CS, 0);
}

void SPI_CS_High(void)
{
	GPIO_WritePin(GPIO_PIN_AFE_SPI2_CS, 1);
}

