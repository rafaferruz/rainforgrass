#ifndef Menux_h
#define Menux_h

#include "Arduino.h"
#include "LiquidCrystal.h"
 
class Menux {
public:
	Menux();
	void addMenuOption(MenuOption menuOption);
	byte getLastOption();
	byte getPresentOption();
	void setPresentMenuCode(byte menuCode);
	byte getPresentMenuCode();
	MenuOption getPresentMenuOption();
	void setTitleMenuOption(String title);
	String getTitleMenuOption();
	byte goBackMenu(byte indexOption);
	byte goNextOption(byte indexOption);
	char* getSelectOptionValue(byte indexOption);
	byte searchNextOption(byte fromOption, byte menuCodeToSearch);
	void showMenuOption(LiquidCrystal &lcd);
	void showMenuOption(LiquidCrystal &lcd, String value);
  
private:
	MenuOption menuOptionList[10];
	byte lastOption;
	byte presentOption;
	byte presentMenuCode;
	String titleMenuOption;
	char* searchTitleMenuOption(byte indexOption);
  
};
 
#endif
