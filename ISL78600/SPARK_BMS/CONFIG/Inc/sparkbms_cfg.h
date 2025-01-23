/*
 * @filename	sparkbms_cfg.h
 * @author		SPARKBMS TEAM
 * @date		Apr 17, 2023
 * @ingroup		FOLDER NAME
 * @prefix		sparkbms_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_SPARKBMS_CFG_H_
#define CONFIG_INC_SPARKBMS_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#if AFE_BQ76PL455 == 1

#define NO_OF_DAISY_STACK		1			// 1 : Master
#define NO_OF_CELLS_PER_STACK	16
#define NO_OF_TEMPS_PER_STACK	8

#define NO_OF_EXT_TEMPS			0

#define BMS_NO_OF_CELLS			(NO_OF_DAISY_STACK*NO_OF_CELLS_PER_STACK)
#define BMS_NO_OF_TEMPS			((NO_OF_DAISY_STACK*NO_OF_TEMPS_PER_STACK) + NO_OF_EXT_TEMPS)

#elif AFE_ISL78600 == 1

#define NO_OF_DAISY_STACK		8			// 1 : Master
#define NO_OF_CELLS_PER_STACK	16
#define NO_OF_TEMPS_PER_STACK	7

#define NO_OF_ADC_TEMPS			0
#define NO_OF_ISO_VOL           3

#define NO_OF_EXT_TEMPS			0

#define BMS_NO_OF_CELLS			124//(NO_OF_DAISY_STACK*NO_OF_CELLS_PER_STACK)
#define BMS_NO_OF_TEMPS			((NO_OF_DAISY_STACK*NO_OF_TEMPS_PER_STACK) + NO_OF_EXT_TEMPS + NO_OF_ADC_TEMPS)

#endif


#define BMS_AFE_COV				4.2

#define BMS_AFE_CUV				3.0


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/



#endif /* CONFIG_INC_SPARKBMS_CFG_H_ */
