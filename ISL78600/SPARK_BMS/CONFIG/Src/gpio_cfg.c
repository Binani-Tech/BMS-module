/*
 * @filename	gpio_cfg.c
 * @author		SPARKBMS TEAM
 * @date		13-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		gpio_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "gpio_cfg.h"
#include "mcu_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */


GPIO_InitTypeDef gpio_cfg[] = {

#if (AFE_BQ76PL455 == 1)
		{.Pin = GPIO_PIN_LED1, 							.Mode = GPIO_MODE_OUTPUT_PP, 			.Alternate = GPIO_NO_ALTERNATIVE ,		.Pull = GPIO_NOPULL, 		.Speed = GPIO_SPEED_FREQ_VERY_HIGH		},
		{.Pin = GPIO_PIN_LED2, 							.Mode = GPIO_MODE_OUTPUT_PP, 			.Alternate = GPIO_NO_ALTERNATIVE , 		.Pull = GPIO_NOPULL, 		.Speed = GPIO_SPEED_FREQ_VERY_HIGH		},
		{.Pin = GPIO_PIN_LED3, 							.Mode = GPIO_MODE_OUTPUT_PP, 			.Alternate = GPIO_NO_ALTERNATIVE ,		.Pull = GPIO_NOPULL, 		.Speed = GPIO_SPEED_FREQ_VERY_HIGH		},
		{.Pin = GPIO_PIN_LED4, 							.Mode = GPIO_MODE_OUTPUT_PP, 			.Alternate = GPIO_NO_ALTERNATIVE ,		.Pull = GPIO_NOPULL, 		.Speed = GPIO_SPEED_FREQ_VERY_HIGH		},

		{.Pin = GPIO_PIN_BMS_INTERFACE_UART2_TX,		.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART2,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BMS_INTERFACE_UART2_RX,		.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART2,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BMS_WAKEUP_PIN,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_PULLDOWN,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BMS_FAULT_PIN,					.Mode = GPIO_MODE_IT_FALLING,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_PULLUP,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_CURRENT_SENSOR,				.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_PCB_TEMP_SENSOR,				.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_GPO1,							.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_GPO2,							.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_CHG_CONTACTOR,					.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_DCHG_CONTACTOR,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_PCHG_CONTACTOR,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},

		{.Pin = GPIO_PIN_EEPROM_I2C2_SCL,				.Mode = GPIO_MODE_AF_OD,				.Alternate = GPIO_AF4_I2C2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_EEPROM_I2C2_SDA,				.Mode = GPIO_MODE_AF_OD,				.Alternate = GPIO_AF4_I2C2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_USER_INTERFACE_UART1_RX,		.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART1,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_HIGH		},
		{.Pin = GPIO_PIN_USER_INTERFACE_UART1_TX,		.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART1,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_HIGH		},

		{.Pin = GPIO_PIN_CAN1_TX,						.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF9_CAN1,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_CAN1_RX,						.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF9_CAN1,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_CAN1_STB,						.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_MEDIUM		}

#endif

#if (AFE_ISL78600 == 1)

		{.Pin = GPIO_PIN_LED,							.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_FAULT_LED,						.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BUZZER,						.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_HIGH		},

		{.Pin = GPIO_PIN_AFE_SPI2_MOSI,					.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF5_SPI2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_AFE_SPI2_MISO,					.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF5_SPI2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_AFE_SPI2_SCLK,					.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF5_SPI2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_AFE_SPI2_CS,					.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_PULLUP,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_AFE_SPI2_DATAREADY,			.Mode = GPIO_MODE_INPUT,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_AFE_SPI2_FAULTPIN,				.Mode = GPIO_MODE_INPUT,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_BMS_INTERFACE_UART3_TX,		.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART3,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BMS_INTERFACE_UART3_RX,		.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART3,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BMS_WAKEUP_PIN,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_PULLDOWN,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BMS_FAULT_PIN,					.Mode = GPIO_MODE_IT_FALLING,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_PULLUP,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_AFE_UART_EN,					.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_PULLUP,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_SPI3_MOSI,					    .Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF6_SPI3,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_SPI3_MISO,					    .Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF6_SPI3,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_SPI3_SCLK,					    .Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF6_SPI3,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_SPI3_CS,					    .Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_AF6_SPI3,		        .Pull = GPIO_PULLUP,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_CAN1_RX,						.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF9_CAN1,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_CAN1_TX,						.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF9_CAN1,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_BLE_UART1_RX,					.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART1,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_BLE_UART1_TX,					.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART1,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_RS_UART2_RX,			    	.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART2,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_RS_UART2_TX,				    .Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF7_USART2,			.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_ADC_RTC_I2C1_SCL,				.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF4_I2C1,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC_RTC_I2C1_SDA,				.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF4_I2C1,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

//		{.Pin = GPIO_PIN_EEPROM_I2C2_SCL,				.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF4_I2C2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_EEPROM_I2C2_SDA,				.Mode = GPIO_MODE_AF_PP,				.Alternate = GPIO_AF4_I2C2,				.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_HS_CONTACTOR,					.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_LS_CONTACTOR,				    .Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_PCHG_CONTACTOR,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_THERM_CONTACTOR,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_DCDC_CONTACTOR,				.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},
		{.Pin = GPIO_PIN_EXT_CONTACTOR,					.Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},

//		{.Pin = GPIO_PIN_ADC1_CURRENT,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_CURRENT_H,				.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_CURRENT_L,				.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_ADC1_PCBTEMP,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_TEMP5,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_TEMP6,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP7,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP8,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP9,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP10,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP11,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP12,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP13,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP14,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP15,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_ADC1_TEMP16,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_HVADC1,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_HVADC2,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
		{.Pin = GPIO_PIN_ADC1_HVADC3,					.Mode = GPIO_MODE_ANALOG,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

		{.Pin = GPIO_PIN_KEYON1_EN,				        .Mode = GPIO_MODE_INPUT,                 .Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_KEYON2_EN,			        	.Mode = GPIO_MODE_INPUT,	             .Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},

//		{.Pin = GPIO_PIN_IN,			        	    .Mode = GPIO_MODE_INPUT,				.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_VERY_HIGH	},
//		{.Pin = GPIO_PIN_OUT,					        .Mode = GPIO_MODE_OUTPUT_PP,			.Alternate = GPIO_NO_ALTERNATIVE,		.Pull = GPIO_NOPULL,		.Speed = GPIO_SPEED_FREQ_LOW		},


#endif

};

uint8_t gpio_cfg_length = sizeof(gpio_cfg)/sizeof(gpio_cfg[0]);
