/*
 * @filename	sd_card.c
 * @author		SPARKBMS TEAM
 * @date		10-Jul-2023
 * @ingroup		FOLDER NAME
 * @prefix		sd_card
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "sd_card.h"

/*-------------------------------------------Macros----------------------------------------------------*/

#define BUFFER_SIZE 1000

/*-------------------------------------------Variables-------------------------------------------------*/

FIL fil; 					// File

uint8_t SDCard_Init = 0;

/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void SD_Init(void)
{
	char buffer[800];
	char com_dummy[40];


	MX_FATFS_Init();

	if(SD_CheckMount() == 1)
	{
		f_open(&fil, "MS_BMS_12S.txt", FA_OPEN_APPEND | FA_READ | FA_WRITE);

		memset(com_dummy,0,sizeof(com_dummy));
		sprintf(buffer,"Timestamp,Error_ID,");
		strcat(buffer,com_dummy);

		memset(com_dummy,0,sizeof(com_dummy));
		for(uint8_t i = 1 ; i<97 ; i++)
		{
			sprintf(com_dummy,"CV_%d,",i);
			strcat(buffer,com_dummy);
		}

		memset(com_dummy,0,sizeof(com_dummy));
		for(uint8_t i = 1 ; i<9 ; i++)
		{
			sprintf(com_dummy,"Temp_%d,",i);
			strcat(buffer,com_dummy);
		}

		memset(com_dummy,0,sizeof(com_dummy));
		sprintf(com_dummy,"Max_V,Min_V,Pack_Voltage,Pack_Current\n");
		strcat(buffer,com_dummy);

		f_puts(buffer, &fil);
		f_close(&fil);

		SDCard_Init = 1;
	}
	else
	{
		MX_FATFS_DeInit();
		SDCard_Init = 0;
	}
}

/*
 * @brief
 * @arguments
 * @retvar
 */

uint8_t SD_CheckMount(void)
{
	FATFS fs;  					// file system
	FRESULT fresult;  			// result

	fresult = f_mount(&fs, "/", 1);
	if (fresult != FR_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

uint32_t SD_CheckFreeSpace(void)
{
	FATFS *pfs;
	DWORD fre_clust;
	uint32_t freeSpace = 0;

	f_getfree("", &fre_clust, &pfs);

//	*totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);

	return freeSpace;
}

uint32_t SD_CheckTotalSpace(void)
{
	FATFS *pfs;
	DWORD fre_clust;
	uint32_t totalSpace = 0;

	f_getfree("", &fre_clust, &pfs);

	totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
//	freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);

	return totalSpace;
}

void SD_Write(void)
{
	if(SDCard_Init == 1)
	{
		if(SD_CheckMount() == 1)
		{
//			TIMER7_Start();
//			sd_flag = 1;

			DATABASE_EEPROM_s	sd_database_eeprom = {0};
			DATABASE_READ((void*)&sd_database_eeprom, DATABASE_EEPROM);

			char buffer[BUFFER_SIZE];
			char com_dummy[20];

			f_open(&fil, "MS_BMS_12S.txt", FA_OPEN_APPEND | FA_READ | FA_WRITE);

			memset(buffer,0,sizeof(buffer));
			memset(com_dummy,0,sizeof(com_dummy));
			sprintf(com_dummy,"%d:%d:%d %d/%d/%d,",sd_database_eeprom.timestamp.hour,sd_database_eeprom.timestamp.minute,sd_database_eeprom.timestamp.second,
					sd_database_eeprom.timestamp.day,sd_database_eeprom.timestamp.month,sd_database_eeprom.timestamp.year);
			strcat(buffer,com_dummy);

			memset(com_dummy,0,sizeof(com_dummy));
			sprintf(com_dummy,"%d,",sd_database_eeprom.error_id);
			strcat(buffer,com_dummy);

			for(uint8_t i=0; i<BMS_NO_OF_CELLS; i++)
			{
				memset(com_dummy,0,sizeof(com_dummy));
				sprintf(com_dummy,"%d,",sd_database_eeprom.cell_voltage[i]);
				strcat(buffer,com_dummy);
			}

			for(uint8_t i=0; i<BMS_NO_OF_TEMPS; i++)
			{
				memset(com_dummy,0,sizeof(com_dummy));
				sprintf(com_dummy,"%d,",sd_database_eeprom.temperature[i]);
				strcat(buffer,com_dummy);
			}

			memset(com_dummy,0,sizeof(com_dummy));
			sprintf(com_dummy,"%d,",sd_database_eeprom.max_voltage);
			strcat(buffer,com_dummy);

			memset(com_dummy,0,sizeof(com_dummy));
			sprintf(com_dummy,"%d,",sd_database_eeprom.min_voltage);
			strcat(buffer,com_dummy);

			memset(com_dummy,0,sizeof(com_dummy));
			sprintf(com_dummy,"%ld,",sd_database_eeprom.pack_voltage);
			strcat(buffer,com_dummy);

			memset(com_dummy,0,sizeof(com_dummy));
			sprintf(com_dummy,"%ld\n",sd_database_eeprom.current);
			strcat(buffer,com_dummy);

//			memset(com_dummy,0,sizeof(com_dummy));
//			sprintf(com_dummy,"%d,",sd_database_eeprom.soc);
//			strcat(buffer,com_dummy);
//
//			memset(com_dummy,0,sizeof(com_dummy));
//			sprintf(com_dummy,"%d,",sd_database_eeprom.soh);
//			strcat(buffer,com_dummy);
//
//			memset(com_dummy,0,sizeof(com_dummy));
//			sprintf(com_dummy,"%d,",sd_database_eeprom.cycle_count);
//			strcat(buffer,com_dummy);
//
//			memset(com_dummy,0,sizeof(com_dummy));
//			sprintf(com_dummy,"%d,",sd_database_eeprom.charge_mos);
//			strcat(buffer,com_dummy);
//
//			memset(com_dummy,0,sizeof(com_dummy));
//			sprintf(com_dummy,"%d\n",sd_database_eeprom.discharge_mos);
//			strcat(buffer,com_dummy);

			f_puts(buffer, &fil);

			f_close(&fil);

//			sd_flag = 0;
//			sd_rst = 0;
//			TIMER7_Stop();
//			GPIO_TogglePin(GPIO_PIN_LED3);
		}
		else
		{
			SDCard_Init = 0;
			MX_FATFS_DeInit();
//			GPIO_WritePin(GPIO_PIN_LED3, 1);
		}
	}
	else
	{
//		GPIO_WritePin(GPIO_PIN_LED3, 1);
	}
}

void SD_ClearBuffer(char *buffer)
{
	for (int i=0; i<BUFFER_SIZE; i++) buffer[i] = '\0';
}
