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
                preset[DELAY] = MIDI.getData2() * 2;
                // digipot->setValue(0, preset[0]);
                setDigiPots();
              }
              if(MIDI.getData1() == 7) {
                preset[FEEDBACK] = MIDI.getData2() * 2;
                setDigiPots();
              }
              if(MIDI.getData1() == 1) {
                preset[MIX] = MIDI.getData2();
                redraw = 1;
              }
              if(MIDI.getData1() == 2) {
                preset[DELAY] = MIDI.getData2();
                redraw = 1;
              }
              if(MIDI.getData1() == 3) {
                preset[FEEDBACK] = MIDI.getData2();
                redraw = 1;
              }
              break;
            default:
              break;
        }
    }
}