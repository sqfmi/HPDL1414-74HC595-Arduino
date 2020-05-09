#include "HPDL1414_74HC595.h"

HPDL::HPDL(){

}

void HPDL::init(){
  digitalWrite(LATCH,HIGH);
  pinMode(LATCH,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(DATA,OUTPUT);
  clear();  
}

//assemble command bits to send to shift registers to write a single char
void HPDL::writeChar(byte cursor, char character){
  unsigned long command = 0;

  //determine which display for Write Enable
  byte wr = (cursor - (cursor % 4)) / 4;
  
  //determine which digit within display
  byte digit = _flipByte(3-(cursor % 4)) >> 6;
  
  //set all WR pins high
  command |= ALL_DISPLAYS_MASK;

  //prepare data bits
  command |= (_asciiLookup(character) << DATA_OFFSET);

  //prepare digit address bits
  command |= (digit << DIGIT_OFFSET);

  //send to shift registers
  _writeSerial(command);

  //toggle the selected display's WR pin to write bits
  bitClear(command,COMMAND_LENGTH-1-wr);
  _writeSerial(command);
  bitSet(command,COMMAND_LENGTH-1-wr);
  _writeSerial(command);
}

//print characters in a string
void HPDL::print(byte cursor, String text){
  for(int i=0; i<text.length(); i++){
    if(cursor + i < DISPLAY_LENGTH){
      writeChar(cursor+i,text.charAt(i)); 
    }
  }
}

//clear display
void HPDL::clear(){
    unsigned long command;
    //A0 A1 are endian swapped but that's ok since we're iterating the entire 2-bit address space
    for(int digit=0; digit<4; digit++){
      command = 0;
      command |= (digit << DIGIT_OFFSET);

      //toggle all display's WR pins and with blank data
      command |= ALL_DISPLAYS_MASK;
      _writeSerial(command);
      command ^= ALL_DISPLAYS_MASK;
      _writeSerial(command);
      command |= ALL_DISPLAYS_MASK;
      _writeSerial(command);
    }
}

//send command to shift registers
void HPDL::_writeSerial(unsigned long packet){
  digitalWrite(LATCH,LOW);
  for(int i=0;i<COMMAND_LENGTH;i++){
      digitalWrite(CLOCK,LOW);
      bitRead(packet,i) ? digitalWrite(DATA,HIGH) : digitalWrite(DATA,LOW);
      digitalWrite(CLOCK,HIGH);
  }
  digitalWrite(LATCH,HIGH);
  digitalWrite(CLOCK,LOW);
  digitalWrite(DATA,LOW);
}

//ASCII Code 32 - 95 lookup
char HPDL::_asciiLookup(char i){
  if (i > 31 && i < 96) return _flipByte(i) >> 1; //shift by 1 becasue the data is only 7 bits
  else if (i > 96 && i < 123) return _flipByte(i - 32)  >> 1 ;
  return _flipByte(32) >> 1;
}

//reverse bit order for correct endian
byte HPDL::_flipByte(byte b)
{
  b = ((b>>1)&0x55)|((b<<1)&0xAA);
  b = ((b>>2)&0x33)|((b<<2)&0xCC);
  b = (b>>4) | (b<<4) ;
  return b;
}