/*
 * @filename	rcc_cfg.h
 * @author		SPARKBMS TEAM
 * @date		14-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		rcc_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_RCC_CFG_H_
#define CONFIG_INC_RCC_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define RCC_HSE_CLOCK				12			// Units : MHz
#define RCC_HSI_CLOCK				16			// Units : MHz

/* 64MHz Configuration */

#define RCC_PLL_M					3
#define RCC_PLL_N					40
#define RCC_PLL_R					RCC_PLLR_DIV2
#define RCC_PLL_Q					RCC_PLLQ_DIV2
#define RCC_PLL_P					RCC_PLLP_DIV7

#define RCC_AHB_PRESCALER_NUM		1
#define RCC_APB1_PRESCALER_NUM		1
#define RCC_APB2_PRESCALER_NUM		1

#if 	RCC_AHB_PRESCALER_NUM == 1
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV1
#elif	RCC_AHB_PRESCALER_NUM == 2
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV2
#elif	RCC_AHB_PRESCALER_NUM == 4
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV4
#elif	RCC_AHB_PRESCALER_NUM == 8
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV8
#elif	RCC_AHB_PRESCALER_NUM == 16
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV16
#elif	RCC_AHB_PRESCALER_NUM == 64
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV64
#elif	RCC_AHB_PRESCALER_NUM == 128
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV128
#elif	RCC_AHB_PRESCALER_NUM == 256
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV256
#elif	RCC_AHB_PRESCALER_NUM == 512
	#define RCC_AHB_PRESCALER		RCC_SYSCLK_DIV512
#endif

#if		RCC_APB1_PRESCALER_NUM == 1
	#define RCC_APB1_PRESCALER		RCC_HCLK_DIV1
#elif	RCC_APB1_PRESCALER_NUM == 2
	#define RCC_APB1_PRESCALER		RCC_HCLK_DIV2
#elif	RCC_APB1_PRESCALER_NUM == 4
	#define RCC_APB1_PRESCALER		RCC_HCLK_DIV4
#elif	RCC_APB1_PRESCALER_NUM == 8
	#define RCC_APB1_PRESCALER		RCC_HCLK_DIV8
#elif	RCC_APB1_PRESCALER_NUM == 16
	#define RCC_APB1_PRESCALER		RCC_HCLK_DIV16
#endif

#if		RCC_APB2_PRESCALER_NUM == 1
	#define RCC_APB2_PRESCALER		RCC_HCLK_DIV1
#elif	RCC_APB2_PRESCALER_NUM == 2
	#define RCC_APB2_PRESCALER		RCC_HCLK_DIV2
#elif	RCC_APB2_PRESCALER_NUM == 4
	#define RCC_APB2_PRESCALER		RCC_HCLK_DIV4
#elif	RCC_APB2_PRESCALER_NUM == 8
	#define RCC_APB2_PRESCALER		RCC_HCLK_DIV8
#elif	RCC_APB2_PRESCALER_NUM == 16
	#define RCC_APB2_PRESCALER		RCC_HCLK_DIV16
#endif

/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern RCC_OscInitTypeDef	OscInitStruct;
extern RCC_ClkInitTypeDef	ClkInitStruct;


#endif /* CONFIG_INC_RCC_CFG_H_ */
