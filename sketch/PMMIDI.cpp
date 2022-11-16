#include "PresetManager.h"

void PresetManager::readMIDI() {
  if (MIDI.read(1)) {
      switch(MIDI.getType()) {
            case midi::ProgramChange:
              preset_number = MIDI.getData1() + 1;
              readPreset();
              digipot->setValue(0, preset[0]);
              digipot->setValue(1, preset[1]);
              redraw = 1;
              break;
            case midi::ControlChange:
              if(MIDI.getData1() == 27) {
                preset[0] = MIDI.getData2() * 2;
                digipot->setValue(0, preset[0]);
              }
              if(MIDI.getData1() == 7) {
                preset[1] = MIDI.getData2() * 2;
                digipot->setValue(1, preset[1]);
              }
              if(MIDI.getData1() == 2) {
                preset[1] = MIDI.getData2();
                redraw = 1;
              }
              if(MIDI.getData1() == 3) {
                preset[2] = MIDI.getData2();
                redraw = 1;
              }
              break;
            default:
              break;
        }
    }
}