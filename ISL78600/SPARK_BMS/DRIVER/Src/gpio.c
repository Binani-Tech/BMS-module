/*
 * @filename	gpio.c
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		gpio
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "gpio.h"

/*-------------------------------------------Macros----------------------------------------------------*/

#define GPIO_GET_GPIOx(_N) ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))

#define NULL_PTR (void*)(0)
/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/

static void GPIO_Clock_Enable(void);

/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void GPIO_Init(const GPIO_InitTypeDef *gpio_cfg)
{
	if(gpio_cfg == NULL_PTR)
	{
		while(1);
	}

	GPIO_Clock_Enable();

	GPIO_InitTypeDef	GPIO_InitStruct;

	for(uint8_t i = 0; i < gpio_cfg_length; i++)
	{
		GPIO_InitStruct.Pin = (uint16_t)(1 << ((gpio_cfg[i].Pin) % NO_OF_PINS_PER_PORT));
		GPIO_InitStruct.Pull = gpio_cfg[i].Pull;
		GPIO_InitStruct.Speed = gpio_cfg[i].Speed;
		GPIO_InitStruct.Mode = gpio_cfg[i].Mode;

		if(gpio_cfg[i].Alternate != GPIO_NO_ALTERNATIVE)
		{
			GPIO_InitStruct.Alternate = gpio_cfg[i].Alternate;
		}

		HAL_GPIO_Init(GPIO_GET_GPIOx((gpio_cfg[i].Pin) / NO_OF_PINS_PER_PORT), &GPIO_InitStruct);
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void BOOT0_Init(void)
{
	GPIO_InitTypeDef	gpio_boot;

	__HAL_RCC_GPIOH_CLK_ENABLE();

	gpio_boot.Pin = GPIO_PIN_BOOT0;
	gpio_boot.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_boot.Pull = GPIO_NOPULL;
	gpio_boot.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIO_PORT_BOOT0, &gpio_boot);

	HAL_GPIO_WritePin(GPIO_PORT_BOOT0, GPIO_PIN_BOOT0, GPIO_PIN_RESET);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

static void GPIO_Clock_Enable(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

#if (AFE_ISL78600 == 1)
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
#endif

}

/*
 * @brief
 * @arguments
 * @retvar
 */

uint8_t GPIO_ReadPin(GPIO_PINs pin)
{
	uint8_t value;
	uint16_t readpin = (uint16_t)(1 << (pin % NO_OF_PINS_PER_PORT));
	value = HAL_GPIO_ReadPin(GPIO_GET_GPIOx(pin/NO_OF_PINS_PER_PORT), readpin);
	return value;
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void GPIO_WritePin(GPIO_PINs pin, uint8_t value)
{
	uint16_t writepin = (uint16_t)(1 << (pin % NO_OF_PINS_PER_PORT));
	HAL_GPIO_WritePin(GPIO_GET_GPIOx(pin/NO_OF_PINS_PER_PORT), writepin, value);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

void GPIO_TogglePin(GPIO_PINs pin)
{
	uint16_t togglepin = (uint16_t)(1 << (pin % NO_OF_PINS_PER_PORT));
	HAL_GPIO_TogglePin(GPIO_GET_GPIOx(pin/NO_OF_PINS_PER_PORT), togglepin);
}
