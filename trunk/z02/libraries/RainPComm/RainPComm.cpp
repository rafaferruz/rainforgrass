#include "Arduino.h"
#include "RainPComm.h"
 
RainPComm::RainPComm( byte txPin, byte rcPin, unsigned int speedComm) : 
	txPin (txPin),
	rcPin (rcPin),
	speedComm (speedComm),
	blockCounter(0)
	{ }
 
RainPComm::RainPComm(byte txPin, byte rcPin, unsigned int speedComm, unsigned long targetNet, unsigned int sourceDev) :
	txPin (txPin),
	rcPin (rcPin),
	speedComm (speedComm),
	targetNet (targetNet),
	sourceDev (sourceDev),
	blockCounter(0)
	{ }

bool RainPComm::sendMessage(unsigned int targetDev, char* command){
	String completeMsg = "";
	char partOfMsg[VW_MAX_PAYLOAD];
	if ( !isRightTxComm() ){
		return false;
	}
	completeMsg = addCheckBlock(prepareMessage(targetDev, command));
	// Llamada a la librería VirtualWire para transmisión de un paquete
	completeMsg.toCharArray(partOfMsg,VM_MAX_PAYLOAD);
	return vw_send( (uint8_t*)partOfMsg, completeMsg.length());
}

void RainPComm::setTargetNet(unsigned long targetNet){
	this->targetNet = targetNet;
}

void RainPComm::setSourceDev(unsigned int sourceDev){
	this->sourceDev = sourceDev;
}

bool RainPComm::isRightTxComm(){
	if ( stateComm == 0 ) {
		if (txPin > 0 && speedComm > 0) {
			//  Llamada a la librería VirtualWire para setup de Comm y activación del transmiter
			vw_set_tx_pin( txPin );
			vw_setup( speedComm );
		} else {
			return false;
		}
	}
	return true;
}

String RainPComm::prepareMessage(unsigned int targetDev, char* command){
	String message = "#";
	// Incluimos la Red de Destino
	message.concat(targetNet);
	message.concat("#");
	// Incluimos la Dispositivo de Destino
	message.concat(targetDev);
	message.concat("#");
	// Incluimos la Dispositivo de Origen
	message.concat(sourceDev);
	message.concat("#");
	// Incluimos la Red de Destino
	message.concat(targetNet);
	message.concat("#");
	// Incluimos el número de bloque
	message.concat(++blockCounter);
	message.concat("#");
	// Incluimos texto de Comando
	message.concat(command);
	message.concat("#");
	return message;
}

String RainPComm::addCheckBlock(String message){
	message.concat("ABCD");
	message.concat("#");
	return message;
}
