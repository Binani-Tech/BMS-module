/*
 * @filename	nvic_cfg.c
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		nvic_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "nvic_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

NVIC_InitStruct nvic_cfg[] = {

//		{EXTI4_IRQn,			1,	0,	NVIC_ENABLE},     /*  AFE FAULT PIN Interrupt  */
		{WWDG_IRQn,              0, 0,  NVIC_ENABLE},
		{DMA1_Channel1_IRQn,	5,	0,	NVIC_ENABLE},		/*	ADC DMA Channel Interrupt	*/
		{SysTick_IRQn,			0,	0,  NVIC_ENABLE},		/* Systick Interrupt */
		{CAN1_RX0_IRQn,			15,	0,	NVIC_ENABLE},
		{CAN1_TX_IRQn,			15,	0,	NVIC_ENABLE},
		{USART1_IRQn,			15,	0,	NVIC_ENABLE},
//		{TIM1_BRK_TIM15_IRQn,    0, 0,  NVIC_ENABLE},
		{TIM7_IRQn,              0, 1,  NVIC_ENABLE},

};

uint8_t nvic_cfg_length = sizeof(nvic_cfg)/sizeof(nvic_cfg[0]);
