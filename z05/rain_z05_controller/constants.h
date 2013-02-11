/*
constants.h

Constantes utilizadas en el proyecto RAIN_Z05.
*/

// Definición de pines para uso del display LCD
const byte LCD_COLUMNS = 16;
const byte LCD_ROWS = 2;
#define LCD_DB4 A0
#define LCD_DB5 A1
#define LCD_DB6 A2
#define LCD_DB7 A3
#define LCD_ENABLE A4
#define LCD_REGISTER_SELECT A5

// Definición de pines para uso del Keypad
const byte KEYPAD_COLUMNS = 4;
const byte KEYPAD_ROWS = 4;
byte KEYPAD_ROW_PINS[KEYPAD_ROWS] = { 11, 10, 9, 8 };
byte KEYPAD_COL_PINS[KEYPAD_COLUMNS] = { 5, 4, 3, 2 };
String KEYPAD_USER_KEY_MAP = "123A456B789C*0#D";
const byte MAX_KEYPAD_ENTRY = 8;

// Definiciones de acciones a ejecutar. El número entero es el que debe codificarse en el campo actionCode de MenuOption.
const byte NO_ACTION = 0;
const byte ACTION_ACTIVATE = 1;
const byte ACTION_DEACTIVATE = 2;
const byte ACTION_ON_OFF = 3;
const byte SET_DATE = 41;
const byte SET_TIME = 42;

char ACTIVATE_COMMAND[4] = "001";
char DEACTIVATE_COMMAND[4] = "002";

// Definición de parámetros de comunicaciones Serial
const unsigned long SERIAL_SPEED = 9600;

// Milisegundos entre consultas de estado de teclas
const byte DELAY_CHECK_KEYS = 50;
// Segundos sin modificar la informacion del display para su apagado por inactividad
const unsigned long TIME_DISPLAY_OFF = 20;

// Control del menú de la aplicación
const byte MENU_START_CODE = 1;
const String MENU_MAIN_TITLE = "RAIN_Z05";

// Modos de trabajo del menu
const byte MANUAL_MODE = 1;
const byte PROGRAM_MODE = 2;
const byte CONFIGURATION_MODE = 3;

// Variables de configuracin de dispositivos
const int MAX_NUM_DEVICES = 4;  // Mximo nmero de dispositivos que se pueden usar

// Variables de control de comunicaciones por VirtualWire
const byte TX_PIN = 13;
const byte RC_PIN = 12;
const unsigned long SPEED_COMM = 1200;
const unsigned long TARGET_NET = 11111;
const unsigned int SOURCE_DEV = 111;

#ifndef TextInput_h
#define TextInput_h
// Tipos de chequeo con datos entrados desde el keypad
const byte NOTHING_TO_DO = 0;
const byte CHECK_DATE = 1;
const byte CHECK_TIME = 2;
#endif
