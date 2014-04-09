#ifndef Menux_h
#define Menux_h

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "MenuOption.h"
 
class Menux {
public:
	Menux();
	void addMenuOption(MenuOption menuOption);
	byte getLastOption();
	byte getPresentOption();
	void setPresentMenuCode(byte menuCode);
	byte getPresentMenuCode();
	MenuOption * getPresentMenuOption();
	void setTitleMenuOption(String title);
	String getTitleMenuOption();
	MenuOption * goBackOption();
	MenuOption * goFollowOption();
	char* getSelectOptionValue();
	MenuOption * goNextOption();
	MenuOption * goPreviousOption();
  
private:
	MenuOption menuOptionList[10];
	byte lastOption;
	byte presentOption;
	byte presentMenuCode;
	String titleMenuOption;
	char* searchTitleMenuOption(byte indexOption);
  
};
 
#endif
