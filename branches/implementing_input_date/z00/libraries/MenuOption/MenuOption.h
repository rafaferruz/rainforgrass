#ifndef MenuOption_h
#define MenuOption_h

#include "Arduino.h"

class MenuOption {
public:
	MenuOption() ;
	MenuOption(byte, String optionText, byte menuBackCode, byte menuNextCode, String defaultValue, byte actionCode) ;
 
	void setMenuCode(byte menuCode) ;
	void setOptionText(String optionText) ;
	void setMenuNextCode(byte menuNextCode) ;
	void setMenuBackCode(byte menuBackCode) ;
	void setDefaultValue(String defaultValue) ;
	void setActionCode(byte actionCode) ;
	byte getMenuCode() ;
	String getOptionText() ;
	byte getMenuNextCode() ;
	byte getMenuBackCode() ;
	String getDefaultValue() ;
	byte getActionCode() ;
private:
	byte menuCode;
	String optionText;
	byte menuNextCode;
	byte menuBackCode;
	String defaultValue;
	byte actionCode;
};
 
#endif
