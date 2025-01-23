/*
 * @filename	uart_cfg.c
 * @author		SPARKBMS TEAM
 * @date		13-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		uart_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "uart_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

UART_HandleTypeDef uart_cfg[] = {
		{
				.Instance = USART3,
				.Init.BaudRate = 250000,
				.Init.HwFlowCtl = UART_HWCONTROL_NONE,
				.Init.Mode = UART_MODE_TX_RX,
				.Init.OverSampling = UART_OVERSAMPLING_16,
				.Init.Parity = UART_PARITY_NONE,
				.Init.StopBits = UART_STOPBITS_1,
				.Init.WordLength = UART_WORDLENGTH_8B,
				.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
		},
		{
				.Instance = USART1,
				.Init.BaudRate = 115200,
				.Init.HwFlowCtl = UART_HWCONTROL_NONE,
				.Init.Mode = UART_MODE_TX_RX,
				.Init.OverSampling = UART_OVERSAMPLING_16,
				.Init.Parity = UART_PARITY_NONE,
				.Init.StopBits = UART_STOPBITS_1,
				.Init.WordLength = UART_WORDLENGTH_8B,
				.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
		},
		{
				.Instance = USART2,
				.Init.BaudRate = 115200,
				.Init.HwFlowCtl = UART_HWCONTROL_NONE,
				.Init.Mode = UART_MODE_TX_RX,
				.Init.OverSampling = UART_OVERSAMPLING_16,
				.Init.Parity = UART_PARITY_NONE,
				.Init.StopBits = UART_STOPBITS_1,
				.Init.WordLength = UART_WORDLENGTH_8B,
				.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
		},
};

uint8_t uart_cfg_length = sizeof(uart_cfg)/sizeof(uart_cfg[0]);

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */
