#ifndef DeviceSolenoid24vac_h
#define DeviceSolenoid24vac_h

#include "Arduino.h"
#include "RainPComm.h"

class DeviceSolenoid24vac {
public:
	DeviceSolenoid24vac();
	DeviceSolenoid24vac(int id, int net, RainPComm * rp) ;
 
	void initialize(int id, int  net);
	void initialize(int id, int  net, RainPComm * rp);
	int getDeviceId() ;
	int getNetCode() ;
	byte getState() ;
	bool deactivate();
	bool activate();
	void setPinActivation(byte pinActivation);
	String readCommand(unsigned int deviceId);
	String getCommand();

private:
	int deviceId;
	int netCode;
	RainPComm * rp;
	byte state;	// 0 = No activated; 1 = Activated;
	byte pinLevel;
	byte pinActivation;
	String command;
	void setPinLevel(byte level);

};
 
#endif
