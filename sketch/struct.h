#ifndef struct_h
#define struct_h

struct menuItem {
  char* name;
  byte type;
  byte param1;
  byte param2;
  char* options[];
};

#endif