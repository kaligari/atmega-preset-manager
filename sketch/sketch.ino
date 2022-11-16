#include "UserInterface.h"
#include "Encoder.h"
#include "Memory.h"
#include "MIDIControl.h"
#include "DigiPot.h"
#include <LiquidCrystal.h>

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

byte preset_number = 0;
byte preset[4] = { 0, 0, 0, 0 };
byte redraw = 0;
int debug[2] = { 999, 999 };

Encoder encoder(ENCODER_CLK, ENCODER_DT, ENCODER_BTN);
UserInterface ui;
Memory memory;
MIDIControl midi_c;
DigiPot digipot(DIGIPOT_CLK, DIGIPOT_MISO, DIGIPOT_MOSI, DIGIPOT_CS, DIGIPOT_READY);
LiquidCrystal lcd(6, 5, 10, 9, 8, 7);
PresetManager presetManager(LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3, ENCODER_CLK, ENCODER_DT, ENCODER_BTN, DIGIPOT_CLK, DIGIPOT_MISO, DIGIPOT_MOSI, DIGIPOT_CS, DIGIPOT_READY);

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Serial.begin(31250);
  // memory.init(&preset_number, preset);
  encoder.begin();
  digipot.init();
  ui.init(&lcd, &encoder, &memory, &preset_number, preset, &redraw, &digipot);
  midi_c.init(&preset_number, &redraw, preset, &memory, &digipot);

  // digipot.set_value(10);
  digipot.reset();
  digipot.wake_up();
}

void loop() {
  midi_c.handle_input();
  encoder.read_input();
  ui.handle_input();
  ui.refresh_screen();
}
