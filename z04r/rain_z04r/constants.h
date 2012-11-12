/*
constants.h

Constantes utilizadas en el sketch rain_z04r.
*/

// Definiciones de acciones a ejecutar. 
const byte ACTION_ACTIVATE = 1;
const byte ACTION_DEACTIVATE = 2;

// Definición de parámetros de comunicaciones Serial
const unsigned long SERIAL_SPEED = 9600;

// Variables de control de comunicaciones por VirtualWire
const byte TX_PIN = 3;                   // No usado en dispositivos SOLO RECEPCION
const byte RX_PIN = 2;
const unsigned long SPEED_COMM = 4800;    // bps
const unsigned long TARGET_NET = 11111;
const unsigned int DEVICE_ID = 3;
const unsigned int CONTROL_DEV = 111;

const unsigned int DELAY_BETWEEN_STATES = 10;      // Miliseconds
const unsigned int MILLIS_BETWEEN_MESSAGES = 500;  // Miliseconds

const int PIN_ACTIVATION = 13;
