#include "Arduino.h"
#include "RainPComm.h"
 
RainPComm::RainPComm( byte txPin, byte rxPin, unsigned int speedComm) : 
	txPin (txPin),
	rxPin (rxPin),
	speedComm (speedComm),
	blockCounter(0),
	stateTxComm(0),
	stateRxComm(0),
	command("")
	{ }
 
RainPComm::RainPComm(byte txPin, byte rxPin, unsigned int speedComm, unsigned long targetNet, unsigned int sourceDev) :
	txPin (txPin),
	rxPin (rxPin),
	speedComm (speedComm),
	targetNet (targetNet),
	sourceDev (sourceDev),
	blockCounter(0),
	command("")
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
	if ( vw_send( (uint8_t*)partOfMsg, completeMsg.length()) == false) {
		return false;
	}
	completeMsg = preparePayloadBlock(command);
	completeMsg.toCharArray(partOfMsg, completeMsg.length()+1);
	// Llamada a la librería VirtualWire para transmisión del paquete de direcciones
	if ( vw_send( (uint8_t*)partOfMsg, completeMsg.length()) == false) {
		return false;
	}
	return true;
}

// Lee un mensaje desde el receptor con verificación de direcciones y estructuras de los bloques
String RainPComm::getMessage(unsigned int deviceId){
	String completeMsg = "";
	bool okMsg = false;
	int payload = VW_MAX_MESSAGE_LEN;
	int* pPayload = &payload; 
	char readBuffer[VW_MAX_MESSAGE_LEN] = "" ;
	if ( !isRightRxComm() ){
		return completeMsg;
	}
	if ( vw_have_message() ) {
		okMsg = vw_get_message( (uint8_t*)readBuffer, (uint8_t*)pPayload );
		if (okMsg) {
			completeMsg = readBuffer;
			if ( validateMessage( completeMsg, deviceId ) ) {
				Serial.println( deviceId );
				Serial.println( this->command );
				completeMsg = this->command;
			} else {
				completeMsg = "";
			}
		}
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
		} else {
			return false;
		}
	}
	return true;
}

bool RainPComm::isRightRxComm(){
	if ( stateRxComm == 0 ) {
		if (rxPin > 0 && speedComm > 0) {
			//  Llamada a la librería VirtualWire para setup de Comm y activación del receiver
			vw_set_rx_pin( rxPin );
			vw_setup( speedComm );
			vw_rx_start();
			stateRxComm = 1;
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

bool RainPComm::validateMessage(String message, unsigned int deviceId){
	if (message == "") {
		return false;
	} else if ( message.substring(0, 1) != "#") {
		return false;
	}

	String splitter = split( message, "#", 3);
	if ( splitter == "A" ) {
	   // Verificamos direcciones de red y de dispositivo
		if (checkNetworkAddress(message, this->targetNet) && checkDeviceAddress(message, deviceId)) {
			splitter = split( message, "#", 2);
			char blockNumber[8] = "";
			splitter.toCharArray( blockNumber, splitter.length() + 1);
			this->addressBlockNumber = atoi(blockNumber);
			return true;
   		}
		this->addressBlockNumber = 0;
		return false;
 	}
	if ( splitter == "P" ) {
	   // Verificamos número de bloque consecutivo al de direcciones
		splitter = split( message, "#", 2);
		char blockNumber[8] = "";
		splitter.toCharArray( blockNumber, splitter.length() + 1);
		if ( (this->addressBlockNumber +1) == atoi(blockNumber) ){
			this->command = split( message, "#", 4);
			this->addressBlockNumber = 0;
			return true;
   		}
		this->addressBlockNumber = 0;
		return false;
 	}
	this->addressBlockNumber = 0;
	return false;  
}

bool RainPComm::checkNetworkAddress(String message, unsigned long address) {
  String net = split(message, "#", 4);
  if (net.length() == 0 ) {
    return false;
  }
  if ( net == String(address) ) {
    return true;
  }
  return false;
}

bool RainPComm::checkDeviceAddress(String message, unsigned int address) {
  String dev = split(message, "#", 5);
  if (dev.length() == 0 ) {
    return false;
  }
  if ( dev == String(address) ) {
    return true;
  }
  return false;
}

String RainPComm::split(String message, String separator, byte hit){
  	String split = "";
  	int start = 0;
  	byte counter = 0;
  	int i = 0;
  	while ( start < message.length() ){
    		i = message.indexOf(separator, start);
    		++counter;
    		if ( i < 0 ) {
      			if (start == 0 && hit == 1) {
        			return message;
      			} else if (start == 0 && hit != counter ) {
        			return "";
      			} else if (start > 0 && hit == counter ) {
        			return message.substring(start);
      			} else if (start > 0 && hit != counter ) {
        			return "";
    			}
		}
    		if ( i == start && counter == hit ) {
      			return "";
    		} else if ( i > start  && counter == hit ) {
      			return message.substring(start, i); 
    		} else {
      			start = i + separator.length();
      			if (start >= message.length()) {
        			return "";
      			}
    		}
	}
}


