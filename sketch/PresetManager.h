#ifndef PresetManager_h
#define PresetManager_h

// possible manu states
#define MENU_MAIN_VIEW 0
#define MENU_PRESET_VIEW 1
#define MENU_PRESET_EDIT 2

// route types
#define ROUTE_PRESET_EDIT_DIGIPOTS 0
#define ROUTE_PRESET_EDIT_RELAYS 1
#define ROUTE_PRESET_STORE 2
#define ROUTE_GO_TO_ROUTE 3

#define ROUTE_DIALOG_NO 0
#define ROUTE_DIALOG_YES 1

#define MIX 0
#define DELAY 1
#define FEEDBACK 2

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <MIDI.h>
#include "Encoder.h"
#include "DigiPot.h"
#include "struct.h"

// Define your transport
extern MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialMIDI;
// Define the MIDI interface
extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI;

class PresetManager {
  public:
    PresetManager(LiquidCrystal* i_lcd, Encoder* i_encoder, DigiPot* i_digipot);
    void begin();
    void loop();
  private:
    LiquidCrystal* lcd;
    Encoder* encoder;
    DigiPot* digipot;

    byte preset_number = 0;
    byte preset[4] = { 0, 0, 0, 0 };
    byte redraw = 0;
    byte menu_state = 0;
    byte submenu_state = 0;
    byte submenu_size = 0;
    byte submenu_dialog = ROUTE_DIALOG_YES;
    struct menuItem submenu[7];

    // char* switchMenu[3] = ["Clean", "Crunch", "Solo"];
    // char* saveMenu[3] = ["Yes", "No"];

    void handleInput();
    void setDigiPots();

    // EEPROM
    void readPreset();
    void storePreset();

    // MIDI
    void readMIDI();

    // LCD
    void LCDBegin();
    void drawNumber();
    void drawMenuHeader();
    void drawMenuValue();
    void drawMainView();
    void refreshScreen();

    byte CC[40][8] = {
      // 0
      {
        B00111,
        B01111,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100
      }, {
        B11100,
        B11110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111
      }, {
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B01111,
        B00111
      }, {
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B11110,
        B11100
      },
      // 1
      {
        B00000,
        B00001,
        B00011,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000
      }, {
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100
      }, {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00011
      }, {
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11111,
        B11111
      },
      // 2
      {
        B00111,
        B01110,
        B11100,
        B11100,
        B11100,
        B00000,
        B00000,
        B00000
      }, {
        B11100,
        B01110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B01110
      }, {
        B00000,
        B00000,
        B00001,
        B00011,
        B00111,
        B01110,
        B11111,
        B11111
      }, {
        B11100,
        B11000,
        B10000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
      },
      // 3
      {
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
        B00001
      }, {
        B11111,
        B11111,
        B00111,
        B01110,
        B11100,
        B11000,
        B10000,
        B11000
      }, {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11100,
        B01111,
        B00111
      }, {
        B01110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00110,
        B11110,
        B11000
      },
      // 4
      {
        B00000,
        B00000,
        B00000,
        B00001,
        B00011,
        B00111,
        B01110,
        B11100
      }, {
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100
      }, {
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
      }, {
        B11111,
        B11111,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100
      },
      // 5
      {
        B11111,
        B11111,
        B11100,
        B11100,
        B11111,
        B11111,
        B11111,
        B00000
      }, {
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B11100,
        B01110,
        B00111
      }, {
        B00000,
        B00000,
        B00000,
        B00000,
        B11100,
        B11100,
        B01111,
        B00111
      }, {
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B01110,
        B11100,
        B11000
      },
      // 6
      {
        B00011,
        B00111,
        B01110,
        B01100,
        B11100,
        B11100,
        B11100,
        B11111
      }, {
        B11100,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11100
      }, {
        B11111,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B01111,
        B00111
      }, {
        B11110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B11110,
        B11100
      },
      // 7
      {
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
        B00011
      }, {
        B11111,
        B11111,
        B00111,
        B00111,
        B01110,
        B11100,
        B11000,
        B10000
      }, {
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111
      }, {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
      },
      // 8
      {
        B00111,
        B01111,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B01111
      }, {
        B11100,
        B11110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B11110
      }, {
        B01111,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B01111,
        B00111
      }, {
        B11110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B11110,
        B11100
      },
      // 9
      {
        B00111,
        B01111,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B01111
      }, {
        B11100,
        B11110,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B11110
      }, {
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B00111
      }, {
        B11111,
        B00111,
        B00111,
        B00111,
        B01110,
        B01110,
        B11100,
        B11000
      }
    };
};

#endif