#include "Arduino.h"
#include "Device.h"
 
Device::Device() :
	deviceId( -1 ),
	netCode( -1 ),
	state(0)
{ }

void Device::initialize(int id, int  net) {
	this->deviceId = id ;
	this->netCode = net ;
}

int Device::getDeviceId(){
	return this->deviceId;
}

int Device::getNetCode(){
	return this->netCode;
}

byte Device::getState(){
	return this->state;
}

bool Device::deactivate(){
	this->state = 0;
	// Operaciones de desactivación del dispositivo
	return true;
}

bool Device::activate(){
	this->state = 1;
	// Operaciones de activación del dispositivo
	return true;
}

