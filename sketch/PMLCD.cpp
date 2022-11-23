#include "PresetManager.h"

void PresetManager::LCDBegin() {
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("Shaley Dly/Sw");
  lcd->setCursor(0, 1);
  lcd->print("v1.0.2137");
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
  if(menu_state == MENU_PRESET_EDIT) {
    lcd->setCursor(4, 1);
    lcd->print("<");
    lcd->setCursor(15, 1);
    lcd->print(">");
  } else {
    if(submenu[submenu_state].type == ROUTE_PRESET_STORE || submenu[submenu_state].type == ROUTE_GO_TO_ROUTE) {
      return;
    }
  }
  if(submenu[submenu_state].type != ROUTE_PRESET_STORE && submenu[submenu_state].bit_mask != 0) {
    submenu_dialog = (preset[submenu[submenu_state].param1] >> submenu[submenu_state].bit_shift) & submenu[submenu_state].bit_mask;
  }
  if(submenu[submenu_state].presentation == OPTIONS) {
    byte startChar = (10 - strlen(submenu[submenu_state].option[submenu_dialog])) / 2;
    lcd->setCursor(5 + startChar, 1);
    lcd->print(submenu[submenu_state].option[submenu_dialog]);
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
    if(submenu[submenu_state].bit_mask != 0) {
      lcd->print(submenu_dialog);
    } else {
      lcd->print(preset[submenu[submenu_state].param1]);
    }
  }
}

void PresetManager::drawMainView() {
  
  byte ctrl_1 = preset[3] >> 0 & B111;
  byte ctrl_2 = preset[3] >> 3 & B111;

  lcd->setCursor(5, 0);
  lcd->print("Mix Dly Fbk");
  for(byte i = 0; i < 3; i++) {
    lcd->setCursor(5 + i * 4, 1);
    if(ctrl_1 == i + 1) {
      lcd->print("C#1");
    } else if(ctrl_2 == i + 1) {
      lcd->print("C#2");
    } else {
      lcd->print(preset[i]);
    }
  }
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