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
const unsigned long SPEED_COMM = 2000;    // bps
const unsigned long TARGET_NET = 11111;
const unsigned int SOURCE_DEV = 111;

const unsigned int MILLIS_BETWEEN_MESSAGES = 50;  // Miliseconds entre consulta de mensajes recibidos

const unsigned short GENERAL_RELAY_CONTROL_PIN = 9;
const unsigned short ADRESSES_ENABLING_PIN = 5;

const unsigned short ADDRES_RELAY_PIN_A = 6;  //PIN_A para direccion de rele
const unsigned short ADDRES_RELAY_PIN_B = 7;  //PIN_B para direccion de rele
const unsigned short ADDRES_RELAY_PIN_C = 8;  //PIN_C para direccion de rele

const unsigned short ADDRES_BOARD_PIN_A = 3;  //PIN_A para direccion de placa
const unsigned short ADDRES_BOARD_PIN_B = 4;  //PIN_B para direccion de placa
