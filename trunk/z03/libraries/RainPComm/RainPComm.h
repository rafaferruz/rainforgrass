#ifndef RainPComm_h
#define RainPComm_h

#include "Arduino.h"
#include "VirtualWire.h"

class RainPComm {
public:
	RainPComm(byte txPin, byte rcPin, unsigned int speedComm);
	RainPComm(byte txPin, byte rcPin, unsigned int speedComm, unsigned long targetNet, unsigned int sourceDev);
	bool sendMessage(int targetDev, char* command);
	void setTargetNet(unsigned long targetNet);
	void setSourceDev(unsigned int sourceDev);
 
private:

	byte txPin;
	byte rcPin;
	unsigned int speedComm;
	unsigned long targetNet;
	unsigned int sourceDev;
	int targetDev;
	unsigned long blockCounter;
	byte stateComm;	// 0 = Comm desactivada; 1 = Comm activada

	bool isRightTxComm();
	String prepareAddressBlock(unsigned int targetDev);
	String preparePayloadBlock(char* command);
};
 
#endif
