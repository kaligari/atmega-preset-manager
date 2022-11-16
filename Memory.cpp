#include "Memory.h"

void Memory::init(byte* i_preset_number, byte* i_preset) {
  preset_number = i_preset_number;
  preset = i_preset;
}

void Memory::readPreset() {
  for(byte i = 0; i < 4; i++) {
    preset[i] = EEPROM.read(*preset_number * 4 + i);
  }
}

void Memory::storePreset() {
  for(byte i = 0; i < 4; i++) {
    EEPROM.update(*preset_number * 4 + i, preset[i]);
  }
}