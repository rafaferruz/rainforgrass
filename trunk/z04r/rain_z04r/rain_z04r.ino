/*
rain_z04r
 
 Proyecto para automatización de sistemas de riegos.
 
 Fase 4: Programación del software de control de dispositivos de tipo solenoide.
 
 Descripción de la Fase 4 (rain_z04r) :
 
 	- Desarrollo del software que deben implementar los dispositivos de control de solenoides de electroválvulas.		  del sistema de riego. Solamente se implementa la comunicación de recepción de paquetes en los dispositivos 		  enviados desde el controlador central
 */

// La clase Device se usa para construir un Device 
#include <Device.h>

/* La librera VirtualWire proporciona soporte para las comunicaciones entre el controlador central y los dispositivos a 
controlar */
#include <VirtualWire.h>
/* La librera RainPComm implementa un protocolo propio para la transmisiones de la aplicacion */
#include <RainPComm.h>




// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// Inicializamos las variables del programa
RainPComm rainPComm = RainPComm( TX_PIN, RX_PIN, SPEED_COMM, TARGET_NET, CONTROL_DEV);
Device device;
unsigned long timePrevious;
byte actionCode;

// Fin de inicializacion de variables

void setup() {
  Serial.begin(SERIAL_SPEED);
  // Inicializamos el dispositivo
  device.initialize( DEVICE_ID, TARGET_NET, &rainPComm); 
  device.setPinActivation(PIN_ACTIVATION);
  device.setDelayBetweenStates(DELAY_BETWEEN_STATES);

  timePrevious = millis();
  
  	// Se define el pin que producirá la activación del solenoide
	pinMode( PIN_ACTIVATION, OUTPUT);

}

void loop() {

	// Se pasa control al gestor de comunicaciones
	commManager();
	// Se pasa control al activador del solenoide
	deviceManager();
}

void deviceManager() {
	if (actionCode == ACTION_DEACTIVATE) {
	// Si el dispositivo debe estar desactivado, se fuerza dicho estado cada vez que deviceManager recibe ciclo de ejecución
		device.deactivate();
		return;
	} else if (actionCode == ACTION_ACTIVATE) {
	// Si el dispositivo debe estar activado, se cambia el estado del pin de salida para producir una tensión alterna necesaria para tener activo el solenoide de la electroválvula. La frecuencia de cambio de estado viene determinada principalmente por el valor de la variable DELAY_BETWEEN_STATES
Serial.println("Activando device");
		device.activate();
		return;
	}
}

void commManager() {
	String message = "";
	if ( isOverGapTime(timePrevious, MILLIS_BETWEEN_MESSAGES) ) {
	// Se consulta si hay mensage recibido cada MILLIS_BETWEEN_MESSAGES milisegundos
		message = rainPComm.getMessage();
		if (message.length() > 0) {
			Serial.println(message);
  actionCode=ACTION_ACTIVATE;
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


