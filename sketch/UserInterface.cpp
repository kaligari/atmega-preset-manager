#include "UserInterface.h"

void UserInterface::init(LiquidCrystal* i_lcd, Encoder* i_encoder, Memory* i_memory, byte* i_preset_number, byte* i_preset, byte* i_redraw, DigiPot* i_digipot) {
  lcd = i_lcd;
  encoder = i_encoder;
  memory = i_memory;
  digipot = i_digipot;
  preset_number = i_preset_number;
  preset = i_preset;
  redraw = i_redraw;

  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("Multiefekt");
  lcd->setCursor(0, 1);
  lcd->print("v1.2.2137");
  delay(1000);
  lcd->clear();

  *redraw = 1;

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

  memory->readPreset();
  digipot->set_value(0, preset[0]);
  digipot->set_value(1, preset[1]);
}

void UserInterface::draw_number(byte number) {
  byte digit1 = number / 10 * 4;
  byte digit2 = number % 10 * 4;

  lcd->createChar(1, CC[digit1]);
  lcd->createChar(2, CC[digit1 + 1]);
  lcd->createChar(3, CC[digit1 + 2]);
  lcd->createChar(4, CC[digit1 + 3]);

  lcd->createChar(5, CC[digit2]);
  lcd->createChar(6, CC[digit2 + 1]);
  lcd->createChar(7, CC[digit2 + 2]);
  lcd->createChar(8, CC[digit2 + 3]);
  
  lcd->setCursor(0, 0);
  lcd->write(1);
  lcd->setCursor(1, 0);
  lcd->write(2);
  lcd->setCursor(0, 1);
  lcd->write(3);
  lcd->setCursor(1, 1);
  lcd->write(4);

  lcd->setCursor(2, 0);
  lcd->write(5);
  lcd->setCursor(3, 0);
  lcd->write(6);
  lcd->setCursor(2, 1);
  lcd->write(7);
  lcd->setCursor(3, 1);
  lcd->write(8);

}

void UserInterface::draw_menu_1_line() {
  byte startChar = (10 - strlen(submenu[submenu_state].name)) / 2;
  lcd->setCursor(5 + startChar, 0);
  lcd->print(submenu[submenu_state].name);
  if(menu_state == 1) {
    lcd->setCursor(4, 0);
    lcd->print("<");
    lcd->setCursor(15, 0);
    lcd->print(">");
  }
}

void UserInterface::draw_menu_2_line_value() {
  if(submenu[submenu_state].type != ROUTE_PRESET_EDIT) {
    return;
  }
  byte current_value = preset[submenu[submenu_state].param1];
  byte digitLength = preset[submenu[submenu_state].param1];
  byte count = 0;
  do {
    digitLength /= 10;
    ++count;
  } while (digitLength != 0);

  byte startChar = (10 - count) / 2;
  lcd->setCursor(5 + startChar, 1);
  lcd->print(preset[submenu[submenu_state].param1]);
  if(menu_state == 2 && current_value > submenu[submenu_state].minVal) {
    lcd->setCursor(4, 1);
    lcd->print("<");
  }
  if(menu_state == 2 && current_value < submenu[submenu_state].maxVal) {
    lcd->setCursor(15, 1);
    lcd->print(">");
  }
}

void UserInterface::draw_menu_2_line_dialog() {
  if(submenu[submenu_state].type != ROUTE_DIALOG) {
    return;
  }
  if(menu_state == 2 && submenu_dialog == ROUTE_DIALOG_YES) {
    lcd->setCursor(8, 1);
    lcd->print("Yes");
  }
  if(menu_state == 2 && submenu_dialog == ROUTE_DIALOG_NO) {
    lcd->setCursor(8, 1);
    lcd->print("No");
  }
}

void UserInterface::draw_main_view() {
  lcd->setCursor(5, 0);
  lcd->print("Dly Fbk Mix");
  lcd->setCursor(5, 1);
  lcd->print(preset[0]);
  lcd->setCursor(9, 1);
  lcd->print(preset[1]);
  lcd->setCursor(13, 1);
  lcd->print(preset[2]);
}

void UserInterface::handle_input() {
  if(menu_state == 0) {
    if(encoder->check_ec_right() == 1) {
      if(*preset_number < 99) {
        (*preset_number)++;
      } else {
        *preset_number = 0;
      }
      memory->readPreset();
      digipot->set_value(0, preset[0]);
      digipot->set_value(1, preset[1]);
      *redraw = 1;
    }
    if(encoder->check_ec_left() == 1) {
      if(*preset_number > 0) {
        (*preset_number)--;
      } else {
        *preset_number = 99;
      }
      memory->readPreset();
      digipot->set_value(0, preset[0]);
      digipot->set_value(1, preset[1]);
      *redraw = 1;
    }
    if(encoder->check_ec_push() == 1) {
      menu_state = 1;
      submenu_state = 0; 
      *redraw = 1;
    }
  }
  if(menu_state == 1) {
    if(encoder->check_ec_right() == 1) {
      if(submenu_state < submenu_size - 1) {
        submenu_state++;
      } else {
        submenu_state = 0;
      }      
      *redraw = 1;
    }
    
    if(encoder->check_ec_left() == 1) {
      if(submenu_state > 0) {
        submenu_state--;
      } else {
        submenu_state = submenu_size - 1;
      }
      *redraw = 1;
    }
    if(encoder->check_ec_push() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT:
          menu_state = 2;
          break;
        case ROUTE_GO_TO_MENU:
          menu_state = 0;
          break;
        case ROUTE_DIALOG:
          menu_state = 2;
          submenu_dialog = ROUTE_DIALOG_YES;
          break;
      }
      *redraw = 1;
    }
  }
  if(menu_state == 2) {
    if(encoder->check_ec_right() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT:
          if(preset[submenu[submenu_state].param1] < submenu[submenu_state].maxVal) {
            preset[submenu[submenu_state].param1]++;
            digipot->set_value(0, preset[0]);
            digipot->set_value(1, preset[1]);
            *redraw = 1;
          }
          break;
        case ROUTE_DIALOG:
          submenu_dialog = !submenu_dialog;
          *redraw = 1;
          break;
      }
    }
    if(encoder->check_ec_left() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT:
          if(preset[submenu[submenu_state].param1] > submenu[submenu_state].minVal) {
            preset[submenu[submenu_state].param1]--;
            digipot->set_value(0, preset[0]);
            digipot->set_value(1, preset[1]);
            *redraw = 1;
          }
          break;
        case ROUTE_DIALOG:
          submenu_dialog = !submenu_dialog;
          *redraw = 1;
          break;
      }
    }
    if(encoder->check_ec_push() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT:
          menu_state = 1;
          break;
        case ROUTE_DIALOG:
          if(submenu_dialog == ROUTE_DIALOG_YES) {
            memory->storePreset();
            menu_state = 0;
            submenu_state = 0;
          }
          if(submenu_dialog == ROUTE_DIALOG_NO) {
            memory->readPreset();
            digipot->set_value(0, preset[0]);
            digipot->set_value(1, preset[1]);
            menu_state = 1;
          }
          break;
      }
      *redraw = 1;
    }
  }
}

void UserInterface::refresh_screen() {
  if(*redraw == 0) {
    return;
  }
  lcd->clear();
  draw_number(*preset_number);
  if(menu_state == 0) {
    draw_main_view();
    // draw_debug();
  }
  if(menu_state == 1 || menu_state == 2) {
    draw_menu_1_line();
    draw_menu_2_line_value();
    draw_menu_2_line_dialog();
  }
  *redraw = 0;
}