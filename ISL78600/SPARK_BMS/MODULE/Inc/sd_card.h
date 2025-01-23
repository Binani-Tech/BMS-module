/*
 * @filename	sd_card.h
 * @author		SPARKBMS TEAM
 * @date		10-Jul-2023
 * @ingroup		FOLDER NAME
 * @prefix		sd_card
 * 
 * @brief		Add the description
 */
#ifndef MODULES_INC_SD_CARD_H_
#define MODULES_INC_SD_CARD_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "fatfs.h"
#include "fatfs_sd.h"
#include "mcu_cfg.h"
#include "database.h"
#include "gpio.h"
#include "timer.h"
#include "stdio.h"

/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t SDCard_Init;

/*---------------------------------------Function Prototypes-------------------------------------------*/

void SD_Init(void);
uint8_t SD_CheckMount(void);
uint32_t SD_CheckFreeSpace(void);
uint32_t SD_CheckTotalSpace(void);
void SD_ClearBuffer(char *buffer);
void SD_Write(void);

#endif /* MODULES_INC_SD_CARD_H_ */
