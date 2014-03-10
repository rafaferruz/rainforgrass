#ifndef Devices_h
#define Devices_h

#include "Arduino.h"
#include "Device.h"

class Devices {
public:
	Devices(Device * pDevices, int numDevices) ;
	bool addDevice(int id, int net, RainPComm * pRainPComm);
	bool removeDevice(Device device);
	Device* getDevice(byte index);
	int getDeviceIndex(int id);
	bool deactivateAll(char * deactivateCommand);
	bool deactivateById(int id, char * deactivateCommand);
	bool activateById(int id, char * activateCommand, char * deactivateCommand);

private:
	Device* pDevices;
	int numDevices;
	// Variables de configuracin de dispositivos
	const int NOT_ASSIGNED_DEVICE_CODE = -1;  // Cdigo de dispositivo para dispositivos sin asignar
	const int NOT_ASSIGNED_NET_CODE = -1;  // Cdigo de red sin asignar
	const int ACTIVE_DEVICE = 1;  // Dispositivo activo
	const int INACTIVE_DEVICE = 0; // Dispositivo inactivo

};
 
#endif
