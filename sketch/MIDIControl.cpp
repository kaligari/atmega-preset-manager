#include "midi_Defs.h"
#include "MIDIControl.h"

void static BlinkLed(byte num)         // Basic blink function
{
    for (byte i=0;i<num;i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN,LOW);
        delay(50);
    }
}

void MIDIControl::init(byte* i_preset_number, byte* i_redraw, byte* i_preset, Memory* i_memory, DigiPot* i_digipot) {
  preset_number = i_preset_number;
  redraw = i_redraw;
  preset = i_preset;
  memory = i_memory;
  digipot = i_digipot;

  pinMode(LED_BUILTIN, OUTPUT);
  MIDI.begin(1);  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  // MIDI.setHandleProgramChange(changeProgram);
}

void MIDIControl::handle_input() {
  if (MIDI.read(1))                    // If we have received a message
    {
      switch(MIDI.getType()) {
            case midi::ProgramChange:
              // BlinkLed(MIDI.getData1());
              // preset[0] = MIDI.getChannelFromStatusByte(12); // MIDI.getData1();
              *preset_number = MIDI.getData1() + 1;
              memory->readPreset();
              digipot->set_value(0, preset[0]);
              digipot->set_value(1, preset[1]);
              // preset[0] = MIDI.getData1();
              // preset[1] = MIDI.getData2();
              *redraw = 1;
              break;
            case midi::ControlChange:
              if(MIDI.getData1() == 27) {
                preset[0] = MIDI.getData2() * 2;
                digipot->set_value(0, preset[0]);
              }
              if(MIDI.getData1() == 7) {
                preset[1] = MIDI.getData2() * 2;
                digipot->set_value(1, preset[1]);
              }
              if(MIDI.getData1() == 2) {
                preset[1] = MIDI.getData2();
                *redraw = 1;
              }
              if(MIDI.getData1() == 3) {
                preset[2] = MIDI.getData2();
                *redraw = 1;
              }
              break;
            default:
              break;
        }
    }
}