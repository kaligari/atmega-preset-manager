#include <LiquidCrystal.h>
#include "PresetManager.h"

PresetManager::PresetManager(LiquidCrystal* i_lcd, Encoder* i_encoder, DigiPot* i_digipot, byte i_relay_1_pin, byte i_relay_2_pin) {
    lcd = i_lcd;
    encoder = i_encoder;
    digipot = i_digipot;
    relay_1_pin = i_relay_1_pin;
    relay_2_pin = i_relay_2_pin;

    pinMode(relay_1_pin, OUTPUT);
    pinMode(relay_2_pin, OUTPUT);
  }

void PresetManager::begin() {
  LCDBegin();
  encoder->begin();
  MIDI.begin(1);
  
  digipot->begin();
  // digipot->reset();
  digipot->wakeUp();
  digipot->wakeUp();

  submenu[0].type = ROUTE_PRESET_EDIT_DIGIPOTS;
  submenu[0].name = "Mix";
  submenu[0].param1 = MIX;

  submenu[1].type = ROUTE_PRESET_EDIT_DIGIPOTS;
  submenu[1].name = "Delay";
  submenu[1].param1 = DELAY;

  submenu[2].type = ROUTE_PRESET_EDIT_DIGIPOTS;
  submenu[2].name = "Feedback";
  submenu[2].param1 = FEEDBACK;

  submenu[3].type = ROUTE_PRESET_EDIT_RELAYS;
  submenu[3].name = " Amp Ch.";
  submenu[3].presentation = OPTIONS;
  submenu[3].param1 = 3;  // offset preset byte to edit 
  submenu[3].bit_shift = 6;  // bite shift from preset byte
  submenu[3].bit_mask = B00000011;
  submenu[3].options = 3; // amount of options
  submenu[3].option[0] = "Clean";    // B00
  submenu[3].option[1] = "Crunch";   // B01
  submenu[3].option[2] = "Lead";     // B10

  submenu[4].type = ROUTE_PRESET_EDIT_RELAYS;
  submenu[4].name = "Ctrl #1";
  submenu[4].presentation = OPTIONS;
  submenu[4].param1 = 3;
  submenu[4].bit_shift = 0;
  submenu[4].bit_mask = B00000111;
  submenu[4].options = 4;
  submenu[4].option[0] = "Off";
  submenu[4].option[1] = "Mix";
  submenu[4].option[2] = "Delay";
  submenu[4].option[3] = "Feedback";

  submenu[5].type = ROUTE_PRESET_EDIT_RELAYS;
  submenu[5].name = "Ctrl #2";
  submenu[5].presentation = OPTIONS;
  submenu[5].param1 = 3;
  submenu[5].bit_shift = 3;
  submenu[5].bit_mask = B00000111;
  submenu[5].options = 4;
  submenu[5].option[0] = "Off";
  submenu[5].option[1] = "Mix";
  submenu[5].option[2] = "Delay";
  submenu[5].option[3] = "Feedback";

  submenu[6].type = ROUTE_PRESET_STORE;
  submenu[6].name = "Store";
  submenu[6].presentation = OPTIONS;
  submenu[6].param1 = 0;
  submenu[6].options = 2;
  submenu[6].option[0] = "Yes";
  submenu[6].option[1] = "No";

  submenu[7].name = "Return";
  submenu[7].type = ROUTE_GO_TO_ROUTE;
  submenu[7].param1 = MENU_MAIN_VIEW;

  submenu_size = sizeof(submenu)/sizeof(menuItem);

  readPreset();
  setDigiPots();
  setRelays();

  redraw = 1;
}

void PresetManager::setDigiPots() {
  
  // Daisy chaining - device 2
  digipot->setValue(0, preset[FEEDBACK]);

  // Daisy chaining - device 1
  digipot->setValue(1, preset[DELAY]);
  digipot->setValue(0, preset[MIX]);
}

/*
 * Set relays pin state based on config byte value (3)
 * B00110000
 *    ||
 *    ||-> relays pins
 */
void PresetManager::setRelays() {
  digitalWrite(relay_1_pin, preset[3] >> 6 & B01);
  digitalWrite(relay_2_pin, preset[3] >> 7 & B01);
}

void PresetManager::loop() {
  readMIDI();
  encoder->readInput();
  handleInput();
  refreshScreen();
}