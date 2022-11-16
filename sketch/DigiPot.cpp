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
}

void DigiPot::sendFrame(byte instruction, byte data1 = 0, byte data2 = 0) {
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
  sendFrame(0x90);
}

void DigiPot::wakeUp() {
  sendFrame(0x10);
}

void DigiPot::setValue(byte digipot, byte value) {
  wakeUp();
  sendFrame(0x40 + digipot, 0, value);
}

void DigiPot::valueUp() {
  sendFrame(0x70);
}

void DigiPot::valueDown() {
  sendFrame(0xF0);
}