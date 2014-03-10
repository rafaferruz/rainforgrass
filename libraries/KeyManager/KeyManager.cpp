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
Keypad * KeyManager::getKeypad() const{
	return this->pKeypad;
}

/* Devuelve una variable char que indica el estado en el que se encuentra el objeto KeyManager
*
* Parámetros:
*	ninguno
*
* Return:
*	char	Valor indicando el estado de KeyManager. Los posibles valores a devolver son los siguientes:
*		"0"	El objeto Keypad no ha tenido ninguna actividad reciente
*		"1"	El objeto Keypad ha añadido pulsaciones de teclas a su buffer pero no solicita envío
*/ 
char KeyManager::getSignal() const{
	//char key = keypad.waitForKey();
	char key = pKeypad->getKey();
  

	return key;
}

