#include "Arduino.h"
#include "TextInput.h"
 
TextInput::TextInput() {
}
 
TextInput::TextInput(byte maxLength, String pattern, byte checkCode) {
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

String TextInput::getTextBuffer(){
	return this->textBuffer;
}

bool TextInput::addChar(char key){
	if (this->textBuffer.length() < this->maxLength) {
	        this->textBuffer = this->textBuffer + key;
	}
/*		presentMenuOption = menux.getPresentMenuOption();
                if (presentMenuOption.getActionCode() != 0) {
                  menux.showMenuOption(lcd, keypadBuffer);
                }
*/
}


