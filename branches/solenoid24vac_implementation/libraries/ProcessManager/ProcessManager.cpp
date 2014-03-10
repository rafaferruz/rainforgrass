#include "ProcessManager.h"

/*
Constantes utilizadas en la clase ProcessManager
*/
// Definiciones de acciones a ejecutar. El número entero es el que debe codificarse en el campo actionCode de MenuOption.
const byte ProcessManager::NO_ACTION = 0;
const byte ProcessManager::ACTION_ACTIVATE = 1;
const byte ProcessManager::ACTION_DEACTIVATE = 2;
const byte ProcessManager::ACTION_ON_OFF = 3;
const byte ProcessManager::SET_DATE = 41;
const byte ProcessManager::SET_TIME = 42;

char ProcessManager::ACTIVATE_COMMAND[4] = "001";
char ProcessManager::DEACTIVATE_COMMAND[4] = "002";


// Configuracin de dispositivos
const int ProcessManager::MAX_NUM_DEVICES = 4;  // Mximo nmero de dispositivos que se pueden usar
const int ProcessManager::NOT_ASSIGNED_DEVICE_CODE = -1;  // Cdigo de dispositivo para dispositivos sin asignar
const int ProcessManager::NOT_ASSIGNED_NET_CODE = -1;  // Cdigo de red sin asignar
const int ProcessManager::ACTIVE_DEVICE = 1;  // Dispositivo activo
const int ProcessManager::INACTIVE_DEVICE = 0; // Dispositivo inactivo


/* Se crea un objeto ProcessManager pasando como parámetros los objetos KeyManager, ViewManager
*
* Parámetros:
*	keyManager	Objeto KeyManager del contexto
*	viewManager	Objeto ViewManager del contexto
*/ 
ProcessManager::ProcessManager(KeyManager * pKeyManager, ViewManager * pViewManager) {
	this->pKeyManager = pKeyManager;
	this->pViewManager = pViewManager;
}

ProcessManager::~ProcessManager() {
}

void ProcessManager::setDevices(Devices * pDevices) {
	this->pDevices = pDevices;
}

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

void ProcessManager::doAction(byte actionCode, char* value){
        int idxDevice = 0;
	switch (actionCode) {
		case ACTION_ACTIVATE:
			// Ejecuta acciones para la Action ACTIVATE
                        if (pDevices->activateById(atoi(value), ACTIVATE_COMMAND, DEACTIVATE_COMMAND) == true ) {
                          pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "MM_ACT_", value);
                        } else {
                          pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "ERROR_DISP_", value);
                        }
			break;
		case ACTION_DEACTIVATE:
			// Ejecuta acciones para la Action DEACTIVATE
                        if (pDevices->deactivateById(atoi(value), DEACTIVATE_COMMAND) == true ) {
                          pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "MM_DACT_", value);
                        } else {
                          pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "ERROR_DISP_", value);
                        }
			break;
		case ACTION_ON_OFF:
			// Ejecuta acciones para la Action ON_OFF
                        idxDevice = pDevices->getDeviceIndex(atoi(value));
                        if (idxDevice >= 0 ) {
                            if ((pDevices->getDevice(idxDevice))->getState() == INACTIVE_DEVICE ) {
                                pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "MM_ACT_", value);
                                pDevices->activateById(atoi(value), ACTIVATE_COMMAND, DEACTIVATE_COMMAND);
                            } else {
                                pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "MM_DACT_", value);
                                pDevices->deactivateById(atoi(value), DEACTIVATE_COMMAND);
                            }
                        } else {
                          pViewManager->sendMessage(pViewManager->getLcd(), 0, 0, "ERROR_DISP_", value);
                        }
			break;
		default:
			// Ejecuta otras acciones cuando no se ha definido una Action definida
			break;
	}

}

