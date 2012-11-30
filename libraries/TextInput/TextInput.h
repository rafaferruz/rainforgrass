#ifndef TextInput_h
#define TextInput_h

#include "Arduino.h"

class TextInput {
public:
	TextInput() ;
	TextInput(byte maxLength, String pattern, byte checkCode) ;

	void setParams(byte maxLength, String pattern, byte checkCode) ;
	void setTextBuffer(String initialTextBuffer);
	const String getTextBuffer();
	bool addChar(char key);
	bool matchTextBuffer();
 
private:
	byte maxLength;
	String pattern;
	byte checkCode;
	String textBuffer;

	bool textBufferAllNumbers(String text);
	bool textBufferAllAlphabetics(String text);
	bool textBufferMatchMixed(String text);
	bool matchCheckCode();
};
 
#endif
