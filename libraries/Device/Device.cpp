#include "Arduino.h"
#include "Device.h"
 
Device::Device() :
	deviceId( -1 ),
	netCode( -1 ),
	state(0)
{ }

/*
Inicializa un dispositivo en el controller con el identificador de dispositivo y la red a la que pertenece.

Parámetros:
	id	Entero para asignar un identificador de dispositivo de destino
	net	Entero para indicar a qué red pertenece el dispositivo
*/
void Device::initialize(int id, int  net) {
	this->deviceId = id ;
	this->netCode = net ;
}

/*
Inicializa un dispositivo en el controller con el identificador de dispositivo, la red a la que pertenece y una referencia al objeto protocolo de comunicaciones que se usará para enviar y/o recibir información del dispositivo. Este objeto será siempre de tipo RainPComm.

Parámetros:
	id	Entero para asignar un identificador de dispositivo de destino
	net	Entero para indicar a qué red pertenece el dispositivo
	RainPComm *	Puntero referencia al objeto de protocolo de comunicaciones de tipo RainPComm
	
*/
void Device::initialize(int id, int  net, RainPComm * rp) {
	this->deviceId = id ;
	this->netCode = net ;
	this->rp = rp ;
}

/*
Devuelve un entero con el número de identificación del dispositivo asignado al objeto Device

Parámetros:	Ninguno.
*/
const int Device::getDeviceId(){
	return this->deviceId;
}

/*
Devuelve un entero con el número de red del dispositivo asignado al objeto Device

Parámetros:	Ninguno.
*/
const int Device::getNetCode(){
	return this->netCode;
}

/*
Devuelve un byte con el estado en el que se encuentra el dispositivo al hacer la consulta.

Parámetros:	Ninguno.

Devuelve:	0	No activo.
		1	Activo.
*/
const byte Device::getState(){
	return this->state;
}

/*
Manda una orden de desactivación al objeto Device. Devuelve un valor booleano para indicar el éxito o fracaso de la orden. En la actual versión, siempre devuelve true.

Parámetros:	Ninguno.

Devuelve:	true	La orden se ha enviado correctamente.
		false	La orden no ha podido ser enviada.
*/
bool Device::deactivate(char * command){
	// Operaciones de desactivación del dispositivo
	if ((*rp).sendMessage(this->deviceId, command)) {
		this->state = 0;
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
bool Device::activate(char * command){
	// Operaciones de activación del dispositivo
	if ((*rp).sendMessage(this->deviceId, command)) {
		this->state = 1;
		return true;
	}
	return false;

}

