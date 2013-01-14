#ifndef Devices_h
#define Devices_h

#include "Arduino.h"
#include "Device.h"

class Devices {
public:
	Devices(Device* pDevices, int numDevices) ;
	bool addDevice(int id, int net, RainPComm * rp);
	bool removeDevice(Device device);
	Device* getDevice(byte index);
	int getDeviceIndex(int id);
	bool deactivateAll(char * deactivateCommand);
	bool deactivateById(int id, char * deactivateCommand);
	bool activateById(int id, char * activateCommand, char * deactivateCommand);

private:
	Device* pDevices;
	int numDevices;

};
 
#endif
