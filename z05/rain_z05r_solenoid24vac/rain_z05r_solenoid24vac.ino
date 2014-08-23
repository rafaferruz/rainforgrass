/*
rain_z05r
 
 Proyecto para automatización de sistemas de riegos.
 
 */


// La clase Device se usa para construir un Device 
#include <Solenoids24vacBoardsControl.h>

/* La librera VirtualWire proporciona soporte para las comunicaciones entre el controlador central y los dispositivos a 
controlar */
#include <VirtualWire.h>
/* La librera RainPComm implementa un protocolo propio para la transmisiones de la aplicacion */
#include <RainPComm.h>




// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// Inicializamos las variables del programa
RainPComm * pRainPComm = new RainPComm( TX_PIN, RX_PIN, SPEED_COMM, TARGET_NET, SOURCE_DEV);
RainPComm & rRainPComm = *pRainPComm;
//RainPComm rainPComm = RainPComm( TX_PIN, RX_PIN, SPEED_COMM, TARGET_NET, CONTROL_DEV);
Solenoids24vacBoardsControl * pDevice = new Solenoids24vacBoardsControl();
unsigned long timePrevious;
byte actionCode;

// Fin de inicializacion de variables

void setup() {
  Serial.begin(SERIAL_SPEED);
  
  timePrevious = millis();
  
  // Se define los pines de de salida de señales de direcciones y activacion del rele general
  pinMode( ADDRES_BOARD_PIN_A, OUTPUT);
  pinMode( ADDRES_BOARD_PIN_B, OUTPUT);
  pinMode( ADDRES_RELAY_PIN_A, OUTPUT);
  pinMode( ADDRES_RELAY_PIN_B, OUTPUT);
  pinMode( ADDRES_RELAY_PIN_C, OUTPUT);
  pinMode( ADRESSES_ENABLING_PIN, OUTPUT);
  pinMode( GENERAL_RELAY_CONTROL_PIN, OUTPUT);

}

void loop() {

	// Se pasa control al gestor de comunicaciones
	if (commManager(pRainPComm)) {
        	// Se pasa control al activador del solenoide
        	deviceManager(pDevice, pRainPComm);
        }
}

void deviceManager(Solenoids24vacBoardsControl * pDevice, RainPComm * pRainPComm) {
//  Serial.println(ACTION_ACTIVATE);
	if (pRainPComm->getCommand() == ACTION_DEACTIVATE) {
	// Si el dispositivo debe estar desactivado, se fuerza dicho estado cada vez que deviceManager recibe ciclo de ejecución
		pDevice->deactivate(pRainPComm->getTargetDev());
		return;
	} else if (pRainPComm->getCommand() == ACTION_ACTIVATE) {
	// Si el dispositivo debe estar activado, se fuerza dicho estado cada vez que deviceManager recibe ciclo de ejecución
		pDevice->activate(pRainPComm->getTargetDev());
		return;
	}
}

bool commManager(RainPComm * pRainPComm) {
        String message;
	if ( isOverGapTime(timePrevious, MILLIS_BETWEEN_MESSAGES ) ) {
	// Se consulta si hay mensage recibido despus de esperar MILLIS_BETWEEN_MESSAGES milisegundos
                message = pRainPComm->getMessage(SOURCE_DEV);
		if (message.length() > 0) {
                        if (split( message, "#", 3) == "P" ) {
                                return true;
                        }
		}
	}
        return false;
}

bool isOverGapTime( unsigned long time, unsigned long gapTime) {
	if ( millis() < time ) {
		time = millis();
	}
	if ( ((millis() - time) > gapTime) ) {
		setTimePrevious(millis());
		return true;
	}
	return false;
}

void setTimePrevious(unsigned long time) {
  timePrevious = time;
}

String split(String message, String separator, byte hit){
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




