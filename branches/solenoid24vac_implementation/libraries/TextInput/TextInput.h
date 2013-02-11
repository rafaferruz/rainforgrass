#ifndef TextInput_h
#define TextInput_h

#include "Arduino.h"
	// Tipos de chequeo con datos entrados desde el keypad
	const byte NOTHING_TO_DO = 0;
	const byte CHECK_DATE = 1;
	const byte CHECK_TIME = 2;

class TextInput {
public:
	TextInput() ;
	TextInput(byte maxLength, String pattern, byte checkCode) ;

	void setParams(byte maxLength, String pattern, byte checkCode) ;
	void setTextBuffer(String initialTextBuffer);
	const String getTextBuffer();
	bool addChar(char key);
	const bool matchTextBuffer();
 
private:

	byte maxLength;
	String pattern;
	byte checkCode;
	String textBuffer;

	const bool textBufferAllNumbers(String text);
	const bool textBufferAllAlphabetics(String text);
	const bool textBufferMatchMixed(String text);
	const bool matchCheckCode();
};
 
#endif
