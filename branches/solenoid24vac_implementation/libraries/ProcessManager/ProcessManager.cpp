#include "ProcessManager.h"


/* Se crea un objeto ProcessManager pasando como parámetros los objetos UserFacade
*
* Parámetros:
*	pUserFacade	Objeto UserFacade del contexto
*/ 
ProcessManager::ProcessManager(UserFacade * pUserFacade) {
	this->pUserFacade = pUserFacade;
}

ProcessManager::~ProcessManager() {
}

void ProcessManager::startServices() {
	pUserFacade->startServices();
}

void ProcessManager::processLifeCycle(){
	// Fase de interacción con el usuario
	pUserFacade->userFacadeLifeCycle();
	// Si recibe orden de ejecutar una acción
	if (pUserFacade->getSignalAction() != NO_ACTION) {
		doAction(pUserFacade->getSignalAction(), pUserFacade->getText());
		delay(3000);
		pUserFacade->reDisplayMenuOption();
	}
}

void ProcessManager::setDevices(Devices * pDevices) {
	this->pDevices = pDevices;
}
/*
void ProcessManager::processKeySignal(char key){
	if (isButtonCancellation(key)) {
                pDevices->deactivateAll(DEACTIVATE_COMMAND);
                pViewManager->showMenuOption();
                pViewManager->setOptionInputText("");
	} else if (isButtonBackRising(key)) {
                pDevices->deactivateAll(DEACTIVATE_COMMAND);
		pViewManager->goBackMenu();
                pViewManager->showMenuOption();
                pViewManager->setOptionInputText("");
	} else if (isButtonOptionRising(key)) {
		pViewManager->goNextOption();
                pViewManager->showMenuOption();
                pViewManager->setOptionInputText("");
	} else if (isButtonSelectRising(key)) {
		doOnActionCode();
	} else {
                if (pViewManager->getMenux()->getPresentMenuOption().getActionCode() != NO_ACTION) {
	                pViewManager->getMenux()->getPresentMenuOption().getTextInput()->addChar(key);
	                pViewManager->getMenux()->showMenuOption(pViewManager->getLcd(), pViewManager->getOptionInputText());
                }
        }
}

bool ProcessManager::isButtonCancellation(char key) {
  return key == '*';
}

bool ProcessManager::isButtonBackRising(char key) {
  return key == '#';
}

bool ProcessManager::isButtonOptionRising(char key) {
  return key == 'B';
}

bool ProcessManager::isButtonSelectRising(char key) {
  return key == 'D';
}

void ProcessManager::doOnActionCode() {
	char optionValue[40];
	// Recibimos el valor de la opción validada o un valor vacío si se trata de navegación a submenú
	if ( pViewManager->getActionCode() != NO_ACTION ) {
               	if (pViewManager->getOptionInputText() != "" ) {
	            	Serial.println(pViewManager->getMenux()->getPresentMenuOption().getTextInput()->matchTextBuffer());
	            	if (pViewManager->getMenux()->getPresentMenuOption().getTextInput()->matchTextBuffer() == false ) {
				// DEBEMOS GUARDAR EL VALOR ENTRADO
	              		pViewManager->getOptionInputText().toCharArray(optionValue, pViewManager->getOptionInputText().length()+1);
		                pViewManager->showMenuOption();
		                pViewManager->setOptionInputText("");
	              		pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "ERR_IN:", optionValue);
	              		return;
	            	}
              		pViewManager->getOptionInputText().toCharArray(optionValue, pViewManager->getOptionInputText().length()+1);
                } else {
      			strcpy(optionValue, pViewManager->getSelectOptionValue());
                }
       		if (optionValue != "") {
	                pViewManager->showMenuOption();
	                pViewManager->setOptionInputText("");
       			doAction(pViewManager->getActionCode(), optionValue);
       		}
	} else {
               	pViewManager->getMenux()->searchNextOption(pViewManager->getMenux()->getPresentOption(), pViewManager->getMenux()->getPresentMenuOption().getMenuNextCode());
                pViewManager->showMenuOption();
                pViewManager->setOptionInputText("");
        }
}
*/
void ProcessManager::doAction(byte actionCode, String stringValue){
	char charValue[stringValue.length()+1];
	stringValue.toCharArray(charValue, stringValue.length()+1);
    	Device* pDevice = NULL;
	if (actionCode == ACTION_ACTIVATE) {
		// Ejecuta acciones para la Action ACTIVATE
		if (pDevices->activateById(atoi(charValue), ACTIVATE_COMMAND, DEACTIVATE_COMMAND) == true ) {
		  pUserFacade->sendMessage(0, 0, "MM_ACT_", charValue);
		} else {
		  pUserFacade->sendMessage(0, 0, "ERROR_DISP_", charValue);
		}
	} else if (actionCode == ACTION_DEACTIVATE) {
		// Ejecuta acciones para la Action DEACTIVATE
		if (pDevices->deactivateById(atoi(charValue), DEACTIVATE_COMMAND) == true ) {
		  pUserFacade->sendMessage(0, 0, "MM_DACT_", charValue);
		} else {
		  pUserFacade->sendMessage(0, 0, "ERROR_DISP_", charValue);
		}
	} else if (actionCode == ACTION_ON_OFF) {
		// Ejecuta acciones para la Action ON_OFF
		pDevice = pDevices->getDevice(atoi(charValue));
		if (pDevice != NULL ) {
		    if (pDevice->getState() == INACTIVE_DEVICE ) {
		        pUserFacade->sendMessage(0, 0, "MM_ACT_", charValue);
		        pDevices->activateById(atoi(charValue), ACTIVATE_COMMAND, DEACTIVATE_COMMAND);
		    } else {
		        pUserFacade->sendMessage(0, 0, "MM_DACT_", charValue);
		        pDevices->deactivateById(atoi(charValue), DEACTIVATE_COMMAND);
		    }
		} else {
		  pUserFacade->sendMessage(0, 0, "ERROR_DISP_", charValue);
		}
	}
}
