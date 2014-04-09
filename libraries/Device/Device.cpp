#include "Arduino.h"
#include "Device.h"

/* 
Crea un objeto Device con sus valores iniciales

Parámetros:
	ninguno
*/
 
Device::Device() :
	deviceType( 0 ),
	deviceId( NOT_ASSIGNED_DEVICE_CODE ),
	netCode( NOT_ASSIGNED_NET_CODE ),
	state(INACTIVE_DEVICE)
{
 }

/* 
Crea un objeto Device con el valor de sus datos iniciales

Parámetros:
	deviceType	Tipo de Dispositivo	11= Electroválvula; 21=Sensor humedad; 22=Sensor temperatura
	id		Código de identificación del Dispositivo
	net		Código de Red del Dispositivo
	pProtocol	Puntero a un objeto RainPComm que representa el protocolo de comunicaciones
*/
 
Device::Device(unsigned int id, unsigned int net, RainPComm * pProtocol) :
	deviceType( 0 ),
	deviceId( id ),
	netCode( net ),
	pProtocol( pProtocol)
{
 }

/* 
Destruye un objeto Device
*/
 
Device::~Device() { }

/*
Inicializa un dispositivo en el controller con el identificador de dispositivo y la red a la que pertenece.

Parámetros:
	id	Entero para asignar un identificador de dispositivo de destino
	net	Entero para indicar a qué red pertenece el dispositivo
*/
void Device::initialize(unsigned int id, unsigned int net) {
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
void Device::initialize(unsigned int id, unsigned int net, RainPComm * pProtocol) {
	this->deviceId = id ;
	this->netCode = net ;
	this->pProtocol = pProtocol ;
}

/*
Devuelve un entero con el Tipo del dispositivo

Parámetros:	Ninguno.
*/
const unsigned short Device::getDeviceType(){
	return this->deviceType;
}

/*
Devuelve un entero con el número de identificación del dispositivo asignado al objeto Device

Parámetros:	Ninguno.
*/
const unsigned int Device::getDeviceId(){
	return this->deviceId;
}

/*
Devuelve un entero con el número de red del dispositivo asignado al objeto Device

Parámetros:	Ninguno.
*/
const unsigned int Device::getNetCode(){
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

Parámetros:	command	Comando que debe ser enviado al dispositivo para su desactivación

Devuelve:	true	La orden se ha enviado correctamente.
		false	La orden no ha podido ser enviada.
*/
bool Device::deactivate(char * command){
	return true;
}

/*
Manda una orden de activación al objeto Device. Devuelve un valor booleano para indicar el éxito o fracaso de la orden. En la actual versión, siempre devuelve true.

Parámetros:	command	Comando que debe ser enviado al dispositivo para su activación

Devuelve:	true	La orden se ha enviado correctamente.
		false	La orden no ha podido ser enviada.
*/
bool Device::activate(char * command){
	return true;
}


