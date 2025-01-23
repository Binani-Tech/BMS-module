/*
 * @filename	nvic_cfg.h
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		nvic_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_NVIC_CFG_H_
#define CONFIG_INC_NVIC_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

typedef enum
{
	NVIC_DISABLE = 0,
	NVIC_ENABLE = 1
}NVIC_State;


typedef struct
{
	IRQn_Type  	IRQ_No;
	uint8_t 	priority;
	uint8_t 	subpriority;
	NVIC_State 	state;
}NVIC_InitStruct;

/*---------------------------------------Function Prototypes-------------------------------------------*/

extern NVIC_InitStruct nvic_cfg[];
extern uint8_t nvic_cfg_length;

#endif /* CONFIG_INC_NVIC_CFG_H_ */
