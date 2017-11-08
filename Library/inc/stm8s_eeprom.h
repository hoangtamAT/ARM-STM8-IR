#ifndef _EEPROM_H
#define _EEPROM_H
#include "stm8s.h"
#include "stm8s_flash.h"

void eepromWriteWord(uint8_t address, uint8_t val);
uint8_t eepromReadByte(uint8_t address);


#endif 