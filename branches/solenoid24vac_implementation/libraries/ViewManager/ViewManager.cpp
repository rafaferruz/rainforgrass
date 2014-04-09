#include "ViewManager.h"


/* Se crea un objeto ViewManager pasando como parámetro el objeto LiquidCrystal que va a manejar
*
* Parámetros:
*	keypad	Objeto Keypad a controlar
*
*/ 
ViewManager::ViewManager(LiquidCrystal * pLcd) :
	lightStatus(true)
{
	this->pLcd = pLcd;
}

ViewManager::~ViewManager(){}

LiquidCrystal * ViewManager::getLcd() const{
	return this->pLcd;
}

void ViewManager::showMenuOption(MenuOption * menuOption) {
	pMenuOption = menuOption;
	pLcd->clear();
	// Se envía al display la MenuOption actual
	pLcd->setCursor(0, 0);
	pLcd->print(pMenuOption->getOptionText());
	// Si es una MenuOption de dato, muestra el valor guardado o el valor por defecto
	if (pMenuOption->getTextInput() != NULL) {
		showTextInput(menuOption);
	}
	return;
}

void ViewManager::showTextInput(MenuOption * menuOption) {
	pMenuOption = menuOption;
	clearLine(1);
	pLcd->print(pMenuOption->getTextInput()->getTextBuffer());
}

/*
  Envía un mensaje a un dispositivo LiquidCrystal colocandolo a partir de la fila y columna indicada en los parmetros
  y concatenando las cadenas messageCode y value.
*/
void ViewManager::sendMessage(short unsigned column, short unsigned row, String messageCode, char* value) {
	this->clearLine(row);
	pLcd->setCursor( column, row);
	messageCode.concat(value);
	pLcd->print(messageCode);
}


void ViewManager::setOffDisplay() {
	pLcd->noDisplay();
	this->lightStatus = false;
}

void ViewManager::setOnDisplay() {
	pLcd->display();
	this->lightStatus = true;
}

bool ViewManager::isTurnedOn() {
	return lightStatus;
}

void ViewManager::clearLine(unsigned short line) {
	byte i;
	pLcd->setCursor(0, line);
	for (i = 0; i < LCD_COLUMNS; i++) {
		pLcd->write(' ');
	}
	pLcd->setCursor(0, line);
}



