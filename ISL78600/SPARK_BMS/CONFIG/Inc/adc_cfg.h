/*
 * @filename	adc_cfg.h
 * @author		SPARKBMS TEAM
 * @date		Apr 14, 2023
 * @ingroup		FOLDER NAME
 * @prefix		adc_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_ADC_CFG_H_
#define CONFIG_INC_ADC_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define ADC_NO_OF_CONVERSION		11

#define ADC_DMA_ENABLE				1

/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern ADC_HandleTypeDef		adc_cfg;
extern ADC_ChannelConfTypeDef	adc_channel_cfg[];

extern uint8_t adc_channel_cfg_length;

#endif /* CONFIG_INC_ADC_CFG_H_ */
