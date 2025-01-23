/*
 * @filename	contactor.c
 * @author		SPARKBMS TEAM
 * @date		21-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		contactor
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "contactor.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_BMS_s	cont_database_bms = {0};
static DATABASE_CONTACTOR_s		cont_database_contactor = {0};
static DATABASE_EEPROM_s	cont_database_eeprom = {0};
//static DATABASE_VOLTAGE_s	isl_database_voltage = {0};
uint8_t cnt = 0;
uint8_t Delay_req = 0;
uint8_t error_req = 0;
extern bool check;
uint8_t cont_int = 0;
bool cont_startreq = 0;
bool cont_init = 0;

bool MainSeqCheck = 0;
bool SlowChrCheck = 0;
bool FastChrCheck = 0;
bool HVACSeqCheck = 0;
bool EMGcheck ;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void CONT_Init(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_eeprom), DATABASE_EEPROM);

	if(cont_database_bms.bms_state == BMS_IDLE)
	{
		cont_init = 1;
		CONT_Open(GPIO_PIN_HS_CONTACTOR);
		HAL_Delay(500);
		cont_database_contactor.CONT_MAIN_MINUS = CONT_OPEN;

		CONT_Open(GPIO_PIN_LS_CONTACTOR);
		HAL_Delay(500);
		cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;

		CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
		HAL_Delay(500);
		cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;

		CONT_Open(GPIO_PIN_DCDC_CONTACTOR);
		HAL_Delay(500);
		cont_database_contactor.CONT_DCDC = CONT_OPEN;

		CONT_Open(GPIO_PIN_THERM_CONTACTOR);
		HAL_Delay(500);
		cont_database_contactor.CONT_THERM = CONT_OPEN;

		CONT_Open(GPIO_PIN_EXT_CONTACTOR);
		HAL_Delay(500);
		cont_database_contactor.CONT_EXT = CONT_OPEN;

		DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

		cont_database_bms.cont_state = CONT_STANDBY;
		DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);
        check = 0;

		cont_database_eeprom.charge_mos = CONT_OPEN;
		cont_database_eeprom.discharge_mos = CONT_OPEN;
		DATABASE_WRITE((void*)(&cont_database_eeprom), DATABASE_EEPROM);
		cont_int = 1;
	}
}

void CONT_StateRequest(CONTACTOR_STATE_e state)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_eeprom), DATABASE_EEPROM);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
	if(state == CONT_NORMAL)
	{
		if(cont_database_bms.bms_state != BMS_ERROR )//&& cont_startreq == 1)
		{
			CONT_Close(GPIO_PIN_LS_CONTACTOR);
			TIMER_Delay_ms(100);
			cont_database_contactor.CONT_MAIN_MINUS= CONT_CLOSE;

			CONT_Close(GPIO_PIN_PCHG_CONTACTOR);
			TIMER_Delay_ms(3000);
			cont_database_contactor.CONT_PRECHARGE = CONT_CLOSE;

//			ISO_VOLTAGE_Read();

			CONT_Close(GPIO_PIN_HS_CONTACTOR);
			TIMER_Delay_ms(1000);
			cont_database_contactor.CONT_MAIN_PLUS = CONT_CLOSE;

			CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
//			HAL_Delay(500);
			cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			error_req = 0;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

			cont_database_bms.cont_state = CONT_NORMAL;
			DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);

			cont_database_eeprom.charge_mos = CONT_CLOSE;
			cont_database_eeprom.discharge_mos = CONT_CLOSE;
			DATABASE_WRITE((void*)(&cont_database_eeprom), DATABASE_EEPROM);
			EMGcheck = 1;
		}

	}
	else if(state == CONT_ERROR)
	{
		if(cont_database_bms.bms_state != BMS_DISCHARGE)
		{
			if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
				HAL_Delay(500);
				cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			}

			CONT_Open(GPIO_PIN_HS_CONTACTOR);
			ERROR_Dealy();
			cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;

			if(cont_database_contactor.CONT_DCDC == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_DCDC_CONTACTOR);
				HAL_Delay(100);
				cont_database_contactor.CONT_DCDC = CONT_OPEN;
			}

			if(cont_database_contactor.CONT_EXT == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_EXT_CONTACTOR);
				HAL_Delay(100);
				cont_database_contactor.CONT_EXT = CONT_OPEN;
			}

			CONT_Open(GPIO_PIN_LS_CONTACTOR);
			ERROR_Dealy();
			cont_database_contactor.CONT_MAIN_MINUS = CONT_OPEN;

			cont_database_bms.cont_state = CONT_ERROR;
			Delay_req = 0;
//			cont_errorFlag = 1;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
			DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);

			cont_database_eeprom.charge_mos = CONT_OPEN;
			cont_database_eeprom.discharge_mos = CONT_OPEN;
			DATABASE_WRITE((void*)(&cont_database_eeprom), DATABASE_EEPROM);
		}

		if(cont_database_bms.bms_state != BMS_CHARGE)
		{
			if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
				HAL_Delay(500);
				cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			}

			CONT_Open(GPIO_PIN_HS_CONTACTOR);
			ERROR_Dealy();
			cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;

			CONT_Open(GPIO_PIN_LS_CONTACTOR);
			ERROR_Dealy();
			cont_database_contactor.CONT_MAIN_MINUS = CONT_OPEN;

			cont_database_bms.cont_state = CONT_ERROR;
			Delay_req = 0;
//			cont_errorFlag = 1;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
			DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);

			cont_database_eeprom.charge_mos = CONT_OPEN;
			cont_database_eeprom.discharge_mos = CONT_OPEN;
			DATABASE_WRITE((void*)(&cont_database_eeprom), DATABASE_EEPROM);
		}
		Req_MainSeq = 0;    MainSeqCheck = 0;
		Req_SlowChrSeq = 0; SlowChrCheck = 0;
		Req_FastChrSeq = 0; FastChrCheck = 0;
		Req_HVACSeq = 0;    HVACSeqCheck = 0;
	}

	if(state == CONT_STANDBY)
	{
		    CONT_Open(GPIO_PIN_LS_CONTACTOR);
			HAL_Delay(1000);
			cont_database_contactor.CONT_MAIN_MINUS= CONT_OPEN;

			CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
			HAL_Delay(5000);
			cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;


			CONT_Open(GPIO_PIN_LS_CONTACTOR);
			cont_database_contactor.CONT_MAIN_MINUS= CONT_OPEN;
			Delay_req = 0;
			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
	}
}

void CONT_DCDC(CONTACTOR_STATE_e state)
{
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
	if(state == CONT_NORMAL)
	{
		CONT_Close(GPIO_PIN_DCDC_CONTACTOR);
		HAL_Delay(50);
		cont_database_contactor.CONT_DCDC= CONT_CLOSE;
	}

	else if(state == CONT_STANDBY)
	{
		CONT_Close(GPIO_PIN_DCDC_CONTACTOR);
		HAL_Delay(50);
		cont_database_contactor.CONT_DCDC = CONT_OPEN;
	}
	DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
}
void Seq_Check(void)
{
	if(Req_MainSeq == 1 && MainSeqCheck == 0 && SlowChrCheck == 0 && FastChrCheck == 0)
	{
		CONT_MainSequence();
		MainSeqCheck = 1;
	}
	else if(Req_MainSeq == 0 && MainSeqCheck == 1)
	{
		CONT_StopSequence();
		MainSeqCheck = 0;
	}

	if(Req_SlowChrSeq == 1 && SlowChrCheck == 0 && Req_FastChrSeq == 0)
	{
		CONT_Slow_CHR_Seq();
		Req_FastChrSeq = 0;
		SlowChrCheck = 1;
	}
	else if(Req_SlowChrSeq == 0 && SlowChrCheck == 1)
	{
		CONT_SlowChr_Disable();
		Req_FastChrSeq = 0;
		SlowChrCheck = 0;
	}

	if(Req_FastChrSeq == 1 && FastChrCheck == 0 && SlowChrCheck == 0)
	{
		CONT_Fast_CHR_Seq();
		Req_SlowChrSeq = 0;
		FastChrCheck = 1;
	}
	else if(Req_FastChrSeq == 0 && FastChrCheck == 1)
	{
		CONT_FastChr_Disable();
		Req_SlowChrSeq = 0;
		FastChrCheck = 0;
	}

	if(Req_HVACSeq == 1 && HVACSeqCheck == 0)
	{
		CONT_HVAC_Seq();
		HVACSeqCheck = 1;
	}
	else if(Req_HVACSeq == 0 && HVACSeqCheck == 1)
	{
		CONT_HVAC_Disable();
		HVACSeqCheck = 0;
	}

}

void CONT_MainSequence(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

//		if(cont_database_bms.bms_state != BMS_ERROR )
		{
			CONT_Close(GPIO_PIN_LS_CONTACTOR);
			HAL_Delay(100);
			cont_database_contactor.CONT_MAIN_MINUS= CONT_CLOSE;

			CONT_Close(GPIO_PIN_PCHG_CONTACTOR);
			HAL_Delay(3000);
			cont_database_contactor.CONT_PRECHARGE = CONT_CLOSE;

			CONT_Close(GPIO_PIN_HS_CONTACTOR);
			HAL_Delay(50);
			cont_database_contactor.CONT_MAIN_PLUS = CONT_CLOSE;

			CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
			cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			error_req = 0;

			CONT_Close(GPIO_PIN_EXT_CONTACTOR);
			HAL_Delay(100);
			cont_database_contactor.CONT_EXT = CONT_CLOSE;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

			cont_database_bms.cont_state = CONT_NORMAL;
			DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);

			CAN_MAIN_SEQ_CPL();
			cont_int = 0;
			cont_startreq = 1;
		}
//		else
//		{
//			Req_MainSeq = 0;
//		}
}

void CONT_StopSequence(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

	if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
	{
		CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
		HAL_Delay(100);
		cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
	}

	CONT_Open(GPIO_PIN_EXT_CONTACTOR);
	HAL_Delay(100);
	cont_database_contactor.CONT_EXT = CONT_OPEN;

	CONT_Open(GPIO_PIN_HS_CONTACTOR);
	HAL_Delay(3000);
	cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;

	CONT_Open(GPIO_PIN_LS_CONTACTOR);
	HAL_Delay(100);
	cont_database_contactor.CONT_MAIN_MINUS= CONT_OPEN;

	DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

	cont_database_bms.cont_state = CONT_STANDBY;
	DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);
}

void CONT_Slow_CHR_Seq(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

		if(cont_database_bms.bms_state != BMS_ERROR )
		{
//			if(cont_database_contactor.CONT_MAIN_PLUS == CONT_CLOSE)
//			{
//				CONT_Open(GPIO_PIN_HS_CONTACTOR);
//				HAL_Delay(50);
//				cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;
//			}

			if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
				HAL_Delay(50);
				cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			}

			if(cont_database_contactor.CONT_MAIN_MINUS == CONT_OPEN)
			{
				CONT_Close(GPIO_PIN_LS_CONTACTOR);
				HAL_Delay(100);
				cont_database_contactor.CONT_MAIN_MINUS= CONT_CLOSE;
			}

			CONT_Close(GPIO_PIN_EXT_CONTACTOR);
			HAL_Delay(100);
			cont_database_contactor.CONT_EXT = CONT_CLOSE;


			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

			cont_database_bms.cont_state = CONT_NORMAL;
			DATABASE_WRITE((void*)(&cont_database_bms), DATABASE_BMS);
			CAN_SLOW_CHR_SEQ_CPL();
		}
		else
		{
			Req_SlowChrSeq = 0;
		}
}

void CONT_SlowChr_Disable(void)
{
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

			if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
				HAL_Delay(100);
				cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			}

//			CONT_Open(GPIO_PIN_HS_CONTACTOR);
//			HAL_Delay(100);
//			cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;

			CONT_Open(GPIO_PIN_EXT_CONTACTOR);
			HAL_Delay(100);
			cont_database_contactor.CONT_EXT= CONT_OPEN;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
}

void CONT_Fast_CHR_Seq(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

		if(cont_database_bms.bms_state != BMS_ERROR )
		{
			if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
				HAL_Delay(50);
				cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
			}

			if(cont_database_contactor.CONT_MAIN_PLUS == CONT_CLOSE)
			{
				CONT_Open(GPIO_PIN_HS_CONTACTOR);
				HAL_Delay(50);
				cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;
			}

			if(cont_database_contactor.CONT_MAIN_MINUS == CONT_OPEN)
			{
				CONT_Close(GPIO_PIN_LS_CONTACTOR);
				HAL_Delay(100);
				cont_database_contactor.CONT_MAIN_MINUS= CONT_CLOSE;
			}

			CONT_Close(GPIO_PIN_DCDC_CONTACTOR);
			HAL_Delay(300);
			cont_database_contactor.CONT_DCDC = CONT_CLOSE;

			CONT_Close(GPIO_PIN_EXT_CONTACTOR);
			HAL_Delay(100);
			cont_database_contactor.CONT_EXT = CONT_CLOSE;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
			CAN_FAST_CHR_SEQ_CPL();
		}
		else
		{
			Req_FastChrSeq = 0;
		}
}

void CONT_FastChr_Disable(void)
{
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

	if(cont_database_contactor.CONT_PRECHARGE == CONT_CLOSE)
	{
		CONT_Open(GPIO_PIN_PCHG_CONTACTOR);
		HAL_Delay(100);
		cont_database_contactor.CONT_PRECHARGE = CONT_OPEN;
	}

	CONT_Open(GPIO_PIN_EXT_CONTACTOR);
	HAL_Delay(100);
	cont_database_contactor.CONT_EXT = CONT_OPEN;

	CONT_Open(GPIO_PIN_HS_CONTACTOR);
	HAL_Delay(100);
	cont_database_contactor.CONT_MAIN_PLUS = CONT_OPEN;

	CONT_Open(GPIO_PIN_DCDC_CONTACTOR);
	cont_database_contactor.CONT_DCDC= CONT_OPEN;

	DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
}

void CONT_HVAC_Seq(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

		if(cont_database_bms.bms_error != BMS_SHORT_CIRCUIT )
		{
			if(cont_database_contactor.CONT_MAIN_MINUS == CONT_OPEN)
			{
				CONT_Close(GPIO_PIN_LS_CONTACTOR);
				HAL_Delay(100);
				cont_database_contactor.CONT_MAIN_MINUS= CONT_CLOSE;
			}

			CONT_Close(GPIO_PIN_THERM_CONTACTOR);
			cont_database_contactor.CONT_THERM = CONT_CLOSE;

			DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
			CAN_HVAC_SEQ_CPL();
		}
		else
		{
			Req_HVACSeq = 0;
		}
}

void CONT_HVAC_Disable(void)
{
	DATABASE_READ((void*)(&cont_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&cont_database_contactor), DATABASE_CONTACTOR);

	if(cont_database_bms.bms_state == BMS_ERROR)
	{
		CONT_Open(GPIO_PIN_LS_CONTACTOR);
		HAL_Delay(100);
		cont_database_contactor.CONT_MAIN_MINUS= CONT_OPEN;
	}
	CONT_Open(GPIO_PIN_THERM_CONTACTOR);
	cont_database_contactor.CONT_THERM = CONT_OPEN;

	DATABASE_WRITE((void*)(&cont_database_contactor), DATABASE_CONTACTOR);
}

void CONT_Dealy(void)
{
	if(Delay_req<2)
	{
		HAL_Delay(5000);
		Delay_req++;
	}
}

void ERROR_Dealy(void)
{
	if(error_req<2)
	{
		HAL_Delay(500);
		error_req++;
	}
}

void CONT_Open(GPIO_PINs cont_name)
{
	GPIO_WritePin(cont_name, 0);
}

void CONT_Close(GPIO_PINs cont_name)
{
	GPIO_WritePin(cont_name, 1);
}

