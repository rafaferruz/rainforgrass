#ifndef ViewManager_h
#define ViewManager_h

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "MenuOption.h"

extern const byte MAX_KEYPAD_ENTRY;
extern const byte LCD_COLUMNS;


class ViewManager {


public:
	ViewManager(LiquidCrystal * pLcd);
	~ViewManager();

	LiquidCrystal * getLcd() const;
	void showMenuOption(MenuOption * menuOption);
	void showTextInput(MenuOption * menuOption);
	void sendMessage(short unsigned column, short unsigned row, String messageCode, char* value);
	void setOffDisplay();
	void setOnDisplay();
	bool isTurnedOn();

private:

	LiquidCrystal * pLcd;
	MenuOption * pMenuOption;
	bool lightStatus;

	void clearLine(unsigned short column, unsigned short row);

};
 
#endif
