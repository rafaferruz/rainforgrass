#include "Arduino.h"
#include "RainPComm.h"
 
RainPComm::RainPComm( byte txPin, byte rxPin, unsigned int speedComm) : 
	txPin (txPin),
	rxPin (rxPin),
	speedComm (speedComm),
	blockCounter(0),
	stateTxComm(0),
	stateRxComm(0)
	{ }
 
RainPComm::RainPComm(byte txPin, byte rxPin, unsigned int speedComm, unsigned long targetNet, unsigned int sourceDev) :
	txPin (txPin),
	rxPin (rxPin),
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
	if ( vw_send( (uint8_t*)partOfMsg, completeMsg.length()) == false) {
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

// Lee un mensaje desde el receptor sin verificación de direcciones ni estructuras de los bloques
String RainPComm::getMessage(){
	String completeMsg = "";
	bool okMsg = false;
	int payload = VW_MAX_PAYLOAD;
	int* pPayload = &payload; 
	char readBuffer[VW_MAX_PAYLOAD] = "" ;
Serial.print("VW_MAX_PAYLOAD: ");
Serial.println(VW_MAX_PAYLOAD);
	if ( !isRightRxComm() ){
Serial.println("RxComm is Right. ");
		return false;
	}
Serial.print( "vw_have_message(): " );
Serial.println( vw_have_message() );
	if ( vw_have_message() ) {
		okMsg = vw_get_message( (uint8_t*)readBuffer, (uint8_t*)pPayload );
Serial.print( "readBuffer después de vw_get_message(): " );
Serial.println( readBuffer );
Serial.print( "okMsg = " );
Serial.println( okMsg );
		if (okMsg) {
			completeMsg = readBuffer;
		}
		if ( completeMsg == "" ) {
			Serial.println("Paquete NO recibido. ");
		} else {
			Serial.print("OK. Paquete recibido: ");
			Serial.println(completeMsg);
		}
	} else {
		Serial.println("NO HAY Paquete ");
	}
	return completeMsg;
}


void RainPComm::setTargetNet(unsigned long targetNet){
	this->targetNet = targetNet;
}

void RainPComm::setSourceDev(unsigned int sourceDev){
	this->sourceDev = sourceDev;
}

bool RainPComm::isRightTxComm(){
	if ( stateTxComm == 0 ) {
		if (txPin > 0 && speedComm > 0) {
			//  Llamada a la librería VirtualWire para setup de Comm y activación del transmiter
			vw_set_tx_pin( txPin );
			vw_setup( speedComm );
			stateTxComm = 1;
Serial.println("Setting up VirtualWire");
		} else {
			return false;
		}
	}
	return true;
}

bool RainPComm::isRightRxComm(){
delay(3000);
	if ( stateRxComm == 0 ) {
Serial.println("Setting up VirtualWire receiving");
delay(1000);
		if (rxPin > 0 && speedComm > 0) {
			//  Llamada a la librería VirtualWire para setup de Comm y activación del receiver
Serial.println(rxPin);
			vw_set_rx_pin( rxPin );
Serial.println(speedComm);
			vw_setup( speedComm );
Serial.println("Comm start.");
			vw_rx_start();
			stateRxComm = 1;
Serial.println("Setting up VirtualWire receiving");
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

