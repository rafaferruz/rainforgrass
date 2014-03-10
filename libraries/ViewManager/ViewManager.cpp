#include "ViewManager.h"


/* Se crea un objeto ViewManager pasando como parámetro el objeto LiquidCrystal que va a manejar
*
* Parámetros:
*	keypad	Objeto Keypad a controlar
*
*/ 
ViewManager::ViewManager(LiquidCrystal * pLcd) {
	this->pLcd = pLcd;
}

ViewManager::~ViewManager() {
}

void ViewManager::setMenux(Menux * menux){
	this->pMenux = menux;
}

Menux * ViewManager::getMenux() const{
	return this->pMenux;
}

LiquidCrystal * ViewManager::getLcd() const{
	return this->pLcd;
}

void ViewManager::startMenux(){
  // Definimos el código del menú inicial a mostrar
	pMenux->setPresentMenuCode(MENU_START_CODE);
	pMenux->setTitleMenuOption(MENU_MAIN_TITLE);

//  menux.searchNextOption( 0, MENU_START_CODE);
	pMenux->showMenuOption(pLcd);
  
}

void ViewManager::showMenuOption(){
	pMenux->showMenuOption(pLcd);
}

void ViewManager::setOptionInputText(String text){
	pMenux->getPresentMenuOption().getTextInput()->setTextBuffer(text);
}

void ViewManager::goBackMenu() {
	pMenux->goBackMenu(pMenux->getPresentOption());
}

void ViewManager::goNextOption() {
	pMenux->goNextOption(pMenux->getPresentOption());
}

String ViewManager::getOptionInputText(){
	return pMenux->getPresentMenuOption().getTextInput()->getTextBuffer();
}

/*
  Envía un mensaje a un dispositivo LiquidCrystal colocandolo a partir de la fila y columna indicada en los parmetros
  y concatenando las cadenas messageCode y value.
*/
void ViewManager::sendMessage(LiquidCrystal * lcd, int column, int row, String messageCode, char* value) {
  lcd->setCursor( column, row);
  messageCode.concat(value);
  lcd->print(messageCode);
}


char* ViewManager::getSelectOptionValue() {
	return pMenux->getSelectOptionValue(pMenux->getPresentOption());
}

byte ViewManager::getActionCode(){
	return pMenux->getPresentMenuOption().getActionCode();
}



