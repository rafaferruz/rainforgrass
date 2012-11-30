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

bool TextInput::matchTextBuffer(){
	if (this->pattern == "") {
		return true;
	} else if (this->pattern == "*#") {
		return textBufferAllNumbers(textBuffer);
	} else if (this->pattern == "*$") {
		return textBufferAllAlphabetics(textBuffer);
	} else {
		return textBufferMatchMixed(textBuffer);
	}
	return false;
}

bool TextInput::textBufferAllNumbers(String text) {
	int i;
	String validChars = "0123456789";
	for (i = 0; i < text.length(); i++) {
		if (validChars.indexOf(text.charAt(i)) < 0) {
			return false;
		} 
	}
}

bool TextInput::textBufferAllAlphabetics(String text) {
	int i;
	String validChars = "ABCDabcd";
	for (i = 0; i < text.length(); i++) {
		if (validChars.indexOf(text.charAt(i)) < 0) {
			return false;
		} 
	}
}

bool TextInput::textBufferMatchMixed(String text) {
	int i;
	String validCharsN = "0123456789";
	String validCharsA = "ABCDabcd";
	for (i = 0; i < text.length(); i++) {
		if (((pattern.substring(i, i+1) == "#") && (validCharsN.indexOf(text.charAt(i)) < 0)) ||((pattern.substring(i, i+1)  == "%") && (validCharsA.indexOf(text.charAt(i)) < 0))) {
			return false;
		} 
	}
}

bool TextInput::matchCheckCode(){
	switch (checkCode) {
		case NOTHING_TO_DO:
			return true;
		case CHECK_DATE:

		default:
			return false;			
	}
}
