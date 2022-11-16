#ifndef PresetManager_h
#define PresetManager_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Encoder.h"
#include "DigiPot.h"

class PresetManager {
  private:
    LiquidCrystal* lcd;
    Encoder* encoder;
    DigiPot* digipot;

    byte preset_number = 0;
    byte preset[4] = { 0, 0, 0, 0 };
  public:
    PresetManager(uint8_t lcd_rs, uint8_t lcd_enable, uint8_t lcd_d0, uint8_t lcd_d1,
      uint8_t lcd_d2, uint8_t lcd_d3, byte encoder_clk, byte encoder_dt,
      byte encoder_btn, byte digipot_clk, byte digipot_miso, byte digipot_mosi,
      byte digipot_cs, byte digipot_ready);
    void begin();
    void loop();
};

#endif