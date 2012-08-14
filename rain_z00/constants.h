/*
constants.h

Constantes utilizadas en el proyecto RAIN.
*/

// Definición de pines para uso mediante pulsadores (modalidad de botones)
const byte BUTTON_PREVIOUS = 6;
const byte BUTTON_OPTION = 7;
const byte BUTTON_SELECT = 8;

// Definición de pines para uso del display LCD
const byte LCD_COLUMNS = 16;
const byte LCD_ROWS = 2;
const byte LCD_ENABLE = 11;
const byte LCD_WRITE = 12;
const byte LCD_DB4 = 5;
const byte LCD_DB5 = 4;
const byte LCD_DB6 = 3;
const byte LCD_DB7 = 2;

// Definiciones de acciones a ejecutar. El número entero es el que debe codificarse en el campo actionCode de MenuOption.
const byte ACTION_ACTIVATE = 1;
const byte ACTION_DEACTIVATE = 2;

// Definición de parámetros de comunicaciones Serial
const byte SERIAL_SPEED = 9600;

// Milisegundos entre consultas de estado de botones
const byte DELAY_CHECK_BUTTONS = 100;

// Control del menú de la aplicación
const byte MENU_START_CODE = 1;
const String MENU_MAIN_TITLE = "Menu general";
