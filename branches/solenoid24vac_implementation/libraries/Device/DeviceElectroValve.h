#ifndef DeviceElectroValve_h
#define DeviceElectroValve_h

#include "Device.h"

class DeviceElectroValve: public Device {
public:
	DeviceElectroValve();
	DeviceElectroValve(unsigned int id, unsigned int net, RainPComm * pRainPComm) ;
	virtual ~DeviceElectroValve();
 
	virtual bool deactivate(char * command);
	virtual bool activate(char * command);

};
 
#endif
