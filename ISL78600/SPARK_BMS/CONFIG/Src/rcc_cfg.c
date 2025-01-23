/*
 * @filename	rcc_cfg.c
 * @author		SPARKBMS TEAM
 * @date		14-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rcc_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "rcc_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

RCC_OscInitTypeDef	OscInitStruct = {
		.OscillatorType = RCC_OSCILLATORTYPE_HSE,
		.HSEState = RCC_HSE_ON,
		.PLL.PLLState = RCC_PLL_ON,
		.PLL.PLLSource = RCC_PLLSOURCE_HSE,
		.PLL.PLLM = RCC_PLL_M,
		.PLL.PLLN = RCC_PLL_N,
		.PLL.PLLP = RCC_PLL_P,
		.PLL.PLLQ = RCC_PLL_Q,
		.PLL.PLLR = RCC_PLL_R
};

RCC_ClkInitTypeDef	ClkInitStruct = {
		.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK,
		.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
		.AHBCLKDivider = RCC_AHB_PRESCALER,
		.APB1CLKDivider = RCC_APB1_PRESCALER,
		.APB2CLKDivider = RCC_APB2_PRESCALER
};
