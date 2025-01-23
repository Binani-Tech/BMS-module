/*
 * eeprom.c
 *
 *  Created on: Apr 10, 2023
 *      Author: nikun
 */


#include "eeprom.h"

// EEPROM ADDRESS (8bits)
uint8_t EEPROM_ADDR = 0xA0;

// EEPROM ADDRESS (8bits)
uint8_t EEPROM_WRITE_ADDR = 0xA0;
uint8_t EEPROM_READ_ADDR = 0xA1;

uint8_t EEPROM_ReadFlag = 0;

#define eeprom_database_size  92

// function to determine the remaining bytes
uint16_t bytestowrite (uint16_t size, uint16_t offset)
{
	if ((size+offset)<PAGE_SIZE) return size;
	else return PAGE_SIZE-offset;
}

/* write the data to the EEPROM
 * @page is the number of the start page. Range from 0 to PAGE_NUM-1
 * @offset is the start byte offset in the page. Range from 0 to PAGE_SIZE-1
 * @data is the pointer to the data to write in bytes
 * @size is the size of the data
 */

void EEPROM_Write (void)
{
	DATABASE_EEPROM_s	database = {0};
	DATABASE_READ((void*)(&database), DATABASE_EEPROM);

	uint16_t size = DATABASE_Length(DATABASE_EEPROM);
	uint8_t data[eeprom_database_size] = {0};
	int paddrposition = log(PAGE_SIZE)/log(2);
	uint16_t PageAddress;
	uint16_t pos=0;
	static uint16_t startPage = 1;
	static uint16_t offset = 0;
	uint16_t endPage = startPage + ((size+offset)/PAGE_SIZE);
	uint16_t numofpages = (endPage-startPage) + 1;

	struct2array(data, &database);

	UART_EEPROM_Send(data, size, 10);

	if(numofpages == 1)
	{
		PageAddress = startPage<<paddrposition | offset;
		HAL_I2C_Mem_Write(&i2c_cfg[1], EEPROM_WRITE_ADDR, PageAddress, 2, data, size, 10);
		offset += size;
		TIMER_Delay_ms(10);
	}
	else
	{
		PageAddress = startPage<<paddrposition | offset;
		uint16_t bytesremaining = bytestowrite(size, offset);
		HAL_I2C_Mem_Write(&i2c_cfg[1], EEPROM_WRITE_ADDR, PageAddress, 2, data, bytesremaining, 10);
		TIMER_Delay_ms(10);
		startPage += 1;
		if(startPage == PAGE_NUM)
		{
			startPage = 1;
			offset = 0;
			PageAddress = startPage<<paddrposition | offset;
			HAL_I2C_Mem_Write(&i2c_cfg[1], EEPROM_WRITE_ADDR, PageAddress, 2, data, size, 100);
			TIMER_Delay_ms(10);
			offset+=size;
		}
		else
		{
			offset = 0;
			PageAddress = startPage<<paddrposition | offset;
			size = size-bytesremaining;
			pos += bytesremaining;
			HAL_I2C_Mem_Write(&i2c_cfg[1], EEPROM_WRITE_ADDR, PageAddress, 2, &data[pos], size, 100);
			TIMER_Delay_ms(10);
			offset+=size;
		}
	}

	GPIO_TogglePin(GPIO_PIN_LED);
}


void struct2array(uint8_t *array, DATABASE_EEPROM_s *database_eeprom)
{
	uint32_t database_length = DATABASE_Length(DATABASE_EEPROM);

    union
    {
        uint8_t eeprom_data[database_length];
        DATABASE_EEPROM_s database;
    }thing;

    thing.database = *database_eeprom;

    for(uint32_t i =0; i<database_length;i++)
    {
        array[i] = thing.eeprom_data[i];
    }
}

void array2struct(uint8_t *array, DATABASE_EEPROM_s *database_eeprom)
{
	uint32_t database_length = DATABASE_Length(DATABASE_EEPROM);

	union
	{
		uint8_t eeprom_data[database_length];
		DATABASE_EEPROM_s database;
	}thing;

    for(uint32_t i =0; i<database_length; i++)
    {
       thing.eeprom_data[i] = array[i];
    }

    *database_eeprom = thing.database;
}

/* READ the data from the EEPROM
 * @page is the number of the start page. Range from 0 to PAGE_NUM-1
 * @offset is the start byte offset in the page. Range from 0 to PAGE_SIZE-1
 * @data is the pointer to the data to write in bytes
 * @size is the size of the data
 */
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	int paddrposition = log(PAGE_SIZE)/log(2);

	uint16_t startPage = page;
	uint16_t endPage = startPage + ((size+offset)/PAGE_SIZE);
	EEPROM_READ_ADDR = EEPROM_READ_ADDR | ((endPage >> 8) << 1);
	uint16_t numofpages = (endPage-startPage) + 1;
	uint16_t pos=0;

	for (int i=0; i<numofpages; i++)
	{
		uint16_t PageAddress = startPage<<paddrposition | offset;
		uint16_t bytesremaining = bytestowrite(size, offset);
		HAL_I2C_Mem_Read(&i2c_cfg[1], EEPROM_READ_ADDR, PageAddress, 2, &data[pos], bytesremaining, 10);
		startPage += 1;
		offset=0;
		size = size-bytesremaining;
		pos += bytesremaining;
	}
}

DATABASE_EEPROM_s EEPROM_ReadAll (void)
{
	DATABASE_EEPROM_s readEEPROM_database = {0};
	int paddrposition = log(PAGE_SIZE)/log(2);
	static uint16_t Read_startPage = 1;
	static uint16_t endPage;
	static uint16_t size = eeprom_database_size;
	static uint16_t Read_offset = 0;
	static uint16_t numofpages;
	uint8_t data[eeprom_database_size] = {0};
	uint16_t PageAddress;
	static uint16_t bytesremaining;

//	GPIO_TogglePin(GPIO_PIN_LED3);

//	while(startPage < PAGE_NUM)
//	{
		uint8_t pos = 0;
		endPage = Read_startPage + ((size+Read_offset)/PAGE_SIZE);
		EEPROM_ADDR = EEPROM_ADDR | ((endPage >> 8) << 1);
		numofpages = (endPage-Read_startPage) + 1;

		if(numofpages > 1)
		{
			uint8_t nextPage = 1;

			for (uint8_t j=0; j<numofpages; j++)
			{
				PageAddress = Read_startPage<<paddrposition | Read_offset;
				bytesremaining = bytestowrite(size, Read_offset);
				HAL_I2C_Mem_Read(&i2c_cfg[0], EEPROM_ADDR, PageAddress, 2, &data[pos], bytesremaining, 10);
				if(nextPage == 1)
				{
					Read_startPage += 1;
					Read_offset=0;
					size = size-bytesremaining;
					pos += bytesremaining;
					nextPage = 0;
				}
				else
				{
					Read_offset += size;
					size = eeprom_database_size;
				}

			}

			if(data[0] == 255)
			{
//				break;
//				GPIO_WritePin(GPIO_PIN_LED3, 0);
				EEPROM_ReadFlag = 0;
				Read_startPage = 1;
				Read_offset = 0;
			}
			else
			{
				array2struct(data, &readEEPROM_database);
				return readEEPROM_database;
			}


//			TIMER_Delay_ms(1);
		}
		else
		{
			PageAddress = Read_startPage<<paddrposition | Read_offset;
			HAL_I2C_Mem_Read(&i2c_cfg[0], EEPROM_ADDR, PageAddress, 2, data, size, 10);
			Read_offset += size;
			if(data[0] == 255)
			{
//				break;
//				GPIO_WritePin(GPIO_PIN_LED3, 0);
				EEPROM_ReadFlag = 0;
				Read_startPage = 1;
				Read_offset = 0;
			}
			else
			{
				array2struct(data, &readEEPROM_database);
				return readEEPROM_database;
			}
//			TIMER_Delay_ms(1);
		}
//	}
}

void EEPROM_PageRead(uint16_t page, uint8_t *data)
{
	int paddrposition = log(PAGE_SIZE)/log(2);
	EEPROM_READ_ADDR = EEPROM_READ_ADDR | ((page >> 8) << 1);
	uint16_t PageAddress = page<<paddrposition;
	HAL_I2C_Mem_Read(&i2c_cfg[1], EEPROM_READ_ADDR, PageAddress, 2, data, PAGE_SIZE, HAL_MAX_DELAY);
}

void EEPROM_ERASEFULL(void)
{
	for(uint16_t i=1; i<PAGE_NUM; i++)
	{
		EEPROM_PageErase(i);
	}
}
/* Erase a page in the EEPROM Memory
 * @page is the number of page to erase
 * In order to erase multiple pages, just use this function in the for loop
 */
void EEPROM_PageErase (uint16_t page)
{
	// calculate the memory address based on the page number
	int paddrposition = log(PAGE_SIZE)/log(2);
	uint16_t PageAddress = page<<paddrposition;
	EEPROM_WRITE_ADDR = EEPROM_WRITE_ADDR | ((page >> 8) << 1);
	// create a buffer to store the reset values
	uint8_t data[PAGE_SIZE];
	memset(data,0x00,PAGE_SIZE);

	// write the data to the EEPROM
	HAL_I2C_Mem_Write(&i2c_cfg[1], EEPROM_WRITE_ADDR, PageAddress, 2, data, PAGE_SIZE,10);

	TIMER_Delay_ms(10); // write cycle delay
}

