/*
 * @filename	can.h
 * @author		SPARKBMS TEAM
 * @date		04-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		can
 * 
 * @brief		Add the description
 */
#ifndef DRIVERS_INC_CAN_H_
#define DRIVERS_INC_CAN_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "can_cfg.h"
#include "gpio.h"
#include "fault_manager.h"
#include "fault_monitor.h"
#include "database.h"

/*---------------------------------------Macros--------------------------------------------------------*/
#define VOLTAGE_CHANNELS      BMS_NO_OF_CELLS/4
#define TEMP_CHANNELS         BMS_NO_OF_TEMPS/4
#define BAL_SUMMARY_CHANNELS  BMS_NO_OF_CELLS/8
//#define CAN_BASE_ID            0X19090301
/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t CAN_Request;
extern bool Req_MainSeq;
extern bool Req_SlowChrSeq;
extern bool Req_FastChrSeq;
extern bool Req_HVACSeq;

typedef enum
{
	CAN_BASE_ID                 = 0X19090300,

	CAN_FAULTS_1 				= 0X19090301,
	CAN_FAULTS_2 				= 0X19090302,
	CAN_WARNING_1 				= 0X19090303,
	CAN_WARNING_2 				= 0X19090304,
	CAN_CONTACTOR_STATUS 		= 0X19090305,
	CAN_BATTERY_SUMMARY			= 0X19090306,
	CAN_MIN_MAX_VOLTAGE			= 0X19090307,
	CAN_MIN_MAX_TEMP			= 0X19090308,
	CAN_PACK_SUMMARY_VOLTAGE	= 0X19090309,
	CAN_PACK_SUMMARY_CURRENT	= 0X1909030A,
	CAN_PACK_SUMMARY_SOX        = 0X1909030B,

	CAN_MASTER_PACK             = 0X19090312,

	CAN_SLAVE_1	     			= 0X19090316,
	CAN_SLAVE_2				    = 0X19090320,
	CAN_SLAVE_3				    = 0X19090324,
	CAN_SLAVE_4				    = 0X19090328,
	CAN_SLAVE_5	     			= 0X19090332,
	CAN_SLAVE_6				    = 0X19090336,
	CAN_SLAVE_7				    = 0X19090340,
	CAN_SLAVE_8				    = 0X19090344,
	CAN_SLAVE_9				    = 0X19090348,
	CAN_SLAVE_10 			    = 0X19090352,
	CAN_SLAVE_11			    = 0X19090356,

	CAN_MASTER_TEMPERATURES		= 0X19090360,

	CAN_SLAVE_TEMPERATURES_1	= 0X19090362,
	CAN_SLAVE_TEMPERATURES_2	= 0X19090364,
	CAN_SLAVE_TEMPERATURES_3	= 0X19090366,
	CAN_SLAVE_TEMPERATURES_4	= 0X19090368,
	CAN_SLAVE_TEMPERATURES_5	= 0X19090370,
	CAN_SLAVE_TEMPERATURES_6	= 0X19090372,
	CAN_SLAVE_TEMPERATURES_7	= 0X19090374,
	CAN_SLAVE_TEMPERATURES_8	= 0X19090376,
	CAN_SLAVE_TEMPERATURES_9	= 0X19090378,
	CAN_SLAVE_TEMPERATURES_10	= 0X19090380,
	CAN_SLAVE_TEMPERATURES_11	= 0X19090382,

	CAN_MASTER_BALANCING_STATE	= 0X19090384,

//	CAN_SLAVE_BALANCING_STATE_1	= 0X19090386,
//	CAN_SLAVE_BALANCING_STATE_2	= 0X19090388,
//	CAN_SLAVE_BALANCING_STATE_3	= 0X19090390,
//	CAN_SLAVE_BALANCING_STATE_4	= 0X19090392,
//	CAN_SLAVE_BALANCING_STATE_5	= 0X19090394,
//	CAN_SLAVE_BALANCING_STATE_6	= 0X19090396,
//	CAN_SLAVE_BALANCING_STATE_7	= 0X19090398,
//	CAN_SLAVE_BALANCING_STATE_8	= 0X19090400,
//	CAN_SLAVE_BALANCING_STATE_9	= 0X19090402,
//	CAN_SLAVE_BALANCING_STATE_10= 0X19090404,
//	CAN_SLAVE_BALANCING_STATE_11= 0X19090406,

	CAN_MODULE_VOLTAGE          = 0X19090407,

	MAIN_CONT_SEQ               = 0X19090402,
	SLOW_CHR_SEQ                = 0X19090403,
	FAST_CHR_SEQ                = 0X19090404,
	HVAC_ENABLE                 = 0X19090405,

	CAN_AFE_INIT                = 0X19090406,

	CAN_ALL_MSSG				= 0X19090500,

	CAN_BMS_CHG_MSG				= 0X1806E5F4,
	CAN_CHR_BIT 				= 0X19090406,

	CAN_CHG_BMS_MSG				= 0X18FF50E5,
}CAN_MSSG_e;

extern bool read_flag;
/*---------------------------------------Function Prototypes-------------------------------------------*/

void CAN1_Init(void);

void CAN1_FilterConfig(void);

void CAN1_Rx(void);

void CAN_MAIN_SEQ(void);
void CAN_MAIN_SEQ_CPL(void);
void CAN_SLOW_CHR_SEQ(void);
void CAN_SLOW_CHR_SEQ_CPL(void);
void CAN_FAST_CHR_SEQ(void);
void CAN_FAST_CHR_SEQ_CPL(void);
void CAN_HVAC_ENABLE(void);
void CAN_HVAC_SEQ_CPL(void);

void CAN_Send_Fault_1(void);
void CAN_Send_Fault_2(void);
void CAN_Send_Warning_1(void);
void CAN_Send_Warning_2(void);
void CAN_Send_Cont_Status(void);
void CAN_Send_Summary(void);
void CAN_Send_MinMax_VOLTAGE(void);
void CAN_Send_MinMax_TEMP(void);
void CAN_Send_PackSummary_VOLTAGE(void);
void CAN_Send_PackSummary_CURRENT(void);
void CAN_Send_PackSummary_SOX(void);

void CAN_Send_MASTER_PACK(void);
void CAN_Send_Slave_PACK(void);
void CAN_Send_ALL_Voltage(void);

void CAN_Send_MASTER_TEMP(void);
void CAN_Send_SLAVE_TEMP(void);
void CAN_Send_ALL_Temp(void);

void CAN_Send_BalancingSummary(void);
void CAN_Send_ALL_BalancingSummary(void);

void CAN_Send_MODULE_VOLTAGE(void);
void CAN_Send_Module_TEMP(void);

void CAN_SendAll(void);

void CAN_Send_CHG_MSG(void);
void CAN_CHR_BIT_SET(void);
void CAN_Rev_CHG_MSG(void);

void Unsigned_Data16toData8(uint8_t *Data8, uint16_t *Data16, uint8_t Data16_Len);
void Data16toData8(uint8_t *Data8, int16_t *Data16, uint8_t Data16_Len);

#endif /* DRIVERS_INC_CAN_H_ */
