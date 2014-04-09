#ifndef UserFacade_h
#define UserFacade_h

#include "Arduino.h"
#include "KeyManager.h"
#include "ViewManager.h"
#include "Menux.h"
#include "LiquidCrystal.h"

extern const byte INACTIVE_KEYPAD;
extern const byte FUNCTION_KEY_ADVISE;
extern const byte NUMERIC_KEY_ADVISE;
extern const byte TEXT_KEY_ADVISE;
extern const byte UNEXPEDTED_KEY;

extern const char KEY_UP;
extern const char KEY_DOWN;
extern const char KEY_LEFT;
extern const char KEY_RIGHT;

extern const long unsigned TIME_DISPLAY_OFF;
extern const byte DELAY_CHECK_KEYS;
extern const byte MENU_START_CODE;
extern const String MENU_MAIN_TITLE;

// Definiciones de acciones a ejecutar en ProcessManager. El número entero es el que debe codificarse en el campo actionCode de MenuOption.
extern const byte NO_ACTION;
extern const byte ACTION_ACTIVATE;
extern const byte ACTION_DEACTIVATE;
extern const byte ACTION_ON_OFF;
extern const byte SET_DATE;
extern const byte SET_TIME;



class UserFacade {

public:
	UserFacade(KeyManager * pKeyManager, ViewManager * pViewManager, Menux * pMenux);
	~UserFacade();
	void startServices();
	byte getSignalKey() const;
	byte getSignalAction() const;
	String getText() const;
	char getChar() const;
	void sendMessage(short column, short row, String messageCode, char* value) const;
	void userFacadeLifeCycle();
	void reDisplayMenuOption();

private:
	KeyManager * pKeyManager;
	ViewManager * pViewManager;
	Menux * pMenux;
	byte signalKey = 0;
	byte signalAction = 0;
	char functionKey = '\0';
	String text;
	char character;
	long unsigned displayLastTime = 0;

	void keyManagerLifeCycle();
	void viewManagerLifeCycle();
	bool checkKeypadActivityInTime(long unsigned miliseconds);
	void setOffDisplay() const ;
	void setOnDisplay() const;
	void startMenux();
	void startView() const ;
	void processSignalKey(); 
	void processSignalKeyFunction(); 
	void processSignalKeyNumeric(); 
	void processSignalKeyText(); 
	void processSignalKeyUnexpected(); 
	void setExpectedKeyType(MenuOption * menuOption);
	void processSignalKeyNothingToDo();


};



#endif
