#ifndef Device_h
#define Device_h

#include "Arduino.h"

class Device {
public:
	Device();
	Device(int id, int net) ;
 
	void initialize(int id, int  net);
	int getDeviceId() ;
	int getNetCode() ;
	int getState() ;
	bool deactivate();
	bool activate();

private:
	int deviceId;
	int netCode;
	int state;	// 0 = No activated; 1 = Activated;

};
 
#endif
