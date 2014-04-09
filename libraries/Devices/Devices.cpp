#include "Arduino.h"
#include "Devices.h"
#include "DeviceElectroValve.h"

#include "RainPComm.h"

/* 
Crea y gestiona una factoría de objetos Device

Parámetros:
	pDevices	Recibe un apuntador al primer elemento de un array de objetos Device
	numDevices	Recibe el número de dispositivos que podrá gestionar la factoría
*/

Devices::Devices() :
	firstFreeIndex(0), 
	numDevices( MAX_NUM_DEVICES)
	{
		this->pDevices = new Device * [MAX_NUM_DEVICES ];
 }

/*
	Devuelve true si consigue añadir el dispositivo a la lista y false si la lista está llena y no lo puede añadir.
*/ 
bool Devices::addDevice(Device * device){
	// Comprobamos que no exista ya el 'id' en la lista
	if ( this->getDeviceIndex( device->getDeviceId() ) < 0  && firstFreeIndex < numDevices) {
		pDevices[firstFreeIndex] = device;
		firstFreeIndex++;
		return true;
	}
	return false;
}

/*
	Devuelve true si consigue eliminar el dispositivo de la lista y false si no lo puede eliminar porque no lo encuentra en la lista.
*/ 
bool Devices::removeDevice(Device device){
	int i = 0, j = 0;
	for (i = 0; i < firstFreeIndex; i++) {
		if ( pDevices[i]->getDeviceId() == device.getDeviceId() ) {
			delete pDevices[i]; 		// Devuelve la memoria ocupada
			pDevices[i] = NULL;
			// Mueve los punteros hacia arriba de la lista para ocupar el puesto dejado vacio
			for ( j = i; j < firstFreeIndex - 1; j++) {
				pDevices[j] = pDevices[j + 1];
				pDevices[j + 1] = NULL;
			}
			firstFreeIndex--;
			return true;
		}
	}
	return false;
}

/*
	Devuelve el dispositivo que se encuentra en la posición indicada por el índice que se pasa como parámetro.
*/ 
Device* Devices::getDevice(byte index){
	if (index > firstFreeIndex) {
		return NULL;
	}
	return *(pDevices + index);
}

/*
	Devuelve el índice que ocupa el dispositivo cuyo id es igual al pasado como parámetro.
*/ 
int Devices::getDeviceIndex(int id){
	int i = 0;
	for (i = 0; i < firstFreeIndex; i++) {
		if (pDevices[i]->getDeviceId() == id) {
			return i;
		}
	}
	return -1;
}

/*
	Devuelve un apuntador al objeto Device cuyo id es igual al pasado como parámetro.
*/ 
Device* Devices::getDevice(int id){
	int i = 0;
	for (i = 0; i < firstFreeIndex; i++) {
		if (pDevices[i]->getDeviceId() == id) {
			return pDevices[i];
		}
	}
	return NULL;
}

/*
	Desactiva todos los dispositivos.
*/ 
bool Devices::deactivateAll(char * deactivateCommand){
	int i = 0;
	for (i = 0; i < numDevices; i++) {
		if (pDevices[i]->getDeviceId() != NOT_ASSIGNED_DEVICE_CODE && pDevices[i]->getState() != INACTIVE_DEVICE ) {
			pDevices[i]->deactivate(deactivateCommand);
		}
	}
	return true;
}

/*
	Desactiva el dispositivo cuyo id sea igual al pasado como parámetro.
*/ 
bool Devices::deactivateById(int id, char * deactivateCommand){
	int i = 0;
	for (i = 0; i < firstFreeIndex; i++) {
		if (pDevices[i]->getDeviceId() == id && pDevices[i]->getState() == ACTIVE_DEVICE ) {
			pDevices[i]->deactivate(deactivateCommand);
			return true;
		}
	}
	return false;
}

/*
	Activa el dispositivo cuyo id sea igual al pasado como parámetro.
*/ 
bool Devices::activateById(int id, char * activateCommand, char * deactivateCommand){
	// Desactivación general de todos los dispositivos
	deactivateAll(deactivateCommand);

	// Activación del dispositivo indicado
	int i = 0;
	for (i = 0; i < firstFreeIndex; i++) {
		if (pDevices[i]->getDeviceId() == id) {
			pDevices[i]->activate(activateCommand);
			return true;
		}
	}
	return false;
}

