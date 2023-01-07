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

void PresetManager::resetPresets() {
  for(byte preset = 0; preset < 100; preset++) {
    EEPROM.update(preset * 4 + 0, 128);
    EEPROM.update(preset * 4 + 1, 128);
    EEPROM.update(preset * 4 + 2, 128);
    EEPROM.update(preset * 4 + 3, 0);
  }
}

// void PresetManager::setPresetWithMask(byte value, byte mask) {
//   preset[3] = value | mask;
// }

// byte PresetManager::readPresetWithMask(byte mask) {
//   return preset[3] | mask;
// }