#include "Arduino.h"
#include "DeviceElectroValve.h"

/* 
Crea un objeto Device con sus valores iniciales

Parámetros:
	ninguno
*/
 
DeviceElectroValve::DeviceElectroValve() {
	deviceType = ELECTRO_VALVE;
}

/* 
Crea un objeto Device con el valor de sus datos iniciales

Parámetros:
	id		Código de identificación del Dispositivo
	net		Código de Red del Dispositivo
	pProtocol	Puntero a un objeto RainPComm que representa el protocolo de comunicaciones
*/
 
DeviceElectroValve::DeviceElectroValve (unsigned int id, unsigned int net, RainPComm * pRainPComm) {
	Device( id, net, pProtocol);
	deviceType = ELECTRO_VALVE; 
	deviceId = id;
	netCode = net;
	pProtocol = pRainPComm;
}

/* 
Destruye un objeto DeviceElectroValve
*/
 
DeviceElectroValve::~DeviceElectroValve() {
}

/*
Manda una orden de desactivación al objeto Device. Devuelve un valor booleano para indicar el éxito o fracaso de la orden. En la actual versión, siempre devuelve true.

Parámetros:	Ninguno.

Devuelve:	true	La orden se ha enviado correctamente.
		false	La orden no ha podido ser enviada.
*/
bool DeviceElectroValve::deactivate(char * command){
	// Operaciones de desactivación del dispositivo
	if ((*pProtocol).sendMessage(this->deviceId, command)) {
		this->state = INACTIVE_DEVICE;
Serial.println("Enviado comando DEACTIVATE_COMMAND");
		return true;
	}
	return false;
}

/*
Manda una orden de activación al objeto Device. Devuelve un valor booleano para indicar el éxito o fracaso de la orden. En la actual versión, siempre devuelve true.

Parámetros:	Ninguno.

Devuelve:	true	La orden se ha enviado correctamente.
		false	La orden no ha podido ser enviada.
*/
bool DeviceElectroValve::activate(char * command){
	// Operaciones de activación del dispositivo
	if ((*pProtocol).sendMessage(this->deviceId, command)) {
		this->state = ACTIVE_DEVICE;
		return true;
	}
	return false;

}


