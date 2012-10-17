#include "Arduino.h"
#include "MenuOption.h"
#include "Menux.h"
 
Menux::Menux() {
 this->lastOption = 0;
}

void Menux::addMenuOption(MenuOption menuOption) {
	menuOptionList[lastOption] = menuOption;
	lastOption += 1;
}	

byte Menux::getLastOption() {
	return lastOption;
}

byte Menux::getPresentOption(){
	return presentOption;
}

void Menux::setPresentMenuCode(byte menuCode){
	presentMenuCode = menuCode;
}

byte Menux::getPresentMenuCode(){
	return presentMenuCode;
}

MenuOption Menux::getPresentMenuOption(){
	return menuOptionList[presentOption];
}

void Menux::setTitleMenuOption(String title){
	titleMenuOption = title;
}

String Menux::getTitleMenuOption(){
	return titleMenuOption;
}

byte Menux::goBackMenu(byte indexOption){
	if (menuOptionList[indexOption].getMenuBackCode() == 0) {
		presentOption = searchNextOption( indexOption, 1);
	} else {
		presentOption = searchNextOption( indexOption, menuOptionList[indexOption].getMenuBackCode());
	}
	return presentOption;	
}

byte Menux::goNextOption(byte indexOption) {
	// Se busca la siguiente MenuOption del grupo
	presentOption = searchNextOption(indexOption, menuOptionList[indexOption].getMenuCode());
	return presentOption;
}

// Devuelve el valor de la option
char* Menux::getSelectOptionValue(byte indexOption) {
	if (menuOptionList[indexOption].getMenuNextCode() == 0) {
		char* returnedValue = menuOptionList[indexOption].getDefaultValue();
		goBackMenu(indexOption);
		return returnedValue;
	} else {
		presentOption = searchNextOption( indexOption, menuOptionList[indexOption].getMenuNextCode());
		return "";
	}
}

byte Menux::searchNextOption(byte fromOption, byte menuCodeToSearch) {
	byte i;
	for ( i = fromOption + 1; i < lastOption; i++) {
		if (menuOptionList[i].getMenuCode() == menuCodeToSearch) {
			presentMenuCode = menuOptionList[i].getMenuCode();
			setTitleMenuOption(*searchTitleMenuOption(i) + ": " + *menuOptionList[fromOption].getDefaultValue());
			return i;
		}
	}
	for ( i = 0; i < fromOption; i++) {
		if (menuOptionList[i].getMenuCode() == menuCodeToSearch) {
			presentMenuCode = menuOptionList[i].getMenuCode();
			setTitleMenuOption(*searchTitleMenuOption(i) + ": " + *menuOptionList[fromOption].getDefaultValue());
			return i;
		}
	}
	return fromOption;
}

void Menux::showMenuOption(LiquidCrystal &lcd) {
	// Se envía al display el título del grupo de MenuOptions	
	lcd.clear();
	if (presentMenuCode == 1) {
		titleMenuOption = "Menu General";
	}
	lcd.setCursor(0, 0);
	lcd.print(titleMenuOption);
	// Se envía al display la MenuOption actual
	lcd.setCursor(0, 1);
	lcd.print(menuOptionList[presentOption].getOptionText());
	return;
}

void Menux::showMenuOption(LiquidCrystal &lcd, String value) {
	showMenuOption(lcd);
	// Se envía al display el valor adicional a mostrar
	lcd.print(" " + value);
	return;
}

char* Menux::searchTitleMenuOption(byte indexOption){
	byte i;
	for ( i = 0; i < lastOption; i++) {
		if (menuOptionList[i].getMenuCode() == menuOptionList[indexOption].getMenuBackCode()) {
			return menuOptionList[i].getOptionText();
		}
	}
	return "";
}
