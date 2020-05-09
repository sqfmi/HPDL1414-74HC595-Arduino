#include "HPDL1414_74HC595.h"

HPDL display;

void setup() {
  display.init();
  display.print(0,"HELLO WORLD!");
}

void loop() {
}
