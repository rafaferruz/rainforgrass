#include "Arduino.h"
#include "DeviceSolenoid.h"
 
DeviceSolenoid::DeviceSolenoid() :
	deviceId( -1 ),
	netCode( -1 ),
	state(0),
	delayBetweenStates(5000)
{ }

void DeviceSolenoid::initialize(int id, int  net) {
	this->deviceId = id ;
	this->netCode = net ;
}

void DeviceSolenoid::initialize(int id, int  net, RainPComm * rp) {
	this->deviceId = id ;
	this->netCode = net ;
	this->rp = rp ;
}

int DeviceSolenoid::getDeviceId(){
	return this->deviceId;
}

int DeviceSolenoid::getNetCode(){
	return this->netCode;
}

byte DeviceSolenoid::getState(){
	return this->state;
}

void DeviceSolenoid::setPinActivation(byte pin) {
	this->pinActivation = pin;
}

void DeviceSolenoid::setDelayBetweenStates(unsigned int timeDelay) {
	this->delayBetweenStates = timeDelay;
}

bool DeviceSolenoid::deactivate(){
	this->state = 0;
	// Operaciones de desactivación del dispositivo
	setPinLevel(0);
		digitalWrite(pinActivation, LOW);
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);

	return true;
}

bool DeviceSolenoid::activate(){

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

bool DeviceSolenoid::isTimeOfChange( unsigned long time, unsigned int gapTime) {
	if ( millis() < time ) {
		time = millis();
	}
	if ( (millis() - time) > gapTime ) {

		setTimeOfChange(millis());
		return true;
	}
	return false;
}

void DeviceSolenoid::setTimeOfChange( unsigned long time ) {
	timeOfChange = time;
}

void DeviceSolenoid::setPinLevel(byte level) {
	pinLevel = level;
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
}

bool DeviceSolenoid::changePinLevel() {
	if (pinLevel == 0){
Serial.println("pinlevel = 1");
		pinLevel = 1;
		digitalWrite(pinActivation, HIGH);
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(8, HIGH);
	} else {
Serial.println("pinlevel = 0");
		pinLevel = 0;
		digitalWrite(pinActivation, LOW);
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(9, HIGH);
	}
	return pinLevel;
}

String DeviceSolenoid::readCommand(unsigned int deviceId) {
	String command = (*rp).getMessage(deviceId);
	if ( command.length() > 0 ) {
		this->command = command;
	}
	return this->command;
}

String DeviceSolenoid::getCommand() {
	return this->command;
}

