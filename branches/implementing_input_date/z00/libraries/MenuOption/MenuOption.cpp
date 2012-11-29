#include "Arduino.h"
#include "MenuOption.h"
 
MenuOption::MenuOption() {
}
 
MenuOption::MenuOption(byte menuCode, String optionText, byte menuBackCode, byte menuNextCode, String defaultValue, byte actionCode) {
 this->menuCode = menuCode ;
 this->optionText = optionText ;
 this->menuNextCode = menuNextCode ;
 this->menuBackCode = menuBackCode ;
 this->defaultValue = defaultValue ;
	this->actionCode = actionCode ;
}

void MenuOption::setMenuCode(byte menuCode){
	this->menuCode = menuCode;
}

void MenuOption::setOptionText(String optionText){
	this->optionText = optionText;
}

void MenuOption::setMenuNextCode(byte menuNextCode){
	this->menuNextCode = menuNextCode;
}

void MenuOption::setMenuBackCode(byte menuBackCode){
	this->menuBackCode = menuBackCode;
}

void MenuOption::setDefaultValue(String defaultValue){
	this->defaultValue = defaultValue;
}

void MenuOption::setActionCode(byte actionCode){
	this->actionCode = actionCode;
}

byte MenuOption::getMenuCode(){
	return menuCode;
}

String MenuOption::getOptionText(){
	return optionText;
}

byte MenuOption::getMenuNextCode(){
	return menuNextCode;
}

byte MenuOption::getMenuBackCode(){
	return menuBackCode;
}

String MenuOption::getDefaultValue(){
	return defaultValue;
}

byte MenuOption::getActionCode(){
	return actionCode;
}
  
