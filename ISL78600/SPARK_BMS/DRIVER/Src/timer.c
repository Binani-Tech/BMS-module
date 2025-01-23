/*
 * @filename	timer.c
 * @author		SPARKBMS TEAM
 * @date		Apr 15, 2023
 * @ingroup		FOLDER NAME
 * @prefix		timer
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "timer.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void BASIC_TIMER_Init(void)
{
	if(HAL_TIM_Base_Init(&basic_timer_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_Base_Start(&basic_timer_cfg);

	if(HAL_TIM_Base_Init(&delay_timer_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIM_ConfigClockSource(&delay_timer_cfg, &delay_timer_clock_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIMEx_MasterConfigSynchronization(&delay_timer_cfg, &delay_timer_master_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_Base_Start(&delay_timer_cfg);

//	__HAL_RCC_TIM6_CLK_ENABLE();
}

void TIMER_Delay_us(uint16_t micros)
{
	__HAL_TIM_SET_COUNTER(&delay_timer_cfg,0);
	while(__HAL_TIM_GET_COUNTER(&delay_timer_cfg) < (micros));
}

void TIMER_Delay_ms(uint16_t millis)
{
	__HAL_TIM_SET_COUNTER(&delay_timer_cfg,0);
	while(__HAL_TIM_GET_COUNTER(&delay_timer_cfg) < (millis*1000));
}

void GENERAL_TIMER_Init(void)
{
	if(HAL_TIM_Base_Init(&gp_timer_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIM_ConfigClockSource(&gp_timer_cfg, &gp_clock_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIMEx_MasterConfigSynchronization(&gp_timer_cfg, &gp_master_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_Base_Start(&gp_timer_cfg);
}

void TIMER7_Init(void)
{
	if(HAL_TIM_Base_Init(&timer7_cfg) != HAL_OK)
	{
		Error_Handler();
	}
}

void TIMER7_Start(void)
{
	HAL_TIM_Base_Start_IT(&timer7_cfg);
}

void TIMER7_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&timer7_cfg);
}

void TIMER7_Reset(void)
{
	__HAL_TIM_SET_COUNTER(&timer7_cfg,0);
}
