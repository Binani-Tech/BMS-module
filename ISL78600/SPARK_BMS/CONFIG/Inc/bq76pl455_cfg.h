/*
 * @filename	bq76pl455_cfg.h
 * @author		SPARKBMS TEAM
 * @date		21-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		bq76pl455_cfg
 * 
 * @brief		Add the description
 */
#ifndef CONFIG_INC_BQ76PL455_CFG_H_
#define CONFIG_INC_BQ76PL455_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "sparkbms_cfg.h"
#include "afe.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define BQ_ADDR		0x00

/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

extern void BQ_AFE_Config(void);
extern void BQ_AFE_OV_Config(void);
extern void BQ_AFE_UV_Config(void);
extern void BQ_AFE_ClearAllFault(void);
extern void BQ_AFE_AddressAll(void);

#endif /* CONFIG_INC_BQ76PL455_CFG_H_ */
