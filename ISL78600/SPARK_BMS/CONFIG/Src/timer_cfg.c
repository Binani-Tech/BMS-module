/*
 * @filename	timer_cfg.c
 * @author		SPARKBMS TEAM
 * @date		Apr 15, 2023
 * @ingroup		FOLDER NAME
 * @prefix		timer_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "timer_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

TIM_HandleTypeDef	basic_timer_cfg = {
		.Instance = TIM6,
		.Init.Prescaler = 8000 - 1,
		.Init.Period = 10000 - 1,		// 1 sec
		.Init.CounterMode = TIM_COUNTERMODE_UP
};

TIM_HandleTypeDef	timer7_cfg = {
		.Instance = TIM7,
		.Init.Prescaler = 80 - 1,
		.Init.Period = 50000 - 1,		// 50 ms
		.Init.CounterMode = TIM_COUNTERMODE_UP
};

TIM_HandleTypeDef	gp_timer_cfg = {
		.Instance = TIM2,
		.Init.Prescaler = 10 - 1,
		.Init.Period = 4000 - 1,		// 500 usec
		.Init.CounterMode = TIM_COUNTERMODE_UP
};

TIM_ClockConfigTypeDef	gp_clock_cfg = {
		.ClockSource = TIM_CLOCKSOURCE_INTERNAL,
};

TIM_MasterConfigTypeDef	gp_master_cfg = {
		.MasterOutputTrigger = TIM_TRGO_UPDATE,
		.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE
};

TIM_HandleTypeDef	delay_timer_cfg = {
		.Instance = TIM15,
		.Init.Prescaler = 80 - 1,
		.Init.Period = 50000 - 1,		// 50 ms
		.Init.CounterMode = TIM_COUNTERMODE_UP
};

TIM_ClockConfigTypeDef	delay_timer_clock_cfg = {
		.ClockSource = TIM_CLOCKSOURCE_INTERNAL,
};

TIM_MasterConfigTypeDef	delay_timer_master_cfg = {
		.MasterOutputTrigger = TIM_TRGO_UPDATE,
		.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE
};
