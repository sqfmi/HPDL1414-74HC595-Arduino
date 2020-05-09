#include "HPDL1414_74HC595.h"

HPDL display;

void setup() {
  display.init();
}

void loop() {
    display.writeChar(0,'/');
    delay(100);
    display.writeChar(0,'-');
    delay(100);
    display.writeChar(0,'\\');
    delay(100);
    display.writeChar(0,'1');
    delay(100);	
}
