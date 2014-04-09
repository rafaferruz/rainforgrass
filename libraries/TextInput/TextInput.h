#ifndef TextInput_h
#define TextInput_h

#include "Arduino.h"
	// Tipos de chequeo con datos entrados desde el keypad
extern	const byte NOTHING_TO_DO;
extern	const byte CHECK_DATE;
extern	const byte CHECK_TIME;

class TextInput {
public:
	TextInput() ;
	TextInput(byte maxLength, String pattern, byte checkCode) ;

	void setParams(byte maxLength, String pattern, byte checkCode) ;
	void setTextBuffer(String initialTextBuffer);
	const String getTextBuffer();
	bool addChar(char key);
	bool removeLastChar();
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
