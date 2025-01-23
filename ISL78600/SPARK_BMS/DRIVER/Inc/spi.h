/*
 * @filename	spi.h
 * @author		SPARKBMS TEAM
 * @date		May 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		spi
 * 
 * @brief		Add the description
 */
#ifndef DRIVER_INC_SPI_H_
#define DRIVER_INC_SPI_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "spi_cfg.h"
#include "mcu_cfg.h"
#include "gpio_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void SPI_Init(void);

void SPI_CS_Low(void);
void SPI_CS_High(void);

#endif /* DRIVER_INC_SPI_H_ */
