/*
 * @filename	balancing.c
 * @author		SPARKBMS TEAM
 * @date		Apr 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		balancing
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "balancing.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

static DATABASE_BMS_s		bal_database_bms = {0};
static DATABASE_VOLTAGE_s	bal_database_voltage = {0};
static DATABASE_CURRENT_s	bal_database_current = {0};

static uint8_t counter = 0;
static uint16_t count = 0;
static uint16_t count_on = 0;
/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void BAL_Check(void)
{
	DATABASE_READ((void*)(&bal_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&bal_database_voltage), DATABASE_VOLTAGE);
	DATABASE_READ((void*)(&bal_database_current), DATABASE_CURRENT);

	if(bal_database_bms.afe_state != AFE_SHUTDOWN)    //AFE not being in sutdown state has highe prority to start balancing
	{
		if(bal_database_bms.bms_state == BMS_CHARGE || bal_database_bms.bms_state == BMS_STANDBY) //Balancing only  required when bms is in charing state
		{
			if(bal_database_voltage.max_voltage > PB_BV && bal_database_voltage.diff_voltage > PB_BDIFFV && bal_database_current.pack_current >
			PB_BC)         //This are the conditions which are necessary to start balancing
			{              //for actual values of macros check fault_sfg.h file
				if(counter == 0)
				{
					bal_database_bms.balancing_status = BAL_ON;                //it's stores in database balancing is in did on
					DATABASE_WRITE((void*)(&bal_database_bms), DATABASE_BMS);
					BAL_START();
				}
				else
				{
					BAL_STOP();
					bal_database_bms.balancing_status = BAL_OFF;
					DATABASE_WRITE((void*)(&bal_database_bms), DATABASE_BMS);
				}
			}
			else
			{
				AFE_WriteReg(BQ_ADDR, 20, 0X0000, 2, FRMWRT_SGL_NR);
				for(uint8_t i =0; i< NO_OF_CELLS; i++)
				{
					bal_database_voltage.cell_balancing_status[i] = BAL_OFF;
				}
				bal_database_bms.balancing_status = BAL_OFF;
				DATABASE_WRITE((void*)(&bal_database_bms), DATABASE_BMS);
			}
		}
		else
		{
			count_on = 0;
			AFE_WriteReg(BQ_ADDR, 20, 0X0000, 2, FRMWRT_SGL_NR);
			for(uint8_t i =0; i< NO_OF_CELLS; i++)
			{
				bal_database_voltage.cell_balancing_status[i] = BAL_OFF;
			}
			bal_database_bms.balancing_status = BAL_OFF;
			DATABASE_WRITE((void*)(&bal_database_bms), DATABASE_BMS);
		}
	}
}

void BAL_START(void)
{
	uint16_t indices;   //this variable is used for enable cells-balancing for individual cells
	uint16_t minV = 0;
	static bool count  = 0;
	DATABASE_READ((void*)(&bal_database_bms), DATABASE_BMS);
	DATABASE_READ((void*)(&bal_database_voltage), DATABASE_VOLTAGE);

	minV = bal_database_voltage.min_voltage;

	if(bal_database_bms.balancing_status == BAL_ON)
	{
		uint8_t i = count;
		while(i < NO_OF_CELLS)
		{
			if (bal_database_voltage.cell_voltage[i] >= (minV + PB_BDIFFV)) //this is minimum check for cell balancing to be active
			{
				indices = indices | (1 << i);             //each bit of insices represents as a cell
				bal_database_voltage.cell_balancing_status[i] = BAL_ON;
			}
			i=i+2;
		}

		DATABASE_WRITE((void*)(&bal_database_voltage), DATABASE_VOLTAGE);

		AFE_WriteReg(BQ_ADDR, 20, indices, 2, FRMWRT_SGL_NR); //this fuction will tell the AFE to start banavcing of specific cell which we
	}                                                         // get from process we did before it {20 is address for balancing enable register

	count_on++;
	if(count_on == 120)
	{
		count_on = 0;
		counter = 1;
		if(count == 0) { count = 1; }
		else { count = 0; }
	}



}

void BAL_STOP(void)
{
	DATABASE_READ((void*)(&bal_database_voltage), DATABASE_VOLTAGE);

	AFE_WriteReg(BQ_ADDR, 20, 0X0000, 2, FRMWRT_SGL_NR); //it sends 0X0000 to adress 20 to disable cell balancing
	count++;
	for(uint8_t i =0; i< NO_OF_CELLS; i++)
	{
		bal_database_voltage.cell_balancing_status[i] = BAL_OFF;
	}

	DATABASE_WRITE((void*)(&bal_database_voltage), DATABASE_VOLTAGE);

	if(count == 120)
	{
		counter = 0;
		count = 0;
	}
}
