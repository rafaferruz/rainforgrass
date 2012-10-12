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
	String goSelectOption(byte indexOption);
	byte searchNextOption(byte fromOption, byte menuCodeToSearch);
	void showMenuOption(LiquidCrystal &lcd);
  
private:
	MenuOption menuOptionList[20];
	byte lastOption;
	byte presentOption;
	byte presentMenuCode;
	String titleMenuOption;
	String searchTitleMenuOption(byte indexOption);
  
};
 
#endif
