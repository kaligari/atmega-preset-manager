#ifndef DigiPot_h
#define DigiPot_h

#include <Arduino.h>
#include <SPI.h>

class DigiPot {
  private:
    int CLK;
    int MISO;
    int MOSI;
    int CS;
    int READY;
    byte* preset;
    byte* redraw;
    void send_frame(byte instruction, byte data1 = 0, byte data2 = 0);
  public:
    void init(int clk, int miso, int mosi, int cs, int ready, byte* i_preset, byte* i_redraw);
    void set_value(byte digipot, byte value);
    void set_value_up();
    void set_value_down();
    void wake_up();
    void reset();
};

#endif