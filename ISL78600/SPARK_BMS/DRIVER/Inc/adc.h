/*
 * @filename	adc.h
 * @author		SPARKBMS TEAM
 * @date		Apr 14, 2023
 * @ingroup		FOLDER NAME
 * @prefix		adc
 * 
 * @brief		Add the description
 */
#ifndef DRIVERS_INC_ADC_H_
#define DRIVERS_INC_ADC_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "adc_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

extern uint16_t rawADC[ADC_NO_OF_CONVERSION];

/*---------------------------------------Function Prototypes-------------------------------------------*/

void ADC_Init(void);


#endif /* DRIVERS_INC_ADC_H_ */
