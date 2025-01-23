/*
 * @filename	stm32l4xx_hal_msp.c
 * @author		SPARKBMS TEAM
 * @date		May 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		stm32l4xx_hal_msp
 *
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "mcu_cfg.h"
#include "dma_cfg.h"
#include "adc_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_MspInit(void)
{
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI2)
	{
		__HAL_RCC_SPI2_CLK_ENABLE();
	}

	if(hspi->Instance == SPI3)
	{
		__HAL_RCC_SPI3_CLK_ENABLE();
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_RTC_ENABLE();
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		__HAL_RCC_TIM6_CLK_ENABLE();
	}
	else if(htim->Instance == TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();
	}
	else if(htim->Instance == TIM7)
	{
		__HAL_RCC_TIM7_CLK_ENABLE();
	}
	else if(htim->Instance == TIM15)
	{
		__HAL_RCC_TIM15_CLK_ENABLE();
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		__HAL_RCC_USART1_CLK_ENABLE();
	}
	else if(huart->Instance == USART2)
	{
		__HAL_RCC_USART2_CLK_ENABLE();
	}
	else if(huart->Instance == USART3)
	{
		__HAL_RCC_USART3_CLK_ENABLE();
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
		__HAL_RCC_CAN1_CLK_ENABLE();
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_I2C_MspInit(I2C_HandleTypeDef	*hi2c)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	if(hi2c->Instance == I2C1)
	{
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
		PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

    	__HAL_RCC_I2C1_CLK_ENABLE();
    }
    else if(hi2c->Instance == I2C2)
    {
    	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C2;
    	PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
    	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    	{
    		Error_Handler();
    	}

    	__HAL_RCC_I2C2_CLK_ENABLE();
    }
    else if(hi2c->Instance == I2C3)
    {
    	__HAL_RCC_I2C3_CLK_ENABLE();
    }
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance == ADC1)
	{
		__HAL_RCC_ADC_CLK_ENABLE();
#if	ADC_DMA_ENABLE == 1
		__HAL_LINKDMA(hadc,DMA_Handle,dma_cfg[0]);
#endif
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void HAL_WWDG_MspInit(WWDG_HandleTypeDef* hwwdg)
{
  if(hwwdg->Instance==WWDG)
  {
    /* Peripheral clock enable */
    __HAL_RCC_WWDG_CLK_ENABLE();
  }

}
