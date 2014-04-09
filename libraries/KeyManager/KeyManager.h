#ifndef KeyManager_h
#define KeyManager_h

#include "Arduino.h"
#include "Keypad.h"
#include "TextInput.h"

extern const byte UNEXPECTED_KEY;
extern const byte EXPECTED_FUNCTION;
extern const byte EXPECTED_NUMERIC;
extern const byte EXPECTED_TEXT;

extern const byte INACTIVE_KEYPAD;
extern const byte FUNCTION_KEY_ADVISE;
extern const byte NUMERIC_KEY_ADVISE;
extern const byte TEXT_KEY_ADVISE;
extern const byte TEXT_WORD_ADVISE;

extern const char KEY_UP;
extern const char KEY_DOWN;
extern const char KEY_LEFT;
extern const char KEY_RIGHT;
extern const char KEY_CANCEL;


class KeyManager {
	public:
		KeyManager(Keypad * keypad);
		~KeyManager();
	
		byte keyManagerLifeCycle();
		byte getSignalKey() const;
		char getFunction() const;
		Keypad * getKeypad() const;
		String getText() const;
		void clearBuffer();
		void setExpectedKeyType(byte expectedKeyType);
		void setTextInput(TextInput * pTextInput);
		void setBuffer(String text);

	private:
		TextInput * pTextInput;
		Keypad * pKeypad;
		char key;
		byte signalKey;
		char functionKey;
		String buffer;
		byte expectedKeyType;


		void readKey();
		byte processKey();
		void unExpectedKey();
		void processFunction();
		void setKeyInBuffer();
		void processFunctionWhenText();

};
 
#endif
