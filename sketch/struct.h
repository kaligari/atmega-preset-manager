#ifndef struct_h
#define struct_h

struct menuItem {
  char* name;
  byte type;
  byte param1;
  byte bit_shift;
  byte bit_mask;
  byte bitMask;
  byte options;
  byte presentation;
  char* option[8];
};

#endif