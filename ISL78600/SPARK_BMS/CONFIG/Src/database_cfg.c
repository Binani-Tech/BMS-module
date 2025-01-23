/*
 * @filename	database_cfg.c
 * @author		SPARKBMS TEAM
 * @date		Apr 18, 2023
 * @ingroup		FOLDER NAME
 * @prefix		database_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "database_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_TIMESTAMP_s	database_timestamp;

static DATABASE_VOLTAGE_s	database_voltage;

static DATABASE_TEMPERATURE_s	database_temperature;

static DATABASE_CURRENT_s	database_current;

static DATABASE_SOC_s	database_soc;

static DATABASE_ERRORFLAG_MOL_s	database_errorflag_MOL;

static DATABASE_ERRORFLAG_MSL_s	database_errorflag_MSL;

static DATABASE_ERRORFLAG_ROL_s	database_errorflag_ROL;

static DATABASE_ERROR_s	database_error;

static DATABASE_ERROR_COUNTER_s	database_errorcounter_MOL;

static DATABASE_ERROR_COUNTER_s	database_errorcounter_ROL;

static DATABASE_ERROR_RELEASE_COUNTER_s	database_releasecounter_MOL;

static DATABASE_ERROR_RELEASE_COUNTER_s	database_releasecounter_ROL;

static DATABASE_EEPROM_s database_eeprom;

static DATABASE_CONTACTOR_s	database_contactor;

static DATABASE_ERROR_SOURCE_s database_error_source;

static DATABASE_IMD_s	database_IMD;

static DATABASE_BMS_s	database_bms;

static DATABASE_CHR_s	database_CHR;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

static DATABASE_HEADER_s database_header[] = {
		{
				.databaseptr = (void*)(&database_timestamp),
				.database_length = sizeof(DATABASE_TIMESTAMP_s)
		},
		{
				.databaseptr = (void*)(&database_voltage),
				.database_length = sizeof(DATABASE_VOLTAGE_s)
		},
		{
				.databaseptr = (void*)(&database_temperature),
				.database_length = sizeof(DATABASE_TEMPERATURE_s)
		},
		{
				.databaseptr = (void*)(&database_current),
				.database_length = sizeof(DATABASE_CURRENT_s)
		},
		{
				.databaseptr = (void*)(&database_soc),
				.database_length = sizeof(DATABASE_SOC_s)
		},
		{
				.databaseptr = (void*)(&database_errorflag_ROL),
				.database_length = sizeof(DATABASE_ERRORFLAG_ROL_s)
		},
		{
				.databaseptr = (void*)(&database_errorflag_MOL),
				.database_length = sizeof(DATABASE_ERRORFLAG_MOL_s)
		},
		{
				.databaseptr = (void*)(&database_errorflag_MSL),
				.database_length = sizeof(DATABASE_ERRORFLAG_MSL_s)
		},
		{
				.databaseptr = (void*)(&database_errorcounter_ROL),
				.database_length = sizeof(DATABASE_ERROR_COUNTER_s)
		},
		{
				.databaseptr = (void*)(&database_errorcounter_MOL),
				.database_length = sizeof(DATABASE_ERROR_COUNTER_s)
		},
		{
				.databaseptr = (void*)(&database_releasecounter_ROL),
				.database_length = sizeof(DATABASE_ERROR_RELEASE_COUNTER_s)
		},
		{
				.databaseptr = (void*)(&database_releasecounter_MOL),
				.database_length = sizeof(DATABASE_ERROR_RELEASE_COUNTER_s)
		},
		{
				.databaseptr = (void*)(&database_error),
				.database_length = sizeof(DATABASE_ERROR_s)
		},
		{
				.databaseptr = (void*)(&database_eeprom),
				.database_length = sizeof(DATABASE_EEPROM_s)
		},
		{
				.databaseptr = (void*)(&database_contactor),
				.database_length = sizeof(DATABASE_CONTACTOR_s)
		},
		{
				.databaseptr = (void*)(&database_error_source),
				.database_length = sizeof(DATABASE_ERROR_SOURCE_s)
		},
		{
				.databaseptr = (void*)(&database_bms),
				.database_length = sizeof(DATABASE_BMS_s)
		},
		{
				.databaseptr = (void*)(&database_IMD),
				.database_length = sizeof(DATABASE_IMD_s)
		},
		{
				.databaseptr = (void*)(&database_CHR),
				.database_length = sizeof(DATABASE_CHR_s)
		}
};

const DATABASE_HEADER_DEV_s	database_header_dev = {
		.no_of_database = sizeof(database_header)/sizeof(DATABASE_HEADER_s),
		.database_headerptr = &database_header[0],
};
