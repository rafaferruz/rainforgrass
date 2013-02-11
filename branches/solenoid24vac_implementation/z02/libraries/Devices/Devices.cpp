#include "Arduino.h"
#include "Devices.h"
#include "RainPComm.h"
 
Devices::Devices(Device* pDevices, int numDevices) {
	this->pDevices = pDevices;
	this->numDevices = numDevices;
}

/*
	Devuelve true si consigue añadir el dispositivo a la lista y false si la lista está llena y no lo puede añadir.
*/ 
bool Devices::addDevice(int id, int net, RainPComm * rp){
	// Comprobamos que no exista ya el 'id' en la lista
	if ( this->getDeviceIndex( id ) > -1 ) {
		return false;
	}
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if ( pDevices[i].getDeviceId() == -1) {
			pDevices[i].initialize( id, net, rp);
			return true;
		}
	}
	return false;
}

/*
	Devuelve true si consigue eliminar el dispositivo de la lista y false si no lo puede eliminar porque no lo encuentra en la lista.
*/ 
bool Devices::removeDevice(Device device){
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if ( pDevices[i].getDeviceId() == device.getDeviceId() ) {
			pDevices[i].initialize( -1, -1); 
			return true;
		}
	}
	return false;
}

/*
	Devuelve el dispositivo que se encuentra en la posición indicada por el índice que se pasa como parámetro.
*/ 
Device* Devices::getDevice(byte index){
/*	if ( index > numDevices ) {
		return NULL;
	}*/
	return pDevices + index;
}

/*
	Devuelve el índice que ocupa el dispositivo cuyo id es igual al pasado como parámetro.
*/ 
int Devices::getDeviceIndex(int id){
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pDevices[i].getDeviceId() == id) {
			return i;
		}
	}
	return -1;
}

/*
	Desactiva todos los dispositivos.
*/ 
bool Devices::deactivateAll(){
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pDevices[i].getDeviceId() >= 0) {
			pDevices[i].deactivate();
		}
	}
	return true;
}

/*
	Desactiva el dispositivo cuyo id sea igual al pasado como parámetro.
*/ 
bool Devices::deactivateById(int id){
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pDevices[i].getDeviceId() == id) {
			pDevices[i].deactivate();
			return true;
		}
	}
	return false;
}

/*
	Activa el dispositivo cuyo id sea igual al pasado como parámetro.
*/ 
bool Devices::activateById(int id){
	// Desactivación general de todos los dispositivos
	deactivateAll();
	// Activación del dispositivo indicado
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pDevices[i].getDeviceId() == id) {
			pDevices[i].activate();
			return true;
		}
	}
	return false;
}

