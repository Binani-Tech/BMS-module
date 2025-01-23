/*
 * eeprom.h
 *
 *  Created on: Apr 10, 2023
 *      Author: nikun
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "mcu_cfg.h"
#include "i2c_cfg.h"
#include "database.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"

// Define the Page Size and number of pages
#define PAGE_SIZE 256     // in Bytes
#define PAGE_NUM  500    // number of pages

extern uint8_t EEPROM_ReadFlag;

void EEPROM_Write (void);
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_PageErase (uint16_t page);
void EEPROM_PageRead(uint16_t page, uint8_t *data);
void EEPROM_ERASEFULL(void);
DATABASE_EEPROM_s EEPROM_ReadAll (void);
void struct2array(uint8_t *array, DATABASE_EEPROM_s *database_eeprom);
void array2struct(uint8_t *array, DATABASE_EEPROM_s *database_eeprom);

#endif /* INC_EEPROM_H_ */
