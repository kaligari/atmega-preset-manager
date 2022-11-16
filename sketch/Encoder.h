#ifndef Encoder_h
#define Encoder_h

#include <Arduino.h>

class Encoder {
  private:
    int last_clk = HIGH;
    int CLK;
    int DT;
    int BTN;

    byte is_ec_right = 0;
    byte is_ec_left = 0;
    byte is_ec_push = 0;

  public:
    Encoder(int clk, int dt, int btn);
    void begin();
    void read_input();
    byte check_ec_right();
    byte check_ec_left();
    byte check_ec_push();
};

#endif