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

// La librera KeyManager permite crear un objeto KeyManager que ser el responsable de gestionar el mod de funcionamiento
// del teclado de entrada de datos y ordenes del sistema
#include <KeyManager.h>

// La librera ViewManager permite crear un objeto ViewManager que sera el responsable de gestionar la visualizacion
// de menus, datos entrados y mensajes por medio de un display LCD
#include <ViewManager.h>

// La librera UserFacade permite crear un objeto UserFacade que sera el responsable de gestionar la entrada de datos
// desde el teclado de usuario y la salida de datos al display de visualizacion, en el orden de navegacin y con las
// condiciones indicadas en el objeto Menux
#include <UserFacade.h>

// La librera ProcessManager permite crear un objeto ProcessManager que sera el Controller en el patron MVC
#include <ProcessManager.h>

// La librería Bounce nos proporciona funcionalidad para comprobar el estado de los botones de control de la aplicación.
#include <Bounce.h>

// Se utiliza la librería LiquidCrystal.h para controlar el display LCD
#include <LiquidCrystal.h>

// Se incluyen las librerías MenuOption y Menux que permiten la creación de menús utilizando un display LCD de 16x2
#include <MenuOption.h>
#include <Menux.h>

// La clase Devices se usa para construir una coleccion de objetos Device 
#include <Devices.h>
#include <Device.h>
#include <DeviceElectroValve.h>



/* La librera VirtualWire proporciona soporte para las comunicaciones entre el controlador central y los dispositivos a 
controlar */
#include <VirtualWire.h>
/* La librera RainPComm implementa un protocolo propio para la transmisiones de la aplicacion */
#include <RainPComm.h>

// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"



// Inicializamos las variables del programa
  // Variables para control de encendido/apagado display LCD
boolean lcdDisplayStatus = true;
long lcdTimeStatus = 0;
  // Otras variables
Devices * pDevices = new Devices();
RainPComm * pRainPComm = new RainPComm( TX_PIN, RC_PIN, SPEED_COMM, TARGET_NET, SOURCE_DEV);
RainPComm & rRainPComm = *pRainPComm;

LiquidCrystal * pLcd = new LiquidCrystal(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
LiquidCrystal & rLcd = *pLcd;

// Creamos un objeto para controlar el menú de opciones
Menux * pMenux = new Menux();

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

// Creamos un objeto responsable de definir los datos a recibir por teclado y su formato, recibir dichos datos del 
// teclado y mostrar informacin al usuario en el display
UserFacade * pUserFacade = new UserFacade(pKeyManager, pViewManager, pMenux);
UserFacade & rUserFacade = *pUserFacade;

// Creamos un objeto responsable de recibir datos de los dispositivos de entrada, procesar los datos y enviar
// datos o acciones a realizar a los dispositivos de salida
ProcessManager * pProcessManager = new ProcessManager(pUserFacade);
ProcessManager & rProcessManager = *pProcessManager;

// Fin de inicializacion de variables

unsigned long counter = 0;
unsigned long time = 0;

void setup() {
  Serial.begin(SERIAL_SPEED);
  // se definen el número de columnas y filas del LCD
  rLcd.begin(LCD_COLUMNS, LCD_ROWS);

  // Rellenamos las opciones del menú de la aplicación
  /* Campos de MenuOption:
  *  menuCode
  *  optionText
  *  menuBackCode
  *  menuNextCode
  *  defaultValue
  *  actionCode
  *  textInput
  */
  pMenux->addMenuOption( MenuOption( 1, "MODO MANUAL", 0, 2, "", NO_ACTION));
  pMenux->addMenuOption( MenuOption( 2, "Dispositivo:", 1, 0, "0", ACTION_ON_OFF, new TextInput(2, "*#", NOTHING_TO_DO)));
  pMenux->addMenuOption( MenuOption( 1, "MODO PROGRAMA", 0, 3, "", NO_ACTION));
  pMenux->addMenuOption( MenuOption( 3, "No disponible 3", 1, 1, "", NO_ACTION));
  pMenux->addMenuOption( MenuOption( 1, "MODO CONFIG.", 0, 4, "", NO_ACTION));
  pMenux->addMenuOption( MenuOption( 4, "Fecha:", 1, 4, "", SET_DATE, new TextInput(8, "########", CHECK_DATE)));
  pMenux->addMenuOption( MenuOption( 4, "Hora:", 1, 0, "", SET_TIME, new TextInput(6, "######", CHECK_TIME)));

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
  pDevices->addDevice(new DeviceElectroValve(1, TARGET_NET, pRainPComm)); 
  pDevices->addDevice(new DeviceElectroValve(2, TARGET_NET, pRainPComm)); 
  pDevices->addDevice(new DeviceElectroValve(3, TARGET_NET, pRainPComm)); 
  pDevices->addDevice(new DeviceElectroValve(4, TARGET_NET, pRainPComm)); 
  // Pasa la lista de dispositivos a ProcessManager
  rProcessManager.setDevices(pDevices);
  
  //Se ejecuta el setup del protocolo de comunicaciones RainPComm
  if (!pRainPComm->startTxComm()) {
    Serial.println("Fail TX Comm starting");
  }
  
  Serial.println("IN SETUP 1");

  // Se arranca el servicio de navegacion
  pProcessManager->startServices();
}

void loop() {
        rProcessManager.processLifeCycle();
}




