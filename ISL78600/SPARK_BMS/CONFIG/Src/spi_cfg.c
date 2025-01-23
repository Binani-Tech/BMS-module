/*
 * @filename	spi_cfg.c
 * @author		SPARKBMS TEAM
 * @date		May 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		spi_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "spi_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

SPI_HandleTypeDef	spi_cfg[] = {
		{
				.Instance = SPI2,
				.Init.Mode = SPI_MODE_MASTER,
				.Init.Direction = SPI_DIRECTION_2LINES,
				.Init.DataSize = SPI_DATASIZE_8BIT,
				.Init.CLKPolarity = SPI_POLARITY_LOW,
				.Init.CLKPhase = SPI_PHASE_1EDGE,
				.Init.NSS = SPI_NSS_SOFT,
				.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32,
				.Init.FirstBit = SPI_FIRSTBIT_MSB,
				.Init.TIMode = SPI_TIMODE_DISABLE,
				.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE,
				.Init.CRCPolynomial = 7,
				.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE,
				.Init.NSSPMode = SPI_NSS_PULSE_ENABLE,
		},
		{
				.Instance = SPI3,
				.Init.Mode = SPI_MODE_MASTER,
				.Init.Direction = SPI_DIRECTION_2LINES,
				.Init.DataSize = SPI_DATASIZE_8BIT,
				.Init.CLKPolarity = SPI_POLARITY_LOW,
				.Init.CLKPhase = SPI_PHASE_1EDGE,
				.Init.NSS = SPI_NSS_SOFT,
				.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4,
				.Init.FirstBit = SPI_FIRSTBIT_MSB,
				.Init.TIMode = SPI_TIMODE_DISABLE,
				.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE,
				.Init.CRCPolynomial = 7,
				.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE,
				.Init.NSSPMode = SPI_NSS_PULSE_ENABLE,
		}

};

uint8_t spi_cfg_length = sizeof(spi_cfg)/sizeof(spi_cfg[0]);
