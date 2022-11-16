#include "PresetManager.h"

PresetManager::PresetManager(uint8_t lcd_rs, uint8_t lcd_enable, uint8_t lcd_d0, uint8_t lcd_d1,
      uint8_t lcd_d2, uint8_t lcd_d3, byte encoder_clk, byte encoder_dt,
      byte encoder_btn, byte digipot_clk, byte digipot_miso, byte digipot_mosi,
      byte digipot_cs, byte digipot_ready) {

    LiquidCrystal* lcd(lcd_rs, lcd_enable, lcd_d0, lcd_d1, lcd_d2, lcd_d3);
    Encoder encoder(encoder_clk, encoder_dt, encoder_btn);
    DigiPot digipot(digipot_clk, digipot_miso, digipot_mosi, digipot_cs, digipot_ready);
  }

void PresetManager::begin() {
  // LCD
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("Multiefekt");
  lcd->setCursor(0, 1);
  lcd->print("v1.2.2137");
  delay(1000);
  lcd->clear();
  
  // Encoder
  encoder->begin();
}