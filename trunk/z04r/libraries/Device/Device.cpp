#include "Arduino.h"
#include "Device.h"
 
Device::Device() :
	deviceId( -1 ),
	netCode( -1 ),
	state(0),
	delayBetweenStates(10)
{ }

void Device::initialize(int id, int  net) {
	this->deviceId = id ;
	this->netCode = net ;
}

void Device::initialize(int id, int  net, RainPComm * rp) {
	this->deviceId = id ;
	this->netCode = net ;
	this->rp = rp ;
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

void Device::setPinActivation(byte pin) {
	this->pinActivation = pin;
}

void Device::setDelayBetweenStates(unsigned int timeDelay) {
	this->delayBetweenStates = timeDelay;
}

bool Device::deactivate(){
	this->state = 0;
	// Operaciones de desactivación del dispositivo
	setPinLevel(0);
	return true;
}

bool Device::activate(){
	if ( this->state == 0 ) {
		setTimeOfChange( millis() );
		this->state = 1;
		setPinLevel(1);
	}
	// Operaciones de activación del dispositivo
	
	if ( isTimeOfChange(timeOfChange, this->delayBetweenStates) ){
		changePinLevel();
	}
	return true;
}

bool Device::isTimeOfChange( unsigned long time, unsigned int gapTime) {
	if ( millis() < time ) {
		time = millis();
	}
	if ( ((millis() - time) > gapTime) ) {
		setTimeOfChange(millis());
		return true;
	}
	return false;
}

void Device::setTimeOfChange( unsigned long time ) {
	timeOfChange = time;
}

void Device::setPinLevel(byte level) {
	pinLevel = level;
}

bool Device::changePinLevel() {
	if (pinLevel == 0){
		pinLevel = 1;
		digitalWrite(pinActivation, HIGH);
	} else {
		pinLevel = 0;
		digitalWrite(pinActivation, LOW);
	}
	return pinLevel;
}

