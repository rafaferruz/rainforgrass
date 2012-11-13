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
	int getDeviceId() ;
	int getNetCode() ;
	byte getState() ;
	bool deactivate();
	bool activate();
	void setPinActivation(byte pinActivation);
	void setDelayBetweenStates(unsigned int timeDelay);
	String getCommand(unsigned int deviceId);

private:
	int deviceId;
	int netCode;
	RainPComm * rp;
	byte state;	// 0 = No activated; 1 = Activated;
	unsigned long timeOfChange;
	byte pinLevel;
	byte pinActivation;
	unsigned int delayBetweenStates;

	bool isTimeOfChange( unsigned long time, unsigned int gapTime);
	void setTimeOfChange( unsigned long time );
	bool changePinLevel();
	void setPinLevel(byte level);

};
 
#endif
