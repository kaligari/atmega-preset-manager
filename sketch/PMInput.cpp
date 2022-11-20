#include "PresetManager.h"

void PresetManager::handleInput() {
  /**
   * MENU_MAIN_VIEW
   **/
  if(menu_state == MENU_MAIN_VIEW) {
    if(encoder->check_ec_right() == 1) {
      if(preset_number < 99) {
        (preset_number)++;
      } else {
        preset_number = 0;
      }
      readPreset();
      setDigiPots();
      setRelays();
      redraw = 1;
    }
    if(encoder->check_ec_left() == 1) {
      if(preset_number > 0) {
        (preset_number)--;
      } else {
        preset_number = 99;
      }
      readPreset();
      setDigiPots();
      setRelays();
      redraw = 1;
    }
    if(encoder->check_ec_push() == 1) {
      menu_state = MENU_PRESET_VIEW;
      submenu_state = 0; 
      redraw = 1;
    }
  }

  /**
   * MENU_PRESET_VIEW
   **/
  if(menu_state == MENU_PRESET_VIEW) {
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
        case ROUTE_GO_TO_ROUTE:
          menu_state = submenu[submenu_state].param1;
          readPreset();
          setDigiPots();
          setRelays();
          break;
        default:
          menu_state = MENU_PRESET_EDIT;
          submenu_dialog = 0;
        
      }
      redraw = 1;
    }
  }

  /**
   * MENU_PRESET_EDIT
   **/
  if(menu_state == MENU_PRESET_EDIT) {
    if(encoder->check_ec_right() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT_DIGIPOTS:
          preset[submenu[submenu_state].param1]++;
          setDigiPots();
          redraw = 1;
          break;
        case ROUTE_PRESET_EDIT_RELAYS:
          if(submenu_dialog < submenu[submenu_state].options - 1) {
            submenu_dialog++;
          } else {
            submenu_dialog = 0;
          }
          // set relays bits in to preset byte
          preset[submenu[submenu_state].param1] = ((submenu_dialog & submenu[submenu_state].bit_mask) << submenu[submenu_state].bit_shift) | (preset[submenu[submenu_state].param1] & ~(submenu[submenu_state].bit_mask << submenu[submenu_state].bit_shift));
          setRelays();
          redraw = 1;
          break;
        case ROUTE_PRESET_STORE:
          submenu_dialog = !submenu_dialog;
          redraw = 1;
          break;
      }
    }
    if(encoder->check_ec_left() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_EDIT_DIGIPOTS:
          preset[submenu[submenu_state].param1]--;
          setDigiPots();
          redraw = 1;
          break;
        case ROUTE_PRESET_EDIT_RELAYS:
          if(submenu_dialog > 0) {
            submenu_dialog--;
          } else {
            submenu_dialog = submenu[submenu_state].options - 1;
          }
          // set relays bits in to preset byte
          preset[submenu[submenu_state].param1] = ((submenu_dialog & submenu[submenu_state].bit_mask) << submenu[submenu_state].bit_shift) | (preset[submenu[submenu_state].param1] & ~(submenu[submenu_state].bit_mask << submenu[submenu_state].bit_shift));
          setRelays();
          redraw = 1;
          break;
        case ROUTE_PRESET_STORE:
          submenu_dialog = !submenu_dialog;
          redraw = 1;
          break;
      }
    }
    if(encoder->check_ec_push() == 1) {
      switch(submenu[submenu_state].type) {
        case ROUTE_PRESET_STORE:
          if(submenu_dialog == ROUTE_DIALOG_YES) {
            storePreset();
            menu_state = MENU_MAIN_VIEW;
            submenu_state = 0;
          }
          if(submenu_dialog == ROUTE_DIALOG_NO) {
            readPreset();
            setDigiPots();
            setRelays();
            menu_state = MENU_PRESET_VIEW;
          }
          break;
        default:
          menu_state = MENU_PRESET_VIEW;
          break;
      }
      redraw = 1;
    }
  }
}