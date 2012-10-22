#ifndef Devices_h
#define Devices_h

#include "Arduino.h"
#include "Device.h"

class Devices {
public:
	Devices(Device* pDevices, int numDevices) ;
	bool addDevice(int id, int net);
	bool removeDevice(Device device);
	Device getDevice(byte index);
	int getDeviceIndex(int id);
	bool deactivateAll();
	bool deactivateById(int id);
	bool activateById(int id);

private:
	Device* pDevices;
	int numDevices;

};
 
#endif
