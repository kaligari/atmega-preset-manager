#ifndef MIDIControl_h
#define MIDIControl_h

#include <Arduino.h>
#include <MIDI.h>
#include "Memory.h"
#include "DigiPot.h"

// Define your transport
extern MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialMIDI;
// Define the MIDI interface
extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI;

class MIDIControl {
  private:
    Memory* memory;
    DigiPot* digipot;
    byte* preset_number;
    byte* preset;
    byte* redraw;
    int* debug;
  public:
    void init(byte* i_preset_number, byte* i_redraw, byte* i_preset, Memory* i_memory, DigiPot* i_digipot);
    void handle_input();
};

#endif