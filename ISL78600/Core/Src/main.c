/*
 * @filename	main.c
 * @author		SPARKBMS TEAM
 * @date		May 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		main
 *
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "mcu_cfg.h"
#include "rcc.h"
#include "spi.h"
#include "gpio.h"
#include "rtc.h"
#include "timer.h"
#include "afe.h"
#include "can.h"
#include "database.h"
#include "uart.h"
#include "i2c.h"
#include "nvic.h"
#include "eeprom.h"
#include "dma.h"
#include "adc.h"
#include "contactor.h"
#include "current.h"
//#include "isl78600.h"
#include "bq76pl455.h"
#include "soc.h"
#include "balancing.h"
#include "adc_exp.h"
#include "sd_card.h"
#include "ble.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

uint8_t error_flag = 0;
uint8_t temp_cnt = 0;
uint8_t bal_cnt = 0;
uint16_t eeprom_cnt = 0;
uint8_t can_cnt = 0;
uint8_t soh_cnt = 0;
static uint16_t current_timer = 0;
bool EmergencyKey = 0;
extern bool EMGcheck;


/*-------------------------------------------Function Prototypes---------------------------------------*/

void BMS_Init(void);

/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

int main(void)
{
	HAL_Init();
	RCC_Init();
	BASIC_TIMER_Init();
	GENERAL_TIMER_Init();
	TIMER7_Init();
	RTC_Init();
	GPIO_Init(&gpio_cfg[0]);
	BOOT0_Init();
	NVIC_Init();
	SPI_Init();
	I2C_Init();
	UART_Init();
	CAN1_Init();
	DMA_Init();
	ADC_Init();
//	ADC_EXP_Init();
	DATABASE_Init();
	BMS_Init();
	CONT_Init();
	BQ_AFE_Init();
//	SOC_Init();
//	SD_Init();
//	BLESparkViewInit();
//	EEPROM_ERASEFULL();
//	CURRENT_StartRead();
//	UART_Send_Index();
	TIMER_Delay_ms(2);
	EMGcheck = 1;

	GPIO_TogglePin(GPIO_PIN_FAULT_LED);
	HAL_Delay(100);
	GPIO_TogglePin(GPIO_PIN_FAULT_LED);

	while(1)
	{
			current_timer = __HAL_TIM_GET_COUNTER(&basic_timer_cfg);
			if(current_timer%1000 == 0)		// 100 msec
			{
				HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
				BQ_AFE_ReadVoltage();

//				EmergencyKey = GPIO_ReadPin(GPIO_PIN_KEYON1_EN);
//				if(EmergencyKey == 0 && EMGcheck == 0)
//				{
//					CONT_StateRequest(CONT_NORMAL);
//					EMGcheck = 1;
//				}
//				else if(EmergencyKey == 1 && EMGcheck == 1)
//				{
//					CONT_StateRequest(CONT_STANDBY);
//					EMGcheck = 0;
//				}
//				SOC_Update();
				Seq_Check();
				temp_cnt++;
				bal_cnt++;
			}

			if(bal_cnt == 5)			// 500 msec
			{
//				BAL_Check();
				BQ_AFE_GETState();

				bal_cnt = 0;
			}

			if(temp_cnt == 10)			// 1000 msec
			{
				BQ_AFE_ReadTemperature();

				can_cnt++;
				temp_cnt  = 0;
			}

			if(can_cnt == 5)
			{
  			    eeprom_cnt++;
  			    soh_cnt++;
				can_cnt = 0;
			}

			if(soh_cnt == 12)     //60 sec
			{
				soh_cnt = 0;
			}

			if(eeprom_cnt == 60)		// 300 sec
			{
				eeprom_cnt = 0;
			}
	}
}

void BMS_Init(void)
{
	DATABASE_BMS_s	database_bms = {0};

	database_bms.afe_error = AFE_NO_ERR;
	database_bms.afe_state = AFE_SHUTDOWN;
	database_bms.bms_state = BMS_IDLE;
	database_bms.bms_error = BMS_NO_ERR;
	database_bms.balancing_status = BAL_OFF;

	DATABASE_WRITE((void*)(&database_bms), DATABASE_BMS);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	current_timer = 1;
}

