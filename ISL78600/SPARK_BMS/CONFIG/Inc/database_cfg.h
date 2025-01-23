/*
 * @filename	database_cfg.h
 * @author		SPARKBMS TEAM
 * @date		Apr 18, 2023
 * @ingroup		FOLDER NAME
 * @prefix		database_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "mcu_cfg.h"
#include "sparkbms_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/

#define CONT_OPEN	0
#define CONT_CLOSE	1

#define BAL_ON		1
#define BAL_OFF		0

#define FAULT		1
#define NO_FAULT	0

#define TOTAL_ERRORS	14
/*-------------------------------------------Variables-------------------------------------------------*/

typedef enum
{
	AFE_SHUTDOWN = 0,
	AFE_IDLE	 = 1,
	AFE_ACTIVE	 = 2,
}AFE_STATE_e;

typedef enum
{
	BMS_IDLE = 0,
	BMS_STANDBY,
	BMS_CHARGE,
	BMS_DISCHARGE,
	BMS_ERROR,
}BMS_STATE_e;

typedef enum
{
	CONT_STANDBY = 0,
	CONT_NORMAL,
	CONT_ERROR,
}CONTACTOR_STATE_e;

typedef struct
{
	uint8_t ERROR_VOLTAGE;
	uint8_t ERROR_CURRENT;
	uint8_t ERROR_TEMPERATURE;
}DATABASE_ERROR_SOURCE_s;

typedef enum
{
	BMS_NO_ERR = 0,
	BMS_CELL_OVER_VOLTAGE,
	BMS_CELL_UNDER_VOLTAGE,
	BMS_PACK_OVER_VOLTAGE,
	BMS_PACK_UNDER_VOLTAGE,
	BMS_CHARGE_OVER_CURRENT,
	BMS_DISCHARGE_OVER_CURRENT,
	BMS_CHARGE_OVER_TEMPERATURE,
	BMS_CHARGE_UNDER_TEMPERATURE,
	BMS_DISCHARGE_OVER_TEMPERATURE,
	BMS_DISCHARGE_UNDER_TEMPERATURE,
	BMS_VOLTAGE_DIFFERENCE,
	BMS_SOC_HIGH,
	BMS_SOC_LOW,
	BMS_SHORT_CIRCUIT
}BMS_ERROR_e;

typedef enum
{
	AFE_NO_ERR = 0,
	AFE_UV_FAULT_SUM,
	AFE_OV_FAULT_SUM,
	AFE_AUXUV_FAULT_SUM,
	AFE_AUXOV_FAULT_SUM,
	AFE_CMPUV_FAULT_SUM,
	AFE_CMPOV_FAULT_SUM,
	AFE_COMM_FAULT_SUM,
	AFE_SYS_FAULT_SUM,
	AFE_CHIP_FAULT_SUM,
	AFE_GPI_FAULT_SUM
}AFE_ERROR_e;

typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t day;
	uint8_t month;
	uint8_t year;
}DATABASE_TIMESTAMP_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	uint8_t CONT_MAIN_PLUS;
	uint8_t CONT_MAIN_MINUS;
	uint8_t CONT_PRECHARGE;
	uint8_t CONT_DCDC;
	uint8_t CONT_THERM;
	uint8_t CONT_EXT;
}DATABASE_CONTACTOR_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	AFE_STATE_e			afe_state;
	BMS_STATE_e			bms_state;
	CONTACTOR_STATE_e	cont_state;
	AFE_ERROR_e			afe_error;
	BMS_ERROR_e			bms_error;
	DATABASE_ERROR_SOURCE_s  bms_error_source;
	bool balancing_status;
}DATABASE_BMS_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	uint16_t cell_voltage[BMS_NO_OF_CELLS];
//	uint16_t iso_pack_voltage[NO_OF_ISO_VOL];
	uint8_t cell_balancing_status[BMS_NO_OF_CELLS];
	uint32_t module_voltage[NO_OF_DAISY_STACK];
	uint16_t max_voltage;
	uint16_t min_voltage;
	uint16_t avg_voltage;
	uint16_t diff_voltage;
	uint32_t sum_voltage;
	uint32_t module_max_voltage;
	uint32_t module_min_voltage;
	uint8_t module_max_voltage_index;
	uint8_t module_min_voltage_index;
	uint32_t module_diff_voltage;
	uint32_t r_power;
	uint32_t S1_voltage;
	uint32_t S2_voltage;
	uint8_t max_voltage_index;
	uint8_t min_voltage_index;
}DATABASE_VOLTAGE_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	int16_t pack_temperature[BMS_NO_OF_TEMPS];
	int16_t pcb_temperature;
	int16_t max_temperature;
	int16_t min_temperature;
	int16_t avg_temperature;
	uint8_t max_temperature_index;
	uint8_t min_temperature_index;
}DATABASE_TEMPERATURE_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	int32_t	pack_current;
	float power;				// W
	float current_counter;		// mAh
	float cycle_counter;		// mAh
	float energy_counter;		// Wh
}DATABASE_CURRENT_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	uint8_t soc;
	uint8_t max_soc;
	uint8_t min_soc;
	uint16_t cycle;
}DATABASE_SOC_s;

typedef struct
{
	uint8_t cell_over_voltage;
	uint8_t cell_under_voltage;
	uint8_t pack_over_voltage;
	uint8_t pack_under_voltage;
	uint8_t charge_over_current;
	uint8_t discharge_over_current;
	uint8_t charge_over_temperature;
	uint8_t charge_under_temperature;
	uint8_t discharge_over_temperature;
	uint8_t discharge_under_temperature;
	uint8_t voltage_difference;
	uint8_t soc_high;
	uint8_t soc_low;
}DATABASE_ERRORFLAG_ROL_s;

typedef struct
{
	uint8_t cell_over_voltage;
	uint8_t cell_under_voltage;
	uint8_t pack_over_voltage;
	uint8_t pack_under_voltage;
	uint8_t charge_over_current;
	uint8_t discharge_over_current;
	uint8_t charge_over_temperature;
	uint8_t charge_under_temperature;
	uint8_t discharge_over_temperature;
	uint8_t discharge_under_temperature;
	uint8_t voltage_difference;
	uint8_t soc_high;
	uint8_t soc_low;
	uint8_t short_circuit;
}DATABASE_ERRORFLAG_MOL_s;

typedef struct
{
	uint8_t cell_over_voltage;
	uint8_t cell_under_voltage;
	uint8_t pack_over_voltage;
	uint8_t pack_under_voltage;
	uint8_t charge_over_current;
	uint8_t discharge_over_current;
	uint8_t charge_over_temperature;
	uint8_t charge_under_temperature;
	uint8_t discharge_over_temperature;
	uint8_t discharge_under_temperature;
	uint8_t voltage_difference;
	uint8_t soc_high;
	uint8_t soc_low;
}DATABASE_ERRORFLAG_MSL_s;

typedef struct
{
	uint8_t cov_counter;
	uint8_t cuv_counter;
	uint8_t pov_counter;
	uint8_t puv_counter;
	uint16_t occ_counter;
	uint16_t ocd_counter;
	uint8_t otc_counter;
	uint8_t utc_counter;
	uint8_t otd_counter;
	uint8_t utd_counter;
	uint8_t cvd_counter;
	uint8_t soch_counter;
	uint8_t socl_counter;
}DATABASE_ERROR_COUNTER_s;

typedef struct
{
	uint8_t cov_release_counter;
	uint8_t cuv_release_counter;
	uint8_t pov_release_counter;
	uint8_t puv_release_counter;
	uint16_t occ_release_counter;
	uint16_t ocd_release_counter;
	uint8_t otc_release_counter;
	uint8_t utc_release_counter;
	uint8_t otd_release_counter;
	uint8_t utd_release_counter;
	uint8_t cvd_release_counter;
	uint8_t soch_release_counter;
	uint8_t socl_release_counter;
}DATABASE_ERROR_RELEASE_COUNTER_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	DATABASE_ERRORFLAG_ROL_s	error_flag_ROL;
	DATABASE_ERRORFLAG_MOL_s	error_flag_MOL;
	DATABASE_ERRORFLAG_MSL_s	error_flag_MSL;
	DATABASE_ERROR_COUNTER_s	error_counter_ROL;
	DATABASE_ERROR_COUNTER_s	error_counter_MOL;
	DATABASE_ERROR_RELEASE_COUNTER_s	error_release_counter_ROL;
	DATABASE_ERROR_RELEASE_COUNTER_s	error_release_counter_MOL;
	DATABASE_ERROR_RELEASE_COUNTER_s	error_release_counter_MSL;
}DATABASE_ERROR_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	uint8_t error_id;
	uint16_t cell_voltage[BMS_NO_OF_CELLS];
	int16_t temperature[BMS_NO_OF_TEMPS];
	int16_t pcb_temperature;
	int32_t current;
	int32_t power;
	uint32_t pack_voltage;
	uint8_t soc;
	uint8_t soh;
	uint16_t CKWH;
	uint16_t cycle_count;
	uint16_t max_voltage;
	uint8_t max_voltage_index;
	uint16_t min_voltage;
	uint8_t min_voltage_index;
	int16_t max_temperature;
	uint8_t max_temperature_index;
	int16_t min_temperature;
	uint8_t min_temperature_index;
	uint8_t charge_mos;
	uint8_t discharge_mos;
}DATABASE_EEPROM_s;

typedef struct
{
	DATABASE_TIMESTAMP_s	timestamp;
	int ISO_RES_MONI_STATE;
	int RISO_STATE;
	uint8_t RISO_CONDITION;
	int OV_ALARM;
	int L_2_ISO_ALARM;
	int L_1_ISO_ALARM;
	int16_t RISO_P;
	int16_t BAT_Voltage;
	int16_t RISO_N;
	uint8_t count;
}DATABASE_IMD_s;

typedef struct
{
	uint16_t CHR_Voltage;
	uint16_t CHR_Current;
	uint8_t CHR_Temp;
}DATABASE_CHR_s;

typedef struct
{
	void *databaseptr;
	uint16_t database_length;
}DATABASE_HEADER_s;

typedef struct
{
	uint8_t no_of_database;
	DATABASE_HEADER_s	*database_headerptr;
}DATABASE_HEADER_DEV_s;

typedef enum
{
	DATABASE_TIMESTAMP			=	0,
	DATABASE_VOLTAGE 			=	1,
	DATABASE_TEMPERATURE 		= 	2,
	DATABASE_CURRENT 			= 	3,
	DATABASE_SOC				= 	4,
	DATABASE_ERRORFLAG_ROL		= 	5,
	DATABASE_ERRORFLAG_MOL		= 	6,
	DATABASE_ERRORFLAG_MSL		= 	7,
	DATABASE_ERRORCOUNTER_ROL	= 	8,
	DATABASE_ERRORCOUNTER_MOL	=	9,
	DATABASE_RELEASECOUNTER_ROL	=	10,
	DATABASE_RELEASECOUNTER_MOL	=	11,
	DATABASE_ERROR				=	12,
	DATABASE_EEPROM				=	13,
	DATABASE_CONTACTOR			=	14,
	DATABASE_ERROR_SOURCE		=	15,
	DATABASE_BMS				=   16,
	DATABASE_IMD                =   17,
	DATABASE_CHR                =   18,
}DATABASE_e;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

extern const DATABASE_HEADER_DEV_s	database_header_dev;
