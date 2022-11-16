#include "DigiPot.h"

DigiPot::DigiPot(int clk, int miso, int mosi, int cs, int ready) {
  CLK = clk;
  MISO = miso;
  MOSI = mosi;
  CS = cs;
  READY = ready;
}

void DigiPot::begin() {
  pinMode(CLK, OUTPUT);
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(READY, INPUT);
  digitalWrite(CS, HIGH);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  wake_up();
}

void DigiPot::send_frame(byte instruction, byte data1 = 0, byte data2 = 0) {
  noInterrupts();
  digitalWrite(CS, LOW);
  SPI.transfer(instruction);
  SPI.transfer(data1);
  SPI.transfer(data2);
  delay(10);
  digitalWrite(CS, HIGH);
  interrupts();
}

void DigiPot::reset() {
  send_frame(0x90);
}

void DigiPot::wake_up() {
  send_frame(0x10);
}

void DigiPot::set_value(byte digipot, byte value) {
  wake_up();
  send_frame(0x40 + digipot, 0, value);
}

void DigiPot::set_value_up() {
  send_frame(0x70);
}

void DigiPot::set_value_down() {
  send_frame(0xF0);
}