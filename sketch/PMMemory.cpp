#include "PresetManager.h"

void PresetManager::readPreset() {
  for(byte i = 0; i < 4; i++) {
    preset[i] = EEPROM.read(preset_number * 4 + i);
  }
}

void PresetManager::storePreset() {
  for(byte i = 0; i < 4; i++) {
    EEPROM.update(preset_number * 4 + i, preset[i]);
  }
}