/*
constants.h

Constantes utilizadas en el sketch rain_z05r_solenoid24vac.
*/

// Command Codes de acciones a ejecutar. 
String ACTION_ACTIVATE = "001";
String ACTION_DEACTIVATE = "002";

// Definición de parámetros de comunicaciones Serial
const unsigned long SERIAL_SPEED = 9600;

// Variables de control de comunicaciones por VirtualWire
const byte TX_PIN = 3;                   // No usado en dispositivos SOLO RECEPCION
const byte RX_PIN = 2;
const unsigned long SPEED_COMM = 1200;    // bps
const unsigned long TARGET_NET = 11111;
const unsigned int DEVICE_ID = 3;
const unsigned int CONTROL_DEV = 111;

const unsigned int MILLIS_BETWEEN_MESSAGES = 50;  // Miliseconds entre consulta de mensajes recibidos

const int PIN_ACTIVATION = 9;
