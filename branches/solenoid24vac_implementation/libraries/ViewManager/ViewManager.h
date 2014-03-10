#ifndef ViewManager_h
#define ViewManager_h

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Menux.h"
// Definición de pines para uso del Keypad
const byte MAX_KEYPAD_ENTRY = 8;

class ViewManager {

// Control del menú de la aplicación
const byte MENU_START_CODE = 1;
const String MENU_MAIN_TITLE = "RAIN_Z05";

public:
	ViewManager(LiquidCrystal * pLcd);
	~ViewManager();

	void setMenux(Menux * pMenux);
	Menux * getMenux() const;
	LiquidCrystal * getLcd() const;
	void startMenux();
	void showMenuOption();
	void setOptionInputText(String text);
	void goBackMenu();
	void goNextOption();
	String getOptionInputText();
	void sendMessage(LiquidCrystal * lcd, int column, int row, String messageCode, char* value);
	char* getSelectOptionValue();
	byte getActionCode();

private:

	LiquidCrystal * pLcd;
	Menux * pMenux = NULL;
	char optionValue[MAX_KEYPAD_ENTRY + 1];

};
 
#endif
