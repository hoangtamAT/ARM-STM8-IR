#include "stm8s_eeprom.h"

void eepromWriteByte(uint8_t address, uint8_t val)
{
 uint32_t start_add;
 start_add=0x004000;
FLASH_ProgramByte(start_add+address, val);
}
uint8_t eepromReadByte(uint8_t address)
{
  uint32_t start_add=0x004000;
  return FLASH_ReadByte(start_add+address);
}

