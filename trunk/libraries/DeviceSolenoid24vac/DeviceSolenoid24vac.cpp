#include "Arduino.h"
#include "DeviceSolenoid24vac.h"
 
DeviceSolenoid24vac::DeviceSolenoid24vac() :
	deviceId( -1 ),
	netCode( -1 ),
	state(0)
{ }

void DeviceSolenoid24vac::initialize(int id, int  net) {
	this->deviceId = id ;
	this->netCode = net ;
}

void DeviceSolenoid24vac::initialize(int id, int  net, RainPComm * rp) {
	this->deviceId = id ;
	this->netCode = net ;
	this->rp = rp ;
}

int DeviceSolenoid24vac::getDeviceId(){
	return this->deviceId;
}

int DeviceSolenoid24vac::getNetCode(){
	return this->netCode;
}

byte DeviceSolenoid24vac::getState(){
	return this->state;
}

void DeviceSolenoid24vac::setPinActivation(byte pin) {
	this->pinActivation = pin;
}

bool DeviceSolenoid24vac::deactivate(){
	this->state = 0;
	// Operaciones de desactivación del dispositivo
	digitalWrite(pinActivation, LOW);
	digitalWrite(13, LOW);
	return true;
}

bool DeviceSolenoid24vac::activate(){
	this->state = 1;
	// Operaciones de activación del dispositivo
	digitalWrite(pinActivation, HIGH);
	digitalWrite(13, HIGH);
	return true;
}


String DeviceSolenoid24vac::readCommand(unsigned int deviceId) {
	String command = (*rp).getMessage(deviceId);
	if ( command.length() > 0 ) {
		this->command = command;
	}
	return this->command;
}

String DeviceSolenoid24vac::getCommand() {
	return this->command;
}

