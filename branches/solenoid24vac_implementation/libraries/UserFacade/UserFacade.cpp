#include "UserFacade.h"

/*
Constantes utilizadas en la clase UserFacade
*/
/* Se crea un objeto UserFacade pasando como parámetros los objetos KeyManager, ViewManager
*
* Parámetros:
*	keyManager	Objeto KeyManager del contexto
*	viewManager	Objeto ViewManager del contexto
*	menux		Objeto Menux del contexto
*/ 

UserFacade::UserFacade(KeyManager * pKeyManager, ViewManager * pViewManager, Menux * pMenux) {
	this->pKeyManager = pKeyManager;
	this->pViewManager = pViewManager;
	this->pMenux = pMenux;
}

UserFacade::~UserFacade() {
}

void UserFacade::startServices() {
	startView();
	startMenux();
}

/**	Devuelve uno de los siguientes valores:
*
*	0	Notificación de 'No hay actividad de teclado'
*	1	Notificación de 'Hay actividad de teclado'
*	2	Disponible caracter de función o comando
*	3	Disponible caracter numérico
*	4	Disponible cadena de texto
*	5	Tecla no esperada
*/
byte UserFacade::getSignalKey() const {
	return signalKey;
}

byte UserFacade::getSignalAction() const {
	return signalAction;
}

String UserFacade::getText() const {
	return text;
}

char UserFacade::getChar() const {
	return character;
}

void UserFacade::sendMessage (short column, short row, String messageCode, char* value) const {
	pViewManager->sendMessage(column, row, messageCode, value);
}

void UserFacade::userFacadeLifeCycle(){
	keyManagerLifeCycle();

	viewManagerLifeCycle();
}

void UserFacade::keyManagerLifeCycle(){
	signalKey = INACTIVE_KEYPAD;
	signalAction = NO_ACTION;
	// Consultamos estado del teclado si se ha pulsado alguna tecla
	if (pKeyManager->keyManagerLifeCycle() == INACTIVE_KEYPAD) {
		checkKeypadActivityInTime(TIME_DISPLAY_OFF);
	} else {
		// Si se ha pulsado una tecla procede al encendido del display.
		if (!pViewManager->isTurnedOn()){
			setOnDisplay();
		} else {
			signalKey = pKeyManager->getSignalKey();
			processSignalKey();
		}
		displayLastTime = millis();
	}
	// Hacemos un delay de DELAY_CHECK_KEYS milisegundos entre consultas de pulsaciones
//	delay(DELAY_CHECK_KEYS);
}

void UserFacade::viewManagerLifeCycle(){
}

bool UserFacade::checkKeypadActivityInTime(long unsigned seconds) {
	// Si se sobrepasa el tiempo de displayado de datos sin atender el menu, se hace un apagado del display.
	if ((millis() - displayLastTime) > (seconds * 1000)) {
		setOffDisplay();
		return false;
	}
	return true;
}		

void UserFacade::setOffDisplay() const {
	pViewManager->setOffDisplay();
}

void UserFacade::setOnDisplay() const {
	pViewManager->setOnDisplay();
}

void UserFacade::startMenux() {
  // Definimos el código del menú inicial a mostrar
	pMenux->setPresentMenuCode(MENU_START_CODE);
	pMenux->setTitleMenuOption(MENU_MAIN_TITLE);

	setExpectedKeyType(pMenux->getPresentMenuOption());
	pViewManager->showMenuOption(pMenux->getPresentMenuOption());
}

void UserFacade::startView() const {
	pViewManager->setOnDisplay();
}

void UserFacade::processSignalKey() {
	if (signalKey == FUNCTION_KEY_ADVISE) {
		processSignalKeyFunction();
	} else if (signalKey == NUMERIC_KEY_ADVISE) {
		processSignalKeyNumeric();
	} else if (signalKey == TEXT_KEY_ADVISE || signalKey == TEXT_WORD_ADVISE) {
		processSignalKeyText();
	} else if (signalKey == UNEXPECTED_KEY) {
		processSignalKeyUnexpected();
	} else {
		processSignalKeyNothingToDo();
	}
}

void UserFacade::processSignalKeyFunction() {
	functionKey = pKeyManager->getFunction();
	if (functionKey == KEY_UP) {
                //	pDevices->deactivateAll(DEACTIVATE_COMMAND);
                pMenux->goPreviousOption();
	} else if (functionKey == KEY_DOWN) {
                //	pDevices->deactivateAll(DEACTIVATE_COMMAND);
                pMenux->goNextOption();
	} else if (functionKey == KEY_LEFT) {
                pMenux->goBackOption();
	} else if (functionKey == KEY_RIGHT) {
                pMenux->goFollowOption();
        }
	setExpectedKeyType(pMenux->getPresentMenuOption());
	pViewManager->showMenuOption(pMenux->getPresentMenuOption());
}

void UserFacade::processSignalKeyNumeric() {
Serial.println("Pasando por processSignalKeyNumeric()");

}

void UserFacade::processSignalKeyText() {
	functionKey = pKeyManager->getFunction();
	if (functionKey == KEY_RIGHT) {		// Validación y envío de texto o dato
		if (pMenux->getPresentMenuOption()->getActionCode() == NO_ACTION) {	// La opción no requiere ninguna acción. Continúa siguiente opción de menú
		        pMenux->goNextOption();
			setExpectedKeyType(pMenux->getPresentMenuOption());
			pViewManager->showMenuOption(pMenux->getPresentMenuOption());
		} else {	// La opción tiene acción a ejecutar cuando se valida
			signalAction = pMenux->getPresentMenuOption()->getActionCode();
			text = pMenux->getPresentMenuOption()->getTextInput()->getTextBuffer();
		}
	}
	pViewManager->showTextInput(pMenux->getPresentMenuOption());
}

void UserFacade::processSignalKeyUnexpected() {
Serial.println("Pasando por processSignalKeyUnexpected()");
}

void UserFacade::setExpectedKeyType(MenuOption * pMenuOption) {
	if (pMenuOption->getTextInput() == NULL) {
		pKeyManager->setExpectedKeyType(EXPECTED_FUNCTION);
		pKeyManager->setTextInput(NULL);
	} else {
		pKeyManager->setExpectedKeyType(EXPECTED_TEXT);
		if (pMenuOption->getTextInput()->getTextBuffer() == "") {
			pMenuOption->getTextInput()->setTextBuffer(pMenuOption->getDefaultValue());
		}
		pKeyManager->setTextInput(pMenuOption->getTextInput());
		// Se guarda en KeyManager el valor inicial del texto de MenuOption para recuperarlo si se cancela la entrada de datos
		pKeyManager->setBuffer(pMenuOption->getTextInput()->getTextBuffer());
	}
}

void UserFacade::processSignalKeyNothingToDo() {
Serial.println("Pasando por processSignalKeyNothingToDo()");
}

void UserFacade::reDisplayMenuOption() {
	setExpectedKeyType(pMenux->getPresentMenuOption());
	pViewManager->showMenuOption(pMenux->getPresentMenuOption());
}

