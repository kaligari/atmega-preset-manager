#include "PresetManager.h"

void PresetManager::handleInput() {
  if(menu_state == 0) {
    if(encoder->check_ec_right() == 1) {
      if(preset_number < 99) {
        (preset_number)++;
      } else {
        preset_number = 0;
      }
      readPreset();
      digipot->setValue(0, preset[0]);
      digipot->setValue(1, preset[1]);
      redraw = 1;
    }
    if(encoder->check_ec_left() == 1) {
      if(preset_number > 0) {
        (preset_number)--;
      } else {
        preset_number = 99;
      }
      readPreset();
      digipot->setValue(0, preset[0]);
      digipot->setValue(1, preset[1]);
      redraw = 1;
    }
    if(encoder->check_ec_push() == 1) {
      menu_state = 1;
      submenu_state = 0; 
      redraw = 1;
    }
  }
  if(menu_state == 1) {
    if(encoder->check_ec_right() == 1) {
      if(submenu_state < submenu_size - 1) {
        submenu_state++;
      } else {
        submenu_state = 0;
      }      
      redraw = 1;
    }
    
    if(encoder->check_ec_left() == 1) {
      if(submenu_state > 0) {
        submenu_state--;
      } else {
        submenu_state = submenu_size - 1;
      }
      redraw = 1;
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
      redraw = 1;
    }
  }
  if(menu_state == 2) {
    if(encoder->check_ec_right() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT:
          if(preset[submenu[submenu_state].param1] < submenu[submenu_state].maxVal) {
            preset[submenu[submenu_state].param1]++;
            digipot->setValue(0, preset[0]);
            digipot->setValue(1, preset[1]);
            redraw = 1;
          }
          break;
        case ROUTE_DIALOG:
          submenu_dialog = !submenu_dialog;
          redraw = 1;
          break;
      }
    }
    if(encoder->check_ec_left() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT:
          if(preset[submenu[submenu_state].param1] > submenu[submenu_state].minVal) {
            preset[submenu[submenu_state].param1]--;
            digipot->setValue(0, preset[0]);
            digipot->setValue(1, preset[1]);
            redraw = 1;
          }
          break;
        case ROUTE_DIALOG:
          submenu_dialog = !submenu_dialog;
          redraw = 1;
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
            storePreset();
            menu_state = 0;
            submenu_state = 0;
          }
          if(submenu_dialog == ROUTE_DIALOG_NO) {
            readPreset();
            digipot->setValue(0, preset[0]);
            digipot->setValue(1, preset[1]);
            menu_state = 1;
          }
          break;
      }
      redraw = 1;
    }
  }
}