#ifndef RainPComm_h
#define RainPComm_h

#include "Arduino.h"
#include "VirtualWire.h"

class RainPComm {
public:
	RainPComm(byte txPin, byte rxPin, unsigned int speedComm);
	RainPComm(byte txPin, byte rxPin, unsigned int speedComm, unsigned long targetNet, unsigned int sourceDev);
	bool sendMessage(int targetDev, char* command);
	void setTargetNet(unsigned long targetNet);
	void setSourceDev(unsigned int sourceDev);
	String getMessage(unsigned int sourceDev);
	String getCommand();
	unsigned int getTargetDev();
	bool startTxComm();
 
private:

	byte txPin;
	byte rxPin;
	unsigned int speedComm;
	unsigned long targetNet;
	unsigned int sourceDev;
	int targetDev;
	unsigned long blockCounter;
	byte stateTxComm;	// Transmitter: 0 = Comm desactivada; 1 = Comm activada
	byte stateRxComm;	// Receiver: 0 = Comm desactivada; 1 = Comm activada
	unsigned long addressBlockNumber;
	String command;
	String message;

	bool isRightTxComm();
	bool isRightRxComm();
	String prepareAddressBlock(unsigned int targetDev);
	String preparePayloadBlock(char* command);
	bool validateMessage(String message, unsigned int deviceId);
	bool checkNetworkAddress(String message, unsigned long address);
	bool checkDeviceAddress(String message, unsigned int address);
	String split(String message, String separator, byte hit);
};
 
#endif
