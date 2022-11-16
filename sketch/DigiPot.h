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
    void sendFrame(byte instruction, byte data1 = 0, byte data2 = 0);
  public:
    DigiPot(int clk, int miso, int mosi, int cs, int ready);
    void begin();
    void setValue(byte digipot, byte value);
    void valueUp();
    void valueDown();
    void wakeUp();
    void reset();
};

#endif