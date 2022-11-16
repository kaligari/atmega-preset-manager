#ifndef PresetManager_h
#define PresetManager_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <MIDI.h>
#include "Encoder.h"
#include "DigiPot.h"

// Define your transport
extern MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialMIDI;
// Define the MIDI interface
extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI;

class PresetManager {
  public:
    PresetManager(uint8_t lcd_rs, uint8_t lcd_enable, uint8_t lcd_d0, uint8_t lcd_d1,
      uint8_t lcd_d2, uint8_t lcd_d3, byte encoder_clk, byte encoder_dt,
      byte encoder_btn, byte digipot_clk, byte digipot_miso, byte digipot_mosi,
      byte digipot_cs, byte digipot_ready);
    void begin();
    void loop();
  private:
    LiquidCrystal* lcd;
    Encoder* encoder;
    DigiPot* digipot;

    byte preset_number = 0;
    byte preset[4] = { 0, 0, 0, 0 };
    byte redraw = 0;

    // EEPROM
    void readPreset();
    void storePreset();

    // MIDI
    void readMIDI();

    // LCD
    void LCDBegin();
    void drawNumber();
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