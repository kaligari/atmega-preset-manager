#include "PresetManager.h"

#define LCD_RS 6
#define LCD_ENABLE 5
#define LCD_D0 10
#define LCD_D1 9
#define LCD_D2 8
#define LCD_D3 7
#define ENCODER_CLK 2
#define ENCODER_DT  3
#define ENCODER_BTN 4
#define DIGIPOT_CLK 13
#define DIGIPOT_MISO 12
#define DIGIPOT_MOSI  11
#define DIGIPOT_CS  A0
#define DIGIPOT_READY A1

PresetManager presetManager(LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3, ENCODER_CLK, ENCODER_DT, ENCODER_BTN, DIGIPOT_CLK, DIGIPOT_MISO, DIGIPOT_MOSI, DIGIPOT_CS, DIGIPOT_READY);

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Serial.begin(31250);
  presetManager.begin();
}

void loop() {
  presetManager.loop();
}
