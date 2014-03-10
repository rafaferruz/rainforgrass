#ifndef KeyManager_h
#define KeyManager_h

#include "Arduino.h"
#include "Keypad.h"
#include "TextInput.h"

class KeyManager {
	public:
		KeyManager(Keypad * keypad);
		~KeyManager();
	
		Keypad * getKeypad() const;
		char getSignal() const;

	private:
		TextInput * pTextInput;
		Keypad * pKeypad;
		char key;
};
 
#endif
