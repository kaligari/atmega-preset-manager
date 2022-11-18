#include "PresetManager.h"

void PresetManager::LCDBegin() {
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("Multiefekt");
  lcd->setCursor(0, 1);
  lcd->print("v1.3.2137");
  delay(1000);
  lcd->clear();
}

void PresetManager::drawNumber() {
  byte digit1 = preset_number / 10 * 4;
  byte digit2 = preset_number % 10 * 4;

  lcd->createChar(1, CC[digit1]);
  lcd->createChar(2, CC[digit1 + 1]);
  lcd->createChar(3, CC[digit1 + 2]);
  lcd->createChar(4, CC[digit1 + 3]);

  lcd->createChar(5, CC[digit2]);
  lcd->createChar(6, CC[digit2 + 1]);
  lcd->createChar(7, CC[digit2 + 2]);
  lcd->createChar(8, CC[digit2 + 3]);
  
  lcd->setCursor(0, 0);
  lcd->write(1);
  lcd->setCursor(1, 0);
  lcd->write(2);
  lcd->setCursor(0, 1);
  lcd->write(3);
  lcd->setCursor(1, 1);
  lcd->write(4);

  lcd->setCursor(2, 0);
  lcd->write(5);
  lcd->setCursor(3, 0);
  lcd->write(6);
  lcd->setCursor(2, 1);
  lcd->write(7);
  lcd->setCursor(3, 1);
  lcd->write(8);
}

void PresetManager::drawMenuHeader() {
  byte startChar = (10 - strlen(submenu[submenu_state].name)) / 2;
  lcd->setCursor(5 + startChar, 0);
  lcd->print(submenu[submenu_state].name);
  if(menu_state == MENU_PRESET_VIEW) {
    lcd->setCursor(4, 0);
    lcd->print("<");
    lcd->setCursor(15, 0);
    lcd->print(">");
  }
}

void PresetManager::drawMenuValue() {
  if(submenu[submenu_state].options > 0) {
    byte startChar = (10 - strlen(submenu[submenu_state].option[submenu_dialog])) / 2;
    lcd->setCursor(5 + startChar, 1);
    // lcd->print(submenu[submenu_state].option[submenu_dialog]);
    lcd->print(preset[submenu[submenu_state].param1]);
  } else {
    byte current_value = preset[submenu[submenu_state].param1];
    byte digitLength = preset[submenu[submenu_state].param1];
    byte count = 0;
    do {
      digitLength /= 10;
      ++count;
    } while (digitLength != 0);
    byte startChar = (10 - count) / 2;
    lcd->setCursor(5 + startChar, 1);
    lcd->print(preset[submenu[submenu_state].param1]);
  }
  if(menu_state == MENU_PRESET_EDIT) {
    lcd->setCursor(4, 1);
    lcd->print("<");
    lcd->setCursor(15, 1);
    lcd->print(">");
  }
}

void PresetManager::drawMainView() {
  lcd->setCursor(5, 0);
  lcd->print("Mix Dly Fbk");
  lcd->setCursor(5, 1);
  lcd->print(preset[0]);
  lcd->setCursor(9, 1);
  lcd->print(preset[1]);
  lcd->setCursor(13, 1);
  lcd->print(preset[2]);
}

void PresetManager::refreshScreen() {
  if(redraw == 0) {
    return;
  }
  lcd->clear();
  drawNumber();
  if(menu_state == MENU_MAIN_VIEW) {
    drawMainView();
  }
  if(menu_state == MENU_PRESET_VIEW || menu_state == MENU_PRESET_EDIT) {
    drawMenuHeader();
    drawMenuValue();
  }
  redraw = 0;
}