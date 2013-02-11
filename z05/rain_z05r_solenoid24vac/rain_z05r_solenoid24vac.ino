/*
rain_z05r
 
 Proyecto para automatización de sistemas de riegos.
 
 */

// La clase Device se usa para construir un Device 
#include <DeviceSolenoid24vac.h>

/* La librera VirtualWire proporciona soporte para las comunicaciones entre el controlador central y los dispositivos a 
controlar */
#include <VirtualWire.h>
/* La librera RainPComm implementa un protocolo propio para la transmisiones de la aplicacion */
#include <RainPComm.h>




// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// Inicializamos las variables del programa
RainPComm rainPComm = RainPComm( TX_PIN, RX_PIN, SPEED_COMM, TARGET_NET, CONTROL_DEV);
DeviceSolenoid24vac device;
unsigned long timePrevious;
byte actionCode;

// Fin de inicializacion de variables

void setup() {
  Serial.begin(SERIAL_SPEED);
  // Inicializamos el dispositivo
  device.initialize( DEVICE_ID, TARGET_NET, &rainPComm); 
  device.setPinActivation(PIN_ACTIVATION);
  
  timePrevious = millis();
  
  // Se define el pin que producirá la activación del solenoide
  pinMode( PIN_ACTIVATION, OUTPUT);

}

void loop() {

	// Se pasa control al gestor de comunicaciones
	commManager(&device);
	// Se pasa control al activador del solenoide
	deviceManager(&device);
}

void deviceManager(DeviceSolenoid24vac* device) {
//  Serial.println(ACTION_ACTIVATE);
	if ((*device).getCommand() == ACTION_DEACTIVATE) {
	// Si el dispositivo debe estar desactivado, se fuerza dicho estado cada vez que deviceManager recibe ciclo de ejecución
		(*device).deactivate();
		return;
	} else if ((*device).getCommand() == ACTION_ACTIVATE) {
	// Si el dispositivo debe estar activado, se fuerza dicho estado cada vez que deviceManager recibe ciclo de ejecución
		(*device).activate();
		return;
	}
// Para pruebas. Debe eliminarse cuando se pruebe con controlador central
(*device).activate();
}

void commManager(DeviceSolenoid24vac* device) {
	if ( isOverGapTime(timePrevious, MILLIS_BETWEEN_MESSAGES) ) {
	// Se consulta si hay mensage recibido cada MILLIS_BETWEEN_MESSAGES milisegundos
		(*device).readCommand((*device).getDeviceId());
		if ((*device).getCommand().length() > 0) {
		}
	}
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


