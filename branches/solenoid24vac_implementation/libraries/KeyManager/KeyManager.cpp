#include "KeyManager.h"

/* Se crea un objeto KeyManager pasando como parámetro el objeto Keypad que va a manejar
*
* Parámetros:
*	keypad	Objeto Keypad a controlar
*
*/ 
KeyManager::KeyManager(Keypad * keypad) {
	this->pKeypad = keypad;
}

KeyManager::~KeyManager(){
}

/* Devuelve el objeto Keypad que controla
*
* Parámetros:
*	ninguno
*
* Return:
*	Objeto Keypad
*/ 
Keypad * KeyManager::getKeypad() const {
	return this->pKeypad;
}

/* Ejecuta las operaciones a realizar en cada ciclo de llamada:
*	Leer la tecla pulsada en el teclado
*	Determinar si se trata de una tecla de función o parte de un número o texto a entrar
*
* Parámetros:
*	ninguno
*
* Return:
*	byte	Valor indicando el estado de KeyManager. Los posibles valores a devolver son los siguientes:
*		0	El objeto Keypad no tiene nada que comunicar
*		1	El objeto Keypad solicita comunicar algún tipo de información
*/
byte KeyManager::keyManagerLifeCycle() {
	signalKey = INACTIVE_KEYPAD;
	byte returnCode = 0;
	readKey();
	returnCode = processKey();
	return returnCode;
}


/* Devuelve una variable char que indica el estado en el que se encuentra el objeto KeyManager
*
* Parámetros:
*	ninguno
*
* Return:
*	byte	Valor indicando el estado de KeyManager. Los posibles valores a devolver son los siguientes:
*		0	El objeto Keypad no ha tenido ninguna actividad reciente
*		1	El objeto Keypad ha añadido pulsaciones de teclas a su buffer pero no solicita envío
*/
byte KeyManager::getSignalKey() const {
	return signalKey;
}

char KeyManager::getFunction() const {
	return functionKey;
}

String KeyManager::getText() const {
	return buffer;
}

void KeyManager::clearBuffer() {
	buffer = "";
}

void KeyManager::readKey() {
	key = pKeypad->getKey();
}

/* Devuelve una variable byte que indica el resultado del procesamiento de la última tecla recibida
*
* Parámetros:
*	ninguno
*
* Return:
*	byte	Valor
*		0	La tecla no ha sido aceptada
*		1	La tecla se ha aceptado
*/
byte KeyManager::processKey() {
	if (key == '\0') {
		signalKey = 0;
		return INACTIVE_KEYPAD;
	}
	String functionKeys = "ABCD*#";
	if (expectedKeyType == EXPECTED_FUNCTION) {
		if (functionKeys.indexOf(key) == -1) {
			unExpectedKey();
			return UNEXPECTED_KEY;
		} else {
			processFunction();
			return FUNCTION_KEY_ADVISE;
		}
	} else if (expectedKeyType == EXPECTED_TEXT) {
		if (functionKeys.indexOf(key) == -1) {
			signalKey = TEXT_KEY_ADVISE;
			setKeyInBuffer();
			functionKey = '\0';
			return signalKey;
		} else {
			processFunctionWhenText();
			return signalKey;
		}
	}
	return 0;
}

void KeyManager::unExpectedKey() {
	signalKey = UNEXPECTED_KEY;
	key = '\0';
	functionKey = '\0';
}

void KeyManager::processFunction() {
	signalKey = FUNCTION_KEY_ADVISE;
	functionKey = key;
}	

void KeyManager::processFunctionWhenText() {
	if (key == KEY_RIGHT) {
		signalKey = TEXT_WORD_ADVISE;
		functionKey = key;
	} else if (key == KEY_LEFT) {
		pTextInput->removeLastChar();
		signalKey = TEXT_KEY_ADVISE;
		functionKey = key;
	} else if (key == KEY_UP || key == KEY_DOWN) {
		pTextInput->setTextBuffer(buffer);
		signalKey = FUNCTION_KEY_ADVISE;
		functionKey = key;
	} else if (key == KEY_CANCEL) {
		pTextInput->setTextBuffer(buffer);
		signalKey = TEXT_KEY_ADVISE;
		functionKey = key;
	}
}	

void KeyManager::setKeyInBuffer() {
	pTextInput->addChar(key);
}	

void KeyManager::setExpectedKeyType(byte expectedKeyType) {
	this->expectedKeyType = expectedKeyType;
}

void KeyManager::setTextInput(TextInput * pTextInput) {
	this->pTextInput = pTextInput;
}

void KeyManager::setBuffer(String text) {
	buffer = text;
}


