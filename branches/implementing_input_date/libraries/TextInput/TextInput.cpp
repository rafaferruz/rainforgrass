#include "Arduino.h"
#include "TextInput.h"
 
TextInput::TextInput() :
	maxLength (0) ,
	pattern ("") ,
	checkCode (0) ,
	textBuffer("") 
{ }
 
TextInput::TextInput(byte maxLength, String pattern, byte checkCode) :
	textBuffer("") 
{
	this->maxLength = maxLength ;
	this->pattern = pattern ;
	this->checkCode = checkCode ;
}

void TextInput::setParams(byte maxLength, String pattern, byte checkCode) {
	this->maxLength = maxLength ;
	this->pattern = pattern ;
	this->checkCode = checkCode ;
}

void TextInput::setTextBuffer(String initialTextBuffer){
	if (initialTextBuffer.length() > this->maxLength) {
		this->textBuffer = initialTextBuffer.substring(0, this->maxLength);
	} else {
		this->textBuffer = initialTextBuffer;
	}
}

const String TextInput::getTextBuffer(){
	return this->textBuffer;
}

bool TextInput::addChar(char key){
	if (this->textBuffer.length() < this->maxLength) {
	        this->textBuffer = this->textBuffer + key;
		return true;
	}
	return false;
}


