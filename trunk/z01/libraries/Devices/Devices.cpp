#include "Arduino.h"
#include "Devices.h"
 
Devices::Devices(Device* pDevices, int numDevices) {
	this->pDevices = pDevices;
	this->numDevices = numDevices;
}

/*
	Devuelve true si consigue añadir el dispositivo a la lista y false si la lista está llena y no lo puede añadir.
*/ 
bool Devices::addDevice(int id, int net){
Serial.print("addDevice ");
Serial.println(id);
	// Comprobamos que no exista ya el 'id' en la lista
	if ( this->getDeviceIndex( id ) > -1 ) {
		return false;
	}
	int i = 0;
Serial.println("Añadiendo dispositivo");
	for (i = 0; i < numDevices; i++) {
		if ( pDevices[i].getDeviceId() == -1) {
Serial.print("i: ");
Serial.print(i);
Serial.print(" - ");
Serial.println(id);
			pDevices[i].initialize( id, net);
			return true;
		}
	}
	return false;
}

/*
	Devuelve true si consigue eliminar el dispositivo de la lista y false no lo puede eliminar porque no lo encuentra en la lista.
*/ 
bool Devices::removeDevice(Device device){
	Device* pTemp = pDevices;
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pTemp != NULL) {
			if ( (*pTemp).getDeviceId() == device.getDeviceId() ) {
				delete pTemp; 
				pTemp = NULL;
				return true;
			}
		}
		pTemp++;
	}
	return false;
}

/*
	Devuelve el dispositivo que se encuentra en la posición indicada por el índice que se pasa como parámetro.
*/ 
Device Devices::getDevice(byte index){
/*	if ( index > numDevices ) {
		return NULL;
	}*/
	Device* pTemp = pDevices;
	int i = 0;
	for (i = 0; i < index; i++) {
		pTemp++;
	}
	return *pTemp;
}

/*
	Devuelve el índice que ocupa el dispositivo cuyo id es igual al pasado como parámetro.
*/ 
int Devices::getDeviceIndex(int id){
	Device* pTemp = pDevices;
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pTemp[i].getDeviceId() == id) {
			return i;
		}
	}
	return -1;
}

/*
	Desactiva todos los dispositivos.
*/ 
bool Devices::deactivateAll(){
	Device* pTemp = pDevices;
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pTemp != NULL) {
			(*pTemp).deactivate();
		}
		pTemp++;
	}
	return true;
}

/*
	Desactiva el dispositivo cuyo id sea igual al pasado como parámetro.
*/ 
bool Devices::deactivateById(int id){
	Device* pTemp = pDevices;
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if ((*pTemp).getDeviceId() == id) {
			(*pTemp).deactivate();
			return true;
		}
		pTemp++;
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
	Device* pTemp = pDevices;
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if ((*pTemp).getDeviceId() == id) {
			(*pTemp).activate();
			return true;
		}
		pTemp++;
	}
	return false;
}

