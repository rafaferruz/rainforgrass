/*
rain_z05
 
 Proyecto para automatización de sistemas de riegos.
          
 */

/* La libreria <pgmspace.h> proporciona las herramientas necesarias para manipular las variables de datos
en la memoria flash */
#include <pgmspace.h>

// La librera Keypad proporciona funcionalidad para la entrada de datos desde teclados o keypads matriciales
#include <Keypad.h>

// La librera TextInput permite crear objetos que chequean y gestionan los datos entrados a traves del keypad
#include <TextInput.h>

// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// La librera KeyManager permite crear un objeto KeyManager que ser el responsable de gestionar el mod de funcionamiento
// del teclado de entrada de datos y ordenes del sistema
#include <KeyManager.h>

// La librera ViewManager permite crear un objeto ViewManager que sera el responsable de gestionar la visualizacion
// de menus, datos entrados y mensajes por medio de un display LCD
#include <ViewManager.h>

// La librera ProcessManager permite crear un objeto ProcessManager que sera el Controller en el patron MVC
#include <ProcessManager.h>

// La librería Bounce nos proporciona funcionalidad para comprobar el estado de los botones de control de la aplicación.
#include <Bounce.h>

// Se utiliza la librería LiquidCrystal.h para controlar el display LCD
#include "LiquidCrystal.h"

// Se incluyen las librerías MenuOption y Menux que permiten la creación de menús utilizando un display LCD de 16x2
#include <MenuOption.h>
#include <Menux.h>

// La clase Devices se usa para construir una coleccion de objetos Device 
#include <Devices.h>
#include <Device.h>



/* La librera VirtualWire proporciona soporte para las comunicaciones entre el controlador central y los dispositivos a 
controlar */
#include <VirtualWire.h>
/* La librera RainPComm implementa un protocolo propio para la transmisiones de la aplicacion */
#include <RainPComm.h>



// Inicializamos las variables del programa
  // Variables para control de encendido/apagado display LCD
boolean lcdDisplayStatus = true;
long lcdTimeStatus = 0;
  // Otras variables
Device arrayDevices[MAX_NUM_DEVICES];
Devices * pDevices = new Devices( arrayDevices, MAX_NUM_DEVICES );
RainPComm * pRainPComm = new RainPComm( TX_PIN, RC_PIN, SPEED_COMM, TARGET_NET, SOURCE_DEV);
RainPComm & rRainPComm = *pRainPComm;

LiquidCrystal * pLcd = new LiquidCrystal(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
LiquidCrystal & rLcd = *pLcd;

// Creamos un objeto para controlar el menú de opciones
Menux menux = Menux();

// Creamos un objeto para controlar entrada de ordenes desde un keypad
char keys[KEYPAD_ROWS][KEYPAD_COLUMNS];
Keypad * pKeypad = new Keypad( makeKeymap( keys), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLUMNS); 
Keypad & rKeypad = *pKeypad;

// Creamos un objeto responsable de gestionar el teclado por el que se reciben los datos del usuario
KeyManager * pKeyManager = new KeyManager(pKeypad);
KeyManager & rKeyManager = *pKeyManager;

// Creamos un objeto responsable de mostrar informacin al usuario
ViewManager * pViewManager = new ViewManager(pLcd);
ViewManager & rViewManager = *pViewManager;

// Creamos un objeto responsable de recibir datos de los dispositivos de entrada, procesar los datos y enviar
// datos o acciones a realizar a los dispositivos de salida
ProcessManager * pProcessManager = new ProcessManager(pKeyManager, pViewManager);
ProcessManager & rProcessManager = *pProcessManager;

// Fin de inicializacion de variables

void setup() {
  Serial.begin(SERIAL_SPEED);
  // se definen el número de columnas y filas del LCD
  rLcd.begin(LCD_COLUMNS, LCD_ROWS);

  // Rellenamos las opciones del menú de la aplicación
  menux.addMenuOption( MenuOption( 1, "MODO MANUAL", 0, 2, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 2, "Dispositivo:", 1, 0, "0", ACTION_ON_OFF, new TextInput(2, "*#", NOTHING_TO_DO)));
  menux.addMenuOption( MenuOption( 1, "MODO PROGRAMA", 0, 3, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 3, "No disponible 3", 1, 1, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 1, "MODO CONFIG.", 0, 4, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 4, "Fecha:", 1, 4, "", SET_DATE, new TextInput(8, "########", CHECK_DATE)));
  menux.addMenuOption( MenuOption( 4, "Hora:", 1, 0, "", SET_TIME, new TextInput(6, "######", CHECK_TIME)));
  // Pasamos la definicin del servicio de navegacion al objeto ViewManager
  rViewManager.setMenux(&menux);
  // Se arranca el servicio de navegacion
  rViewManager.startMenux();

  // Inicializacin del keypad
  int i, j;
  for (i = 0; i < KEYPAD_ROWS; i++) {
    for (j = 0; j < KEYPAD_COLUMNS; j++) {
      keys[i][j] = KEYPAD_USER_KEY_MAP.charAt( KEYPAD_ROWS * i + j); 
    }
  }
  // Creamos una instancia de la clase Keypad
  rKeyManager.getKeypad()->begin( makeKeymap( keys)); 
 
  // Inicializamos los dispositivos
  pDevices->addDevice( 1, TARGET_NET, pRainPComm); 
  pDevices->addDevice( 2, TARGET_NET, pRainPComm); 
  pDevices->addDevice( 3, TARGET_NET, pRainPComm); 
  pDevices->addDevice( 4, TARGET_NET, pRainPComm); 
  // Pasa la lista de dispositivos a ProcessManager
  rProcessManager.setDevices(pDevices);
  
  Serial.println("IN SETUP");

  // Activamos el display
  setOnLCD(rLcd);
}

void loop() {

  // Si se sobrepasa el tiempo de displayado de datos sin atender el menu, se hace un apagado del display.
  setOffLCD(rLcd);
	// Hacemos un delay de DELAY_CHECK_KEYS milisegundos entre consultas de pulsaciones
	delay(DELAY_CHECK_KEYS);
  // Consultamos estado del teclado si se ha pulsado alguna tecla
  char keySignal = rKeyManager.getSignal();
  
  // Si se ha pulsado una tecla y el display est apagado se procede al encendido del display.
  if (keySignal != 0 && lcdDisplayStatus == false) {
      setOnLCD(rLcd);
  }
  if (keySignal != 0) {
    lcdTimeStatus = millis();
    Serial.println(keySignal);
	// Consultamos si KeyManager desea pasar informacin a ProcessManager
        rProcessManager.processKeySignal(keySignal);
                
  }
}


void deactivateDevice(char* device) {
  // deactivate action del dispositivo
}

void deactivateAllDevices() {
}


void setOffLCD( LiquidCrystal & lcd) {
  if ( ( (millis() - lcdTimeStatus) > (TIME_DISPLAY_OFF * 1000) ) && lcdDisplayStatus == true) {
    lcdDisplayStatus = false;
    lcd.noDisplay();
  }
}

void setOnLCD( LiquidCrystal & lcd) {
  lcdDisplayStatus = true;
  lcd.display();
  lcdTimeStatus = millis();
}


