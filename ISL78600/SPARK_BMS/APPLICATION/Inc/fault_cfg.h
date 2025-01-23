/*
 * @filename	fault_cfg.h
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		fault_cfg
 * 
 * @brief		Add the description
 */
#ifndef APPLICATION_INC_FAULT_CFG_H_
#define APPLICATION_INC_FAULT_CFG_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"
#include "database.h"

/*---------------------------------------Macros--------------------------------------------------------*/

/* Battery Pack Configuration */

extern uint8_t NO_OF_CELLS;
extern uint8_t NO_OF_TEMPS;

extern uint16_t VOLTAGE_SAMPLING;
extern uint16_t CURRENT_SAMPLING;
extern uint16_t TEMPERATURE_SAMPLING;
extern uint16_t SOC_SAMPLING;

/* Cell OverVoltage Configuration */

extern uint16_t COV_ROL;
extern uint16_t COV_MOL;
extern uint16_t COV_MSL;

extern uint16_t COV_ROL_DELAY;
extern uint16_t COV_MOL_DELAY;
extern uint16_t COV_MSL_DELAY;

extern uint16_t COV_ROL_R;
extern uint16_t COV_MOL_R;
extern uint16_t COV_MSL_R;

extern uint16_t COV_ROL_R_DELAY;
extern uint16_t COV_MOL_R_DELAY;
extern uint16_t COV_MSL_R_DELAY;

/* Cell UnderVoltage Configuration */

extern uint16_t CUV_ROL;
extern uint16_t CUV_MOL;
extern uint16_t CUV_MSL;

extern uint16_t CUV_ROL_DELAY;
extern uint16_t CUV_MOL_DELAY;
extern uint16_t CUV_MSL_DELAY;

extern uint16_t CUV_ROL_R;
extern uint16_t CUV_MOL_R;
extern uint16_t CUV_MSL_R;

extern uint16_t CUV_ROL_R_DELAY;
extern uint16_t CUV_MOL_R_DELAY;
extern uint16_t CUV_MSL_R_DELAY;

/* Pack OverVoltage Configuration */

extern uint32_t POV_ROL;
extern uint32_t POV_MOL;
extern uint32_t POV_MSL;

extern uint16_t POV_ROL_DELAY;
extern uint16_t POV_MOL_DELAY;
extern uint16_t POV_MSL_DELAY;

extern uint32_t POV_ROL_R;
extern uint32_t POV_MOL_R;
extern uint32_t POV_MSL_R;

extern uint16_t POV_ROL_R_DELAY;
extern uint16_t POV_MOL_R_DELAY;
extern uint16_t POV_MSL_R_DELAY;

/* Pack UnderVoltage Configuration */

extern uint32_t PUV_ROL;
extern uint32_t PUV_MOL;
extern uint32_t PUV_MSL;

extern uint16_t PUV_ROL_DELAY;
extern uint16_t PUV_MOL_DELAY;
extern uint16_t PUV_MSL_DELAY;

extern uint32_t PUV_ROL_R;
extern uint32_t PUV_MOL_R;
extern uint32_t PUV_MSL_R;

extern uint16_t PUV_ROL_R_DELAY;
extern uint16_t PUV_MOL_R_DELAY;
extern uint16_t PUV_MSL_R_DELAY;

/* Over Current Charge Configuration */

extern int32_t OCC_ROL;
extern int32_t OCC_MOL;
extern int32_t OCC_MSL;

extern uint16_t OCC_ROL_DELAY;
extern uint16_t OCC_MOL_DELAY;
extern uint16_t OCC_MSL_DELAY;

extern int32_t OCC_ROL_R;
extern int32_t OCC_MOL_R;
extern int32_t OCC_MSL_R;

extern uint16_t OCC_ROL_R_DELAY;
extern uint16_t OCC_MOL_R_DELAY;
extern uint16_t OCC_MSL_R_DELAY;

/* Over Current Discharge Configuration */

extern int32_t OCD_ROL;
extern int32_t OCD_MOL;
extern int32_t OCD_MSL;

extern uint16_t OCD_ROL_DELAY;
extern uint16_t OCD_MOL_DELAY;
extern uint16_t OCD_MSL_DELAY;

extern int32_t OCD_ROL_R;
extern int32_t OCD_MOL_R;
extern int32_t OCD_MSL_R;

extern uint16_t OCD_ROL_R_DELAY;
extern uint16_t OCD_MOL_R_DELAY;
extern uint16_t OCD_MSL_R_DELAY;

/* Over Temperature Charge Configuration */

extern int16_t OTC_ROL;
extern int16_t OTC_MOL;
extern int16_t OTC_MSL;

extern uint16_t OTC_ROL_DELAY;
extern uint16_t OTC_MOL_DELAY;
extern uint16_t OTC_MSL_DELAY;

extern int16_t OTC_ROL_R;
extern int16_t OTC_MOL_R;
extern int16_t OTC_MSL_R;

extern uint16_t OTC_ROL_R_DELAY;
extern uint16_t OTC_MOL_R_DELAY;
extern uint16_t OTC_MSL_R_DELAY;

/* Under Temperature Charge Configuration */

extern int16_t UTC_ROL;
extern int16_t UTC_MOL;
extern int16_t UTC_MSL;

extern uint16_t UTC_ROL_DELAY;
extern uint16_t UTC_MOL_DELAY;
extern uint16_t UTC_MSL_DELAY;

extern int16_t UTC_ROL_R;
extern int16_t UTC_MOL_R;
extern int16_t UTC_MSL_R;

extern uint16_t UTC_ROL_R_DELAY;
extern uint16_t UTC_MOL_R_DELAY;
extern uint16_t UTC_MSL_R_DELAY;

/* Over Temperature Discharge Configuration */

extern int16_t OTD_ROL;
extern int16_t OTD_MOL;
extern int16_t OTD_MSL;

extern uint16_t OTD_ROL_DELAY;
extern uint16_t OTD_MOL_DELAY;
extern uint16_t OTD_MSL_DELAY;

extern int16_t OTD_ROL_R;
extern int16_t OTD_MOL_R;
extern int16_t OTD_MSL_R;

extern uint16_t OTD_ROL_R_DELAY;
extern uint16_t OTD_MOL_R_DELAY;
extern uint16_t OTD_MSL_R_DELAY;

/* Under Temperature Discharge Configuration */

extern int16_t UTD_ROL;
extern int16_t UTD_MOL;
extern int16_t UTD_MSL;

extern uint16_t UTD_ROL_DELAY;
extern uint16_t UTD_MOL_DELAY;
extern uint16_t UTD_MSL_DELAY;

extern int16_t UTD_ROL_R;
extern int16_t UTD_MOL_R;
extern int16_t UTD_MSL_R;

extern uint16_t UTD_ROL_R_DELAY;
extern uint16_t UTD_MOL_R_DELAY;
extern uint16_t UTD_MSL_R_DELAY;

/* Short Circuit Configuration */

#define SC_MSL				200000			// mA

#define SC_MSL_DELAY		10000			// milli second

/* Passive Balancing Configuration */

extern uint16_t PB_BV;
extern uint16_t PB_BDIFFV;
extern int16_t PB_BC;
extern uint16_t PB_BSV;

/* Voltage Difference Configuration */

extern uint16_t CVD_ROL;
extern uint16_t CVD_MOL;
extern uint16_t CVD_MSL;

extern uint16_t CVD_ROL_DELAY;
extern uint16_t CVD_MOL_DELAY;
extern uint16_t CVD_MSL_DELAY;

extern uint16_t CVD_ROL_R;
extern uint16_t CVD_MOL_R;
extern uint16_t CVD_MSL_R;

extern uint16_t CVD_ROL_R_DELAY;
extern uint16_t CVD_MOL_R_DELAY;
extern uint16_t CVD_MSL_R_DELAY;

/* SOC High Configuration */

extern uint8_t SOCH_ROL;
extern uint8_t SOCH_MOL;

extern uint16_t SOCH_ROL_DELAY;
extern uint16_t SOCH_MOL_DELAY;

extern uint8_t SOCH_ROL_R;
extern uint8_t SOCH_MOL_R;

extern uint16_t SOCH_ROL_R_DELAY;
extern uint16_t SOCH_MOL_R_DELAY;

/* SOC Low Configuration */

extern uint8_t SOCL_ROL;
extern uint8_t SOCL_MOL;

extern uint16_t SOCL_ROL_DELAY;
extern uint16_t SOCL_MOL_DELAY;

extern uint8_t SOCL_ROL_R;
extern uint8_t SOCL_MOL_R;

extern uint16_t SOCL_ROL_R_DELAY;
extern uint16_t SOCL_MOL_R_DELAY;


/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void fault_CurrentConfig(void);

#endif /* APPLICATION_INC_FAULT_CFG_H_ */
