/*
 * @filename	crc.h
 * @author		SPARKBMS TEAM
 * @date		14-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		crc
 * 
 * @brief		Add the description
 */
#ifndef MODULES_INC_CRC_H_
#define MODULES_INC_CRC_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

uint16_t CRC16_Calc(uint8_t *Buffer, uint8_t length);

#endif /* MODULES_INC_CRC_H_ */
