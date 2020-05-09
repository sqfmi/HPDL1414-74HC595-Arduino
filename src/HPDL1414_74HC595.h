#ifndef _HPDL1414_74HC595_H
#define _HPDL1414_74HC595_H
#include <Arduino.h>

/*******************************************************************************************************************************************************************************
 * 
 *    HPDL1414          -         U1    U2    U3    U4    U5    U6    U7    U8     U9    U10
 *    PIN               -         WR0   WR1   WR2   WR3   WR4   WR5   WR6   WR7 |  WR8   WR9   D0    D1    D2    D3    D4    D5  |  D6    A0    A1    XX    XX    XX    XX    XX
 *    BIT POSITON       -         23    22    21    20    19    18    17    16  |  15    14    13    12    11    10     9     8  |   7     6     5     4     3     2     1     0
 * 
 /******************************************************************************************************************************************************************************/

#define LATCH			5
#define CLOCK			18
#define DATA 			23
#define OE 				4
#define DISPLAY_LENGTH 	40
#define COMMAND_LENGTH 	24
#define DIGIT_OFFSET    5
#define DATA_OFFSET     7
#define WR_OFFSET      	14
#define ALL_DISPLAYS_MASK 0xFFC000 //BINARY 111111111100000000000000 = HEX 0xFFC000

class HPDL
{
	public:
		HPDL();
    void init();
		void writeChar(byte cursor, char character);
		void print(byte cursor, String text);
		void clear();
	private:
		void _writeSerial(unsigned long packet);
		char _asciiLookup(char i);
		byte _flipByte(byte b);
};

#endif
