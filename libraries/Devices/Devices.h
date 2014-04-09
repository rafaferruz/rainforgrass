#ifndef Devices_h
#define Devices_h

#include "Arduino.h"
#include "Device.h"

// Configuracin de dispositivos
extern const int MAX_NUM_DEVICES;  // Mximo nmero de dispositivos que se pueden usar
extern const int NOT_ASSIGNED_DEVICE_TYPE;  // Tipo de dispositivo para dispositivos sin asignar
extern const int NOT_ASSIGNED_DEVICE_CODE;  // Cdigo de dispositivo para dispositivos sin asignar
extern const int NOT_ASSIGNED_NET_CODE;  // Cdigo de red sin asignar
extern const int ACTIVE_DEVICE;  // Dispositivo activo
extern const int INACTIVE_DEVICE; // Dispositivo inactivo


class Devices {
public:
	Devices() ;
	bool addDevice(Device * device);
	bool removeDevice(Device device);
	Device* getDevice(byte index);
	int getDeviceIndex(int id);
	Device* getDevice(int id);
	bool deactivateAll(char * deactivateCommand);
	bool deactivateById(int id, char * deactivateCommand);
	bool activateById(int id, char * activateCommand, char * deactivateCommand);

private:
	Device ** pDevices;
	int numDevices;
	int firstFreeIndex;

};
 
#endif
