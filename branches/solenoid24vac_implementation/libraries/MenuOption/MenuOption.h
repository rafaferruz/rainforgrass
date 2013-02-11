#ifndef MenuOption_h
#define MenuOption_h

#include "Arduino.h"
#include "TextInput.h"

class MenuOption {
public:
	MenuOption() ;
	MenuOption(byte, char* optionText, byte menuBackCode, byte menuNextCode, char* defaultValue, byte actionCode) ;
	MenuOption(byte, char* optionText, byte menuBackCode, byte menuNextCode, char* defaultValue, byte actionCode, TextInput * textInput) ;
 
	void setMenuCode(byte menuCode) ;
	void setOptionText(char* optionText) ;
	void setMenuNextCode(byte menuNextCode) ;
	void setMenuBackCode(byte menuBackCode) ;
	void setDefaultValue(char* defaultValue) ;
	void setActionCode(byte actionCode) ;
	byte getMenuCode() ;
	char* getOptionText() ;
	byte getMenuNextCode() ;
	byte getMenuBackCode() ;
	char* getDefaultValue() ;
	byte getActionCode() ;
	TextInput * getTextInput() ;
private:
	byte menuCode;
	char* optionText;
	byte menuNextCode;
	byte menuBackCode;
	char* defaultValue;
	byte actionCode;
	TextInput * pTextInput;
};
 
#endif
