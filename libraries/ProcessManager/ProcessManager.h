#ifndef ProcessManager_h
#define ProcessManager_h

#include "Arduino.h"
#include "KeyManager.h"
#include "ViewManager.h"
#include "Devices.h"


class ProcessManager {

public:
	ProcessManager(KeyManager * pKeyManager, ViewManager * pViewManager);
	~ProcessManager();
	void processKeySignal(char key);
	bool isButtonCancellation(char key);
	bool isButtonBackRising(char key);
	bool isButtonOptionRising(char key);
	bool isButtonSelectRising(char key);
	void setDevices(Devices * devices);
	void doAction(byte actionCode, char* value);
	void doOnActionCode();

private:
	KeyManager * pKeyManager;
	ViewManager * pViewManager;
	Devices * pDevices;

/*
Constantes utilizadas en la clase ProcessManager
*/
// Definiciones de acciones a ejecutar. El número entero es el que debe codificarse en el campo actionCode de MenuOption.
static const byte NO_ACTION;
static const byte ACTION_ACTIVATE;
static const byte ACTION_DEACTIVATE;
static const byte ACTION_ON_OFF;
static const byte SET_DATE;
static const byte SET_TIME;

static char ACTIVATE_COMMAND[4];
static char DEACTIVATE_COMMAND[4];


// Configuracin de dispositivos
static const int MAX_NUM_DEVICES;  // Mximo nmero de dispositivos que se pueden usar
static const int NOT_ASSIGNED_DEVICE_CODE;  // Cdigo de dispositivo para dispositivos sin asignar
static const int NOT_ASSIGNED_NET_CODE;  // Cdigo de red sin asignar
static const int ACTIVE_DEVICE;  // Dispositivo activo
static const int INACTIVE_DEVICE; // Dispositivo inactivo

};


#endif
