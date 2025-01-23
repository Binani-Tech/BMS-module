/*
 * @filename	timer_cfg.h
 * @author		SPARKBMS TEAM
 * @date		Apr 15, 2023
 * @ingroup		FOLDER NAME
 * @prefix		timer_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_TIMER_CFG_H_
#define CONFIG_INC_TIMER_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern TIM_HandleTypeDef	basic_timer_cfg;

extern TIM_HandleTypeDef	gp_timer_cfg;

extern TIM_ClockConfigTypeDef	gp_clock_cfg;

extern TIM_MasterConfigTypeDef	gp_master_cfg;

extern TIM_HandleTypeDef	timer7_cfg;

extern TIM_HandleTypeDef	delay_timer_cfg;

extern TIM_ClockConfigTypeDef	delay_timer_clock_cfg;

extern TIM_MasterConfigTypeDef	delay_timer_master_cfg;

#endif /* CONFIG_INC_TIMER_CFG_H_ */
