/*
 * @filename	adc_exp.c
 * @author		SPARKBMS TEAM
 * @date		01-Jun-2023
 * @ingroup		FOLDER NAME
 * @prefix		adc_exp
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "adc_exp.h"

/*-------------------------------------------Macros----------------------------------------------------*/

#define ADCEXP_ADDR1		(0X17 << 1)
#define ADCEXP_ADDR2		(0X15 << 1)

/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void ADC_EXP_Init(void)
{
	uint8_t Tx_Buff[3] = {0};

	/* Analog Input Config in PIN_CFG */
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X5;
	Tx_Buff[2] = 0X00;

	HAL_I2C_Master_Transmit(&i2c_cfg[0], ADCEXP_ADDR2 , Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Analog Pin Selection for Sequencing in AUTO_SEQ_CHSEL */
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X12;
	Tx_Buff[2] = 0XFF;

	HAL_I2C_Master_Transmit(&i2c_cfg[0], ADCEXP_ADDR2, Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Audo Sequence Mode and Enable Channel Sequencing in SEQUENCE_CFG */
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X10;
	Tx_Buff[2] = 0X11;

	HAL_I2C_Master_Transmit(&i2c_cfg[0], ADCEXP_ADDR2, Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Analog Input Config in PIN_CFG */
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X5;
	Tx_Buff[2] = 0X00;

	HAL_I2C_Master_Transmit(&i2c_cfg[0], ADCEXP_ADDR1, Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Analog Pin Selection for Sequencing in AUTO_SEQ_CHSEL */
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X12;
	Tx_Buff[2] = 0XFF;

	HAL_I2C_Master_Transmit(&i2c_cfg[0], ADCEXP_ADDR1, Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Audo Sequence Mode and Enable Channel Sequencing in SEQUENCE_CFG */
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X10;
	Tx_Buff[2] = 0X11;

	HAL_I2C_Master_Transmit(&i2c_cfg[0], ADCEXP_ADDR1, Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);
}

void ADC_EXP_Temperatures(int16_t *temperature)
{
	uint8_t RX_Buff[NO_OF_EXT_TEMPS*2] = {0};
	uint16_t Temp_ADC = 0;
	int16_t Vout = 0;
	int16_t R_NTC = 0;

	uint8_t Count = 0;

	HAL_I2C_Master_Receive(&i2c_cfg[0], ADCEXP_ADDR1, RX_Buff, NO_OF_EXT_TEMPS, HAL_MAX_DELAY);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c_cfg[0], ADCEXP_ADDR2, &RX_Buff[NO_OF_EXT_TEMPS], NO_OF_EXT_TEMPS, HAL_MAX_DELAY);

	for(uint8_t i=0; i<NO_OF_EXT_TEMPS; i++)
	{
		Temp_ADC = ((RX_Buff[Count] << 8) | (RX_Buff[Count + 1] & 0XF0)) >> 4;
		Vout = (Temp_ADC*3323)/4095;
		R_NTC = (Vout * 10000)/(5000 - Vout);
		temperature[i] = ((298*3700)/(298*log((float)R_NTC/10000)+3700)) - 273;
		Count += 2;
	}
}
