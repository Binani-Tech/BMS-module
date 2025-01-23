/*
 * @filename	gpio.h
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		gpio
 * 
 * @brief		Add the description
 */
#ifndef DRIVERS_INC_GPIO_H_
#define DRIVERS_INC_GPIO_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "gpio_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void GPIO_Init(const GPIO_InitTypeDef *gpio_cfg);
void BOOT0_Init(void);

uint8_t GPIO_ReadPin(GPIO_PINs pin);
void GPIO_WritePin(GPIO_PINs pin, uint8_t value);
void GPIO_TogglePin(GPIO_PINs pin);

#endif /* DRIVERS_INC_GPIO_H_ */
