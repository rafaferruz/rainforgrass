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

bool RainPComm::sendMessage(int targetDev, char* command){
	String completeMsg = "";
	unsigned int startPosition = 0;
	char partOfMsg[VW_MAX_PAYLOAD];
	if ( !isRightTxComm() ){
		return false;
	}
	completeMsg = prepareAddressBlock(targetDev);
	completeMsg.toCharArray(partOfMsg, completeMsg.length()+1);
	// Llamada a la librería VirtualWire para transmisión del paquete de direcciones
Serial.println(completeMsg);
Serial.println(partOfMsg);
	if ( vw_send( (uint8_t*)partOfMsg, (uint8_t)completeMsg.length()) == false) {
		return false;
	}
	completeMsg = preparePayloadBlock(command);
	completeMsg.toCharArray(partOfMsg, completeMsg.length()+1);
	// Llamada a la librería VirtualWire para transmisión del paquete de direcciones
Serial.println(completeMsg);
Serial.println(partOfMsg);
	if ( vw_send( (uint8_t*)partOfMsg, completeMsg.length()) == false) {
		return false;
	}
Serial.println("Envío finalizado");
	return true;
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
Serial.println("Setting up VirtualWire");
		} else {
			return false;
		}
	}
	return true;
}

String RainPComm::prepareAddressBlock(unsigned int targetDev){
	String message = "#";
	// Incluimos el número de bloque
	if (blockCounter > 64000) {
		blockCounter = 0;
	}
	message.concat(++blockCounter);
	message.concat("#");
	// Incluimos el tipo de bloque (A)ddress
	message.concat("A");
	message.concat("#");
	// Incluimos la Red de Destino
	message.concat(targetNet);
	message.concat("#");
	// Incluimos la Dispositivo de Destino
	message.concat(targetDev);
	message.concat("#");
	// Incluimos la Dispositivo de Origen
	message.concat(sourceDev);
	message.concat("#");
	return message;
}

String RainPComm::preparePayloadBlock(char* command){
	String message = "#";
	// Incluimos el número de bloque
	message.concat(++blockCounter);
	message.concat("#");
	// Incluimos el tipo de bloque (P)ayload
	message.concat("P");
	message.concat("#");
	// Incluimos texto de Comando
	message.concat(command);
	message.concat("#");
	return message;
}

