#include "PresetManager.h"

void PresetManager::readMIDI() {
  if (MIDI.read(1)) {
      switch(MIDI.getType()) {
            case midi::ProgramChange:
              preset_number = MIDI.getData1() + 1;
              readPreset();
              setDigiPots();
              redraw = 1;
              break;
            case midi::ControlChange:
              if(MIDI.getData1() == 27) {
                byte ctrl_config = (preset[3] >> 0) & B111;
                if(ctrl_config == 0 || ctrl_config > DIGIPOTS_TOTAL) {
                  return;
                }
                preset[ctrl_config - 1] = MIDI.getData2() * 2;
                setDigiPots();
                if(menu_state == MENU_PRESET_EDIT || menu_state == MENU_PRESET_VIEW) {
                  redraw = 1;
                }
              }
              if(MIDI.getData1() == 7) {
                byte ctrl_config = (preset[3] >> 3) & B111;
                if(ctrl_config == 0 || ctrl_config > DIGIPOTS_TOTAL) {
                  return;
                }
                preset[ctrl_config - 1] = MIDI.getData2() * 2;
                setDigiPots();
                if(menu_state == MENU_PRESET_EDIT || menu_state == MENU_PRESET_VIEW) {
                  redraw = 1;
                }
              }
              // Control change
              // if(MIDI.getData1() == 1) {
              //   preset[MIX] = MIDI.getData2();
              //   redraw = 1;
              // }
              // if(MIDI.getData1() == 2) {
              //   preset[DELAY] = MIDI.getData2();
              //   redraw = 1;
              // }
              // if(MIDI.getData1() == 3) {
              //   preset[FEEDBACK] = MIDI.getData2();
              //   redraw = 1;
              // }
              break;
            default:
              break;
        }
    }
}