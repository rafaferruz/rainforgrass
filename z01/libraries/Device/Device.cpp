#include "Arduino.h"
#include "Device.h"
 
Device::Device() {
	this->deviceId = -1 ;
	this->netCode = -1 ;
}

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

byte Device::getStatus(){
	return this->status;
}

bool Device::deactivate(){
	this->status = 0;
	// Operaciones de desactivación del dispositivo
	return true;
}

bool Device::activate(){
	this->status = 1;
Serial.print("Activado disp. ");
Serial.println(this->getDeviceId());
	// Operaciones de activación del dispositivo
	return true;
}

