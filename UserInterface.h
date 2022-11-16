#ifndef UserInterface_h
#define UserInterface_h

#define ROUTE_PRESET_EDIT 0
#define ROUTE_GO_TO_MENU 1
#define ROUTE_GO_TO_SUBMENU 2
#define ROUTE_DIALOG 3

#define ROUTE_DIALOG_NO 0
#define ROUTE_DIALOG_YES 1

#include <LiquidCrystal.h>
#include "Encoder.h"
#include "Memory.h"
#include "DigiPot.h"
#include "struct.h"

class UserInterface {
  public:
    void init(LiquidCrystal* i_lcd, Encoder* i_encoder, Memory* i_memory, byte* i_preset_number, byte* i_preset, byte* i_redraw, DigiPot* i_digipot);
    void draw_number(byte number);
    void draw_menu_1_line();
    void draw_menu_2_line_value();
    void draw_menu_2_line_dialog();
    void draw_main_view();
    void refresh_screen();
    void handle_input();

  private:
    LiquidCrystal* lcd;
    Encoder* encoder;
    Memory* memory;
    DigiPot* digipot;
    byte* preset_number;
    byte* preset;
    byte* redraw;

    byte menu_state = 0;
    byte submenu_state = 0;
    byte submenu_size = 0;
    byte submenu_dialog = ROUTE_DIALOG_YES;

    struct menuItem submenu[6];

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