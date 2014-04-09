#include "Arduino.h"
#include "MenuOption.h"
#include "Menux.h"
 
Menux::Menux() :
	lastOption(-1),
	presentOption(0)
{ }

void Menux::addMenuOption(MenuOption menuOption) {
	menuOptionList[++lastOption] = menuOption;
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

MenuOption * Menux::getPresentMenuOption(){
	return menuOptionList + presentOption;
}

void Menux::setTitleMenuOption(String title){
	titleMenuOption = title;
}

String Menux::getTitleMenuOption(){
	return titleMenuOption;
}

MenuOption * Menux::goBackOption(){
	if (menuOptionList[presentOption].getMenuBackCode() == 0) {
		presentMenuCode = 1;
	} else {
		presentMenuCode = menuOptionList[presentOption].getMenuBackCode();
	}
	goNextOption();
	return menuOptionList + presentOption;	
}

MenuOption * Menux::goFollowOption() {
	if (menuOptionList[presentOption].getMenuNextCode() != 0) {
		presentMenuCode = menuOptionList[presentOption].getMenuNextCode();
	}
	goNextOption();
	return menuOptionList + presentOption;	
}

// Devuelve el valor de la option
char* Menux::getSelectOptionValue() {
	if (menuOptionList[presentOption].getMenuNextCode() == 0) {
		char* returnedValue = menuOptionList[presentOption].getDefaultValue();
		goBackOption();
		return returnedValue;
	} else {
		presentMenuCode = menuOptionList[presentOption].getMenuCode();
		goNextOption();
		return '\0';
	}
}

MenuOption * Menux::goNextOption() {
	short i;
	for ( i = presentOption + 1; i <= lastOption; i++) {
		if (menuOptionList[i].getMenuCode() == presentMenuCode) {
			presentOption = i;
			presentMenuCode = menuOptionList[i].getMenuCode();
			setTitleMenuOption(*searchTitleMenuOption(i) + ": " + *menuOptionList[presentOption].getDefaultValue());
			return menuOptionList + i;
		}
	}
	// El siguiente caso es para retornar al nivel de menú superior después de la última opción de dato entrante
	if (menuOptionList[presentOption].getTextInput() != NULL) {
		presentMenuCode = menuOptionList[presentOption].getMenuBackCode();
		goPreviousOption();
		return menuOptionList + presentOption;
	}
	for ( i = 0; i < presentOption; i++) {
		if (menuOptionList[i].getMenuCode() == presentMenuCode) {
			presentOption = i;
			presentMenuCode = menuOptionList[i].getMenuCode();
			setTitleMenuOption(*searchTitleMenuOption(i) + ": " + *menuOptionList[presentOption].getDefaultValue());
			return menuOptionList + i;
		}
	}
	return menuOptionList + presentOption;
}

MenuOption * Menux::goPreviousOption() {
	short i;
	for ( i = presentOption - 1; i >= 0 ; i--) {
		if (menuOptionList[i].getMenuCode() == presentMenuCode) {
			presentOption = i;
			presentMenuCode = menuOptionList[i].getMenuCode();
			setTitleMenuOption(*searchTitleMenuOption(i) + ": " + *menuOptionList[presentOption].getDefaultValue());
			return menuOptionList + i;
		}
	}
	for ( i = lastOption; i > presentOption; i--) {
		if (menuOptionList[i].getMenuCode() == presentMenuCode) {
			presentOption = i;
			presentMenuCode = menuOptionList[i].getMenuCode();
			setTitleMenuOption(*searchTitleMenuOption(i) + ": " + *menuOptionList[presentOption].getDefaultValue());
			return menuOptionList + i;
		}
	}
	return menuOptionList + presentOption;
}

char* Menux::searchTitleMenuOption(byte indexOption){
	byte i;
	for ( i = 0; i < lastOption; i++) {
		if (menuOptionList[i].getMenuCode() == menuOptionList[indexOption].getMenuBackCode()) {
			return menuOptionList[i].getOptionText();
		}
	}
	return '\0';
}
