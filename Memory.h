#ifndef Memory_h
#define Memory_h

#include <Arduino.h>
#include <EEPROM.h>
#include "struct.h"

class Memory {
  private:
    byte* preset_number;
    byte* preset;
  public:
    void init(byte* i_preset_number, byte* i_preset);
    void readPreset();
    void storePreset();
};

#endif