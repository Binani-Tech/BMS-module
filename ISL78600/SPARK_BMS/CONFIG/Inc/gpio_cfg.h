/*
 * @filename	gpio_cfg.h
 * @author		SPARKBMS TEAM
 * @date		13-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		gpio_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_GPIO_CFG_H_
#define CONFIG_INC_GPIO_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define GPIO_NO_ALTERNATIVE		0XFF

/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern GPIO_InitTypeDef gpio_cfg[];
extern uint8_t gpio_cfg_length;

#endif /* CONFIG_INC_GPIO_CFG_H_ */
