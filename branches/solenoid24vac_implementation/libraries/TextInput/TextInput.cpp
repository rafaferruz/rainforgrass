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

const bool TextInput::matchTextBuffer(){
	if (this->pattern == "") {
		return true;
	} else if (this->pattern == "*#") {
		return textBufferAllNumbers(textBuffer);
	} else if (this->pattern == "*$") {
		return textBufferAllAlphabetics(textBuffer);
	} else {
Serial.println("Salgo por aquí");
		return textBufferMatchMixed(textBuffer);
	}
	return false;
}

const bool TextInput::textBufferAllNumbers(String text) {
	int i;
	String validChars = "0123456789";
	for (i = 0; i < text.length(); i++) {
		if (validChars.indexOf(text.charAt(i)) < 0) {
			return false;
		} 
	}
	return matchCheckCode();
}

const bool TextInput::textBufferAllAlphabetics(String text) {
	int i;
	String validChars = "ABCDabcd";
	for (i = 0; i < text.length(); i++) {
		if (validChars.indexOf(text.charAt(i)) < 0) {
			return false;
		} 
	}
	return matchCheckCode();
}

const bool TextInput::textBufferMatchMixed(String text) {
	int i;
	String validCharsN = "0123456789";
	String validCharsA = "ABCDabcd";
	for (i = 0; i < text.length(); i++) {
		if (((pattern.substring(i, i+1) == "#") && (validCharsN.indexOf(text.charAt(i)) < 0)) ||((pattern.substring(i, i+1)  == "%") && (validCharsA.indexOf(text.charAt(i)) < 0))) {
			return false;
		} 
	}
	return matchCheckCode();
}

/*
	Este método somete al contenido de la variable textBuffer a unas pruebas de verificación
	que debería cumplir antes de darlo como un contenido válido. Las pruebas vienen definidas
	por la variable checkCode.

	NOTHING_TO_DO	No se exige ninguna comprobación. Devuelve siempre true.

	CHECK_DATE	Comprueba que textBuffer es una fecha válida. El dato a comprobar debe contener
			8 dígitos numéricos y cumplir que el año sea igual o mayor a 1970 y que el día
			y el mes son válidos para el año indicado. Se tomaran los dos primeros dígitos
			como el día (deberá rellenarse con 0 a la izquierda si fuera preciso), los 				dígitos 3 y 4 representan el mes y los cuatro últimos dígitos son el año. El
			formato será, por tanto, ddmmyyyy.

*/
const bool TextInput::matchCheckCode(){
	char cBuf[5];
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
			 
	switch (checkCode) {
		case NOTHING_TO_DO:
			return true;
		case CHECK_DATE:
			textBuffer.substring(4, 8).toCharArray(cBuf,5);
			if (( atoi(cBuf) < 1970) || 
				( atoi(cBuf) > 2049)) {
				return false;
			}
			year = atoi(cBuf);
			textBuffer.substring(2, 4).toCharArray(cBuf,3);
			if (( atoi(cBuf) < 1) || 
				( atoi(cBuf) > 12)) {
				return false;
			}
			month = atoi(cBuf);
			textBuffer.substring(0, 2).toCharArray(cBuf,3);
			if (( atoi(cBuf) < 1) ) {
				return false;
			}
			day = atoi(cBuf);
			if ( ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ) && day > 31 ) ||
				((month == 4 || month == 6 || month == 9 || month == 11 ) && day > 30 ) ||
			 	(month == 2 &&  day > 29 ) ||
				(month == 2 && year % 4 > 0 && day > 28) ) {
				return false;
			}
			return true;
		case CHECK_TIME:
			textBuffer.substring(0, 2).toCharArray(cBuf,3);
			if (( atoi(cBuf) < 0) || 
				( atoi(cBuf) > 23)) {
				return false;
			}
			hour = atoi(cBuf);
			textBuffer.substring(2, 4).toCharArray(cBuf,3);
			if (( atoi(cBuf) < 0) || 
				( atoi(cBuf) > 59)) {
				return false;
			}
			minute = atoi(cBuf);
			textBuffer.substring(4, 6).toCharArray(cBuf,3);
			if (( atoi(cBuf) < 0) || 
				( atoi(cBuf) > 59)) {
				return false;
			}
			second = atoi(cBuf);
			return true;
		default:
			return false;			
	}
}
