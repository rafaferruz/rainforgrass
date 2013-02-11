#ifndef Device_h
#define Device_h

#include "Arduino.h"
#include "RainPComm.h"

class Device {
public:
	Device();
	Device(int id, int net, RainPComm * rp) ;
 
	void initialize(int id, int  net);
	void initialize(int id, int  net, RainPComm * rp);
	const int getDeviceId() ;
	const int getNetCode() ;
	const byte getState() ;
	bool deactivate(char * command);
	bool activate(char * command);

private:
	int deviceId;
	int netCode;
	RainPComm * rp;
	byte state;	// 0 = No activated; 1 = Activated;

};
 
#endif
