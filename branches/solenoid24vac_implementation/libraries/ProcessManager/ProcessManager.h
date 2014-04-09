#ifndef ProcessManager_h
#define ProcessManager_h

#include "Arduino.h"
#include "KeyManager.h"
#include "ViewManager.h"
#include "UserFacade.h"
#include "Devices.h"

/*
Constantes utilizadas en la clase ProcessManager
*/
// Definiciones de acciones a ejecutar. El número entero es el que debe codificarse en el campo actionCode de MenuOption.
extern const byte NO_ACTION;
extern const byte ACTION_ACTIVATE;
extern const byte ACTION_DEACTIVATE;
extern const byte ACTION_ON_OFF;
extern const byte SET_DATE;
extern const byte SET_TIME;
// Configuracin de dispositivos
extern const int MAX_NUM_DEVICES;  // Mximo nmero de dispositivos que se pueden usar
extern const int NOT_ASSIGNED_DEVICE_CODE;  // Cdigo de dispositivo para dispositivos sin asignar
extern const int NOT_ASSIGNED_NET_CODE;  // Cdigo de red sin asignar
extern const int ACTIVE_DEVICE;  // Dispositivo activo
extern const int INACTIVE_DEVICE; // Dispositivo inactivo


class ProcessManager {

public:
	ProcessManager(UserFacade * pUserFacade);
	~ProcessManager();
	void startServices();
	bool isButtonCancellation(char key);
	bool isButtonBackRising(char key);
	bool isButtonOptionRising(char key);
	bool isButtonSelectRising(char key);
	void setDevices(Devices * devices);
	void doAction(byte actionCode, String stringValue);
//	void doOnActionCode();
	void processLifeCycle();

private:
	UserFacade * pUserFacade;
	Devices * pDevices;

static char ACTIVATE_COMMAND[4];
static char DEACTIVATE_COMMAND[4];


};


#endif
