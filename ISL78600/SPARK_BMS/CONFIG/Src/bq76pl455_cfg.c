/*
 * @filename	bq76pl455_cfg.c
 * @author		SPARKBMS TEAM
 * @date		21-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		bq76pl455_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "bq76pl455_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void BQ_AFE_Config(void)
{
	if(NO_OF_DAISY_STACK == 1)
	{
		/* Mask the Checksum Fault */
		AFE_WriteReg(BQ_ADDR, 107, 0X8000, 2, FRMWRT_SGL_NR);

		/* Communication Configuration : Single Ended, 250K Buad Rate */
		AFE_WriteReg(BQ_ADDR, 16, 0X1080, 2, FRMWRT_SGL_NR);

		/* Device Configuration : Auto Addressing Enable */
		AFE_WriteReg(BQ_ADDR, 14, 0X1D, 1, FRMWRT_SGL_NR);

		/* Device Control : Enable Auto Address */
		AFE_WriteReg(BQ_ADDR, 12, 0X08, 1, FRMWRT_SGL_NR);

		/* Auto-Monitor Period : Auto-Monitor off */
		AFE_WriteReg(BQ_ADDR, 50, 0X00, 1, FRMWRT_SGL_NR);

		/* Number of Channels : 16 */
		AFE_WriteReg(BQ_ADDR, 13, 0X10, 1, FRMWRT_SGL_NR);

		/* Channel Select : 16 Voltage Channel & 8 Auxiliary Channel */
		AFE_WriteReg(BQ_ADDR, 3, 0XFFFFFF00, 4, FRMWRT_SGL_NR);

		/* Power Configuration  */
		AFE_WriteReg(BQ_ADDR, 15, 0X80, 1, FRMWRT_SGL_NR);

		/* Command Oversampling : OVS_CYCLE - 1 & OVSMP - 0 samples */
		AFE_WriteReg(BQ_ADDR, 7, 0XF8, 1, FRMWRT_SGL_NR);

		/* Cell Voltage & Temperature Sampling : Voltage - 60us & Internal Temperature - 100us */
		AFE_WriteReg(BQ_ADDR, 62, 0XBC, 1, FRMWRT_SGL_NR);

		/* AUX Sampling : Temperature - 12.6us */
		AFE_WriteReg(BQ_ADDR, 63, 0X44444444, 4, FRMWRT_SGL_NR);

		/* Test Sampling : TI Recommended Setting */
		AFE_WriteReg(BQ_ADDR, 67, 0XF999, 2, FRMWRT_SGL_NR);

		/* Initial Sampling Delay : Voltage - 0 & Auxiliary - 0 */
		AFE_WriteReg(0X00, 61, 0X00, 1, FRMWRT_SGL_NR);

		/* Balancing Configuration : BAL_TIME - Untill Stopped & BAL_CONTINUE - 1 */
		AFE_WriteReg(BQ_ADDR, 19, 0X08, 1, FRMWRT_SGL_NR);

		/* Balancing OFF */
		AFE_WriteReg(BQ_ADDR, 20, 0X0000, 2, FRMWRT_SGL_NR);

		/* Device Config : Auto Addressing Enable and UNLATCHED_FAULT Enable */
		AFE_WriteReg(BQ_ADDR, 14, 0X11, 1, FRMWRT_SGL_NR);
	}
	if(NO_OF_DAISY_STACK > 1)
	{
	/* Mask the Checksum Fault */
	AFE_WriteReg(BQ_ADDR, 107, 0X8000, 2, FRMWRT_ALL_NR);

	/* Communication Configuration : Single Ended, 250K Buad Rate */
	AFE_WriteReg(BQ_ADDR, 16, 0X10E0, 2, FRMWRT_ALL_NR);

	/* Device Configuration : Auto Addressing Enable */
	AFE_WriteReg(BQ_ADDR, 14, 0X10, 1, FRMWRT_ALL_NR);

	/* Device Control : Enable Auto Address */
	AFE_WriteReg(BQ_ADDR, 12, 0X08, 1, FRMWRT_ALL_NR);

	/* Assign Address in Incremental Order : Master - 0 */
	BQ_AFE_AddressAll();

	/* Auto-Monitor Period : Auto-Monitor off */
	AFE_WriteReg(BQ_ADDR, 50, 0X00, 1, FRMWRT_ALL_NR);

	/* Number of Channels : 16 */
	AFE_WriteReg(BQ_ADDR, 13, 0X10, 1, FRMWRT_ALL_NR);

	/* Channel Select : 16 Voltage Channel & 8 Auxiliary Channel */
	AFE_WriteReg(BQ_ADDR, 3, 0XFFFFFF00, 4, FRMWRT_ALL_NR);

	/* Power Configuration  */
	AFE_WriteReg(BQ_ADDR, 15, 0X80, 1, FRMWRT_ALL_NR);

	/* Command Oversampling : OVS_CYCLE - 1 & OVSMP - 0 samples */
	AFE_WriteReg(BQ_ADDR, 7, 0XF8, 1, FRMWRT_ALL_NR);

	/* Cell Voltage & Temperature Sampling : Voltage - 60us & Internal Temperature - 100us */
	AFE_WriteReg(BQ_ADDR, 62, 0XBC, 1, FRMWRT_ALL_NR);

	/* AUX Sampling : Temperature - 12.6us */
	AFE_WriteReg(BQ_ADDR, 63, 0X44444444, 4, FRMWRT_ALL_NR);

	/* Test Sampling : TI Recommended Setting */
	AFE_WriteReg(BQ_ADDR, 67, 0XF999, 2, FRMWRT_ALL_NR);

	/* Initial Sampling Delay : Voltage - 0 & Auxiliary - 0 */
	AFE_WriteReg(0X00, 61, 0X00, 1, FRMWRT_ALL_NR);

	/* Balancing Configuration : BAL_TIME - Untill Stopped & BAL_CONTINUE - 1 */
	AFE_WriteReg(BQ_ADDR, 19, 0X08, 1, FRMWRT_ALL_NR);

	/* Balancing OFF */
	AFE_WriteReg(BQ_ADDR, 20, 0X0000, 2, FRMWRT_ALL_NR);

	/* Device Config : Auto Addressing Enable and UNLATCHED_FAULT Enable */
	AFE_WriteReg(BQ_ADDR, 14, 0X11, 1, FRMWRT_ALL_NR);

	AFE_WriteReg(0, 16, 0X10D0, 2, FRMWRT_SGL_NR);

	AFE_WriteReg(NO_OF_DAISY_STACK-1, 16, 0X1028, 2, FRMWRT_SGL_NR);
	}
}

void BQ_AFE_OV_Config(void)
{
	/* Cell OverVoltage Threshold : 4.2V */                       // (0XFFFF*4.2V)/5V = OVERVOLTAGE THRESHOLD
	AFE_WriteReg(BQ_ADDR, 144, 0XD70A, 2, FRMWRT_ALL_NR);

	/* Comparator OverVoltage Threshold : 4.2V */           // (0XFF*4.2V)/5.175V = OVERVOLTAGE THRESHOLD
	AFE_WriteReg(BQ_ADDR, 141, 0XCE, 1, FRMWRT_ALL_NR);

	/* AUX0 OverVoltage Threshold : 4.15V @ 0C */              // (0XFFFF*4.2V)/5V = AUX OVERVOLTAGE
	AFE_WriteReg(BQ_ADDR, 148, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX1 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 152, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX2 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 156, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX3 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 160, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX4 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 164, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX5 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 168, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX6 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 172, 0XD47A, 2, FRMWRT_ALL_NR);

	/* AUX7 OverVoltage Threshold : 4.15V @ 0C */
	AFE_WriteReg(BQ_ADDR, 176, 0XD47A, 2, FRMWRT_ALL_NR);
}

void BQ_AFE_UV_Config(void)
{
	/* Cell UnderVoltage Threshold : 3.0V */                   // (0XFFFF*3.0V)/5V = UNDERVOLTAGE THRESHOLD
	AFE_WriteReg(BQ_ADDR, 142, 0X9997, 2, FRMWRT_ALL_NR);

	/* Comparator UnderVoltage Threshold : 3.0V */             // (0XFF*3.0V)/5.175V = UNDEROLTAGE THRESHOLD
	AFE_WriteReg(BQ_ADDR, 140, 0XC4, 1, FRMWRT_ALL_NR);

	/* AUX0 UnderVoltage Threshold : 1.08V @ 60C */            // (0XFFFF*1.08V)/5V = AUX UNDERVOLTAGE
	AFE_WriteReg(BQ_ADDR, 146, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX1 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 150, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX2 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 154, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX3 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 158, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX4 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 162, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX5 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 166, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX6 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 170, 0X374C, 2, FRMWRT_ALL_NR);

	/* AUX7 UnderVoltage Threshold : 1.08V @ 60C */
	AFE_WriteReg(BQ_ADDR, 174, 0X374C, 2, FRMWRT_ALL_NR);
}


void BQ_AFE_ClearAllFault(void)
{
	/* Device Status : Reset the Comm_Clear, Comm_Reset and Stack_Fault_Det */
	AFE_WriteReg(0X00, 81, 0X38, 1, FRMWRT_ALL_NR);

	/* Fault Summary : Reset all the Faults */
	AFE_WriteReg(0X00, 82, 0XFFC0, 2, FRMWRT_ALL_NR);
}

void BQ_AFE_AddressAll(void)
{
	uint64_t Address = 0;

	for(uint8_t i = 0; i < NO_OF_DAISY_STACK; i++)
	{
		AFE_WriteReg(0X00, 10, Address, 1, FRMWRT_ALL_NR);
		Address++;
	}
}
