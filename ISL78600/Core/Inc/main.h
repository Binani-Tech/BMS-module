/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_OUT_Pin GPIO_PIN_13
#define BUZZER_OUT_GPIO_Port GPIOC
#define ONBOARD_TEMP_Pin GPIO_PIN_0
#define ONBOARD_TEMP_GPIO_Port GPIOC
#define CURRENT_ADC_Pin GPIO_PIN_1
#define CURRENT_ADC_GPIO_Port GPIOC
#define EEPROM_I2C2_SCL_Pin GPIO_PIN_10
#define EEPROM_I2C2_SCL_GPIO_Port GPIOB
#define EEPROM_I2C2_SDA_Pin GPIO_PIN_11
#define EEPROM_I2C2_SDA_GPIO_Port GPIOB
#define AFE_SPI2_CS_Pin GPIO_PIN_12
#define AFE_SPI2_CS_GPIO_Port GPIOB
#define AFE_SPI2_SCK_Pin GPIO_PIN_13
#define AFE_SPI2_SCK_GPIO_Port GPIOB
#define AFE_SPI2_MISO_Pin GPIO_PIN_14
#define AFE_SPI2_MISO_GPIO_Port GPIOB
#define AFE_SPI2_MOSI_Pin GPIO_PIN_15
#define AFE_SPI2_MOSI_GPIO_Port GPIOB
#define AFE_DATAREADY_Pin GPIO_PIN_6
#define AFE_DATAREADY_GPIO_Port GPIOC
#define AFE_FAULTPIN_Pin GPIO_PIN_7
#define AFE_FAULTPIN_GPIO_Port GPIOC
#define CHG_CONT_EN_Pin GPIO_PIN_8
#define CHG_CONT_EN_GPIO_Port GPIOC
#define PCHG_CONT_EN_Pin GPIO_PIN_9
#define PCHG_CONT_EN_GPIO_Port GPIOC
#define DCHG_CONT_EN_Pin GPIO_PIN_8
#define DCHG_CONT_EN_GPIO_Port GPIOA
#define BLE_UART1_TX_Pin GPIO_PIN_9
#define BLE_UART1_TX_GPIO_Port GPIOA
#define BLE_UART1_RX_Pin GPIO_PIN_10
#define BLE_UART1_RX_GPIO_Port GPIOA
#define DCDC_CONT_EN_Pin GPIO_PIN_11
#define DCDC_CONT_EN_GPIO_Port GPIOA
#define THERM_CONT_EN_Pin GPIO_PIN_12
#define THERM_CONT_EN_GPIO_Port GPIOA
#define EXT_CONT_EN_Pin GPIO_PIN_15
#define EXT_CONT_EN_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOD
#define ADCEXP_RTC_I2C1_SCL_Pin GPIO_PIN_6
#define ADCEXP_RTC_I2C1_SCL_GPIO_Port GPIOB
#define ADCEXP_RTC_I2C1_SDA_Pin GPIO_PIN_7
#define ADCEXP_RTC_I2C1_SDA_GPIO_Port GPIOB
#define BOOT_PIN_Pin GPIO_PIN_3
#define BOOT_PIN_GPIO_Port GPIOH

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
