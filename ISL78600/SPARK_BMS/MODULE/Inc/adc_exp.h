/*
 * @filename	adc_exp.h
 * @author		SPARKBMS TEAM
 * @date		01-Jun-2023
 * @ingroup		FOLDER NAME
 * @prefix		adc_exp
 * 
 * @brief		Add the description
 */
#ifndef MODULE_INC_ADC_EXP_H_
#define MODULE_INC_ADC_EXP_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "i2c.h"
#include "sparkbms_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void ADC_EXP_Init(void);

void ADC_EXP_Temperatures(int16_t *temperature);

#endif /* MODULE_INC_ADC_EXP_H_ */
