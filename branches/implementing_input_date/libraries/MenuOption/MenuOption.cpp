#include "Arduino.h"
#include "MenuOption.h"
#include "TextInput.h"
 
MenuOption::MenuOption() {
	this->pTextInput = NULL;
}
 
MenuOption::MenuOption(byte menuCode, char* optionText, byte menuBackCode, byte menuNextCode, char* defaultValue, byte actionCode) {
	this->menuCode = menuCode ;
	this->optionText = optionText ;
	this->menuNextCode = menuNextCode ;
	this->menuBackCode = menuBackCode ;
	this->defaultValue = defaultValue ;
	this->actionCode = actionCode ;
	this->pTextInput = NULL;
}

MenuOption::MenuOption(byte menuCode, char* optionText, byte menuBackCode, byte menuNextCode, char* defaultValue, byte actionCode, TextInput * textInput) {
	this->menuCode = menuCode ;
	this->optionText = optionText ;
	this->menuNextCode = menuNextCode ;
	this->menuBackCode = menuBackCode ;
	this->defaultValue = defaultValue ;
	this->actionCode = actionCode ;
	this->pTextInput = textInput ;
}

void MenuOption::setMenuCode(byte menuCode){
	this->menuCode = menuCode;
}

void MenuOption::setOptionText(char* optionText){
	this->optionText = optionText;
}

void MenuOption::setMenuNextCode(byte menuNextCode){
	this->menuNextCode = menuNextCode;
}

void MenuOption::setMenuBackCode(byte menuBackCode){
	this->menuBackCode = menuBackCode;
}

void MenuOption::setDefaultValue(char* defaultValue){
	this->defaultValue = defaultValue;
}

void MenuOption::setActionCode(byte actionCode){
	this->actionCode = actionCode;
}

byte MenuOption::getMenuCode(){
	return menuCode;
}

char* MenuOption::getOptionText(){
	return optionText;
}

byte MenuOption::getMenuNextCode(){
	return menuNextCode;
}

byte MenuOption::getMenuBackCode(){
	return menuBackCode;
}

char* MenuOption::getDefaultValue(){
	return defaultValue;
}

byte MenuOption::getActionCode(){
	return actionCode;
}

TextInput * MenuOption::getTextInput(){
	return pTextInput;
}

  
