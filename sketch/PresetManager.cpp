#include <LiquidCrystal.h>
#include "PresetManager.h"

PresetManager::PresetManager(LiquidCrystal* i_lcd, Encoder* i_encoder, DigiPot* i_digipot) {
    
    lcd = i_lcd;
    encoder = i_encoder;
    digipot = i_digipot;
  }

void PresetManager::begin() {
  LCDBegin();
  encoder->begin();
  MIDI.begin(1);
  
  digipot->begin();
  // digipot->reset();
  // digipot->wake_up();

  submenu[0].name = "Delay";
  submenu[0].type = ROUTE_PRESET_EDIT;
  submenu[0].param1 = 0;
  submenu[0].minVal = 0;
  submenu[0].maxVal = 255;

  submenu[1].name = "Feedback";
  submenu[1].type = ROUTE_PRESET_EDIT;
  submenu[1].param1 = 1;
  submenu[1].minVal = 0;
  submenu[1].maxVal = 255;

  submenu[2].name = "Mix";
  submenu[2].type = ROUTE_PRESET_EDIT;
  submenu[2].param1 = 2;
  submenu[2].minVal = 0;
  submenu[2].maxVal = 255;

  submenu[3].name = "Channel";
  submenu[3].type = ROUTE_PRESET_EDIT;
  submenu[3].param1 = 3;
  submenu[3].minVal = 0;
  submenu[3].maxVal = 16;

  submenu[4].name = "Store";
  submenu[4].type = ROUTE_DIALOG;
  submenu[4].param1 = 0;

  submenu[5].name = "Return";
  submenu[5].type = ROUTE_GO_TO_MENU;
  submenu[5].param1 = 0;

  submenu_size = sizeof(submenu)/sizeof(menuItem);

  readPreset();
  digipot->setValue(0, preset[0]);
  digipot->setValue(1, preset[1]);

  redraw = 1;
}

void PresetManager::loop() {
  readMIDI();
  encoder->readInput();
  handleInput();
  refreshScreen();
}