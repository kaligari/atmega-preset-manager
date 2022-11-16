#include "Encoder.h"

Encoder::Encoder(int clk, int dt, int btn) {
  CLK = clk;
  DT = dt;
  BTN = btn;
}

void Encoder::begin() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(BTN, INPUT_PULLUP);
}

void Encoder::readInput() {
  // if(is_ec_right == 1 || is_ec_left == 1) {
  //   return;
  // }
  int new_clk = digitalRead(CLK);
  if (new_clk != last_clk) {
    // noInterrupts();
    // There was a change on the CLK pin
    last_clk = new_clk;
    int dt_value = digitalRead(DT);
    
    if (new_clk == LOW && dt_value == HIGH) {
      // Serial.println("Right");
      is_ec_right = 1;
    } else if (new_clk == LOW && dt_value == LOW) {
      // Serial.println("Left");
      is_ec_left = 1;
    }
    delay(5);
  }

  if (digitalRead(BTN) == LOW) {
    is_ec_push = !is_ec_push;
    delay(300);
  }
}

byte Encoder::check_ec_right() {
  if(is_ec_right == 1) {
    is_ec_right = 0;
    return 1;
  } else {
    return 0;
  }
}

byte Encoder::check_ec_left() {
  if(is_ec_left == 1) {
    is_ec_left = 0;
    return 1;
  } else {
    return 0;
  }
}

byte Encoder::check_ec_push() {
  if(is_ec_push == 1) {
    is_ec_push = 0;
    return 1;
  } else {
    return 0;
  }
}