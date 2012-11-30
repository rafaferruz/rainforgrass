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




// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// Inicializamos las variables del programa
boolean showAction = false;
byte activeMode = 0;
char optionValue[MAX_KEYPAD_ENTRY + 1] = "";
//MenuOption presentMenuOption;
//String keypadBuffer;
Device pDevices[MAX_NUM_DEVICES];
Devices devices = Devices( pDevices, MAX_NUM_DEVICES );
RainPComm rainPComm = RainPComm( TX_PIN, RC_PIN, SPEED_COMM, TARGET_NET, SOURCE_DEV);


LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);


// Creamos un objeto para controlar el menú de opciones
Menux menux = Menux();

// Creamos un objeto para controlar entrada de ordenes desde un keypad
char keys[KEYPAD_ROWS][KEYPAD_COLUMNS];
Keypad keypad = Keypad( makeKeymap( keys), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLUMNS); 

// Fin de inicializacion de variables

void setup() {
  Serial.begin(SERIAL_SPEED);
  // se definen el número de columnas y filas del LCD
  lcd.begin(LCD_COLUMNS, LCD_ROWS);

  // Rellenamos las opciones del menú de la aplicación
  menux.addMenuOption( MenuOption( 1, "MODO MANUAL", 0, 2, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 2, "Dispositivo:", 1, 0, "0", ACTION_ON_OFF, new TextInput(2, "*#", NOTHING_TO_DO)));
  menux.addMenuOption( MenuOption( 1, "MODO PROGRAMA", 0, 3, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 3, "No disponible 3", 1, 1, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 1, "MODO CONFIG.", 0, 4, "", NO_ACTION));
  menux.addMenuOption( MenuOption( 4, "Fecha:", 1, 4, "", SET_DATE, new TextInput(8, "########", CHECK_DATE)));
  menux.addMenuOption( MenuOption( 4, "Hora:", 1, 0, "", SET_TIME, new TextInput(6, "######", CHECK_TIME)));

  // Definimos el código del menú inicial a mostrar
  menux.setPresentMenuCode(MENU_START_CODE);
  menux.setTitleMenuOption(MENU_MAIN_TITLE);

//  menux.searchNextOption( 0, MENU_START_CODE);
  menux.showMenuOption(lcd);
  
  // Inicializacin del keypad
  int i, j;
  for (i = 0; i < KEYPAD_ROWS; i++) {
    for (j = 0; j < KEYPAD_COLUMNS; j++) {
      keys[i][j] = KEYPAD_USER_KEY_MAP.charAt( KEYPAD_ROWS * i + j); 
    }
  }
  // Creamos una instancia de la clase Keypad
  keypad.begin( makeKeymap( keys)); 
 
  // Inicializamos los dispositivos
  devices.addDevice( 1, TARGET_NET, &rainPComm); 
  devices.addDevice( 2, TARGET_NET, &rainPComm); 
  devices.addDevice( 3, TARGET_NET, &rainPComm); 
  devices.addDevice( 4, TARGET_NET, &rainPComm); 
}

void loop() {

	// Hacemos un delay de DELAY_CHECK_KEYS milisegundos entre consultas de pulsaciones
	delay(DELAY_CHECK_KEYS);
  // Consultamos si se ha pulsado alguna tecla
//  char key = keypad.waitForKey();
  char key = keypad.getKey();
  if (key != 0) {
	// Consultamos si se ha pulsado algún botón
	if (isButtonCancellation(key)) {
                devices.deactivateAll();
                menux.showMenuOption(lcd);
                setOptionInputText(&menux, "");
	} else if (isButtonBackRising(key)) {
                devices.deactivateAll();
		goBackMenu();
                menux.showMenuOption(lcd);
                setOptionInputText(&menux, "");
	} else if (isButtonOptionRising(key)) {
		goNextOption();
                menux.showMenuOption(lcd);
                setOptionInputText(&menux, "");
	} else if (isButtonSelectRising(key)) {
		// Recibimos el valor de la opción validada o un valor vacío si se trata de navegación a submenú
		if ( menux.getPresentMenuOption().getActionCode() != NO_ACTION ) {
                  if (getOptionInputText(&menux) != "" ) {
                    if (menux.getPresentMenuOption().getTextInput()->matchTextBuffer() == false ) {
// DEBEMOS GUARDAR EL VALOR ENTRADO
                      menux.showMenuOption(lcd);
                      setOptionInputText(&menux, "");
                      getOptionInputText(&menux).toCharArray(optionValue,getOptionInputText(&menux).length()+1);
                      sendMessage(lcd, 0, 0, "ERROR_INPUT:", optionValue);
                      return;
                    }
                    getOptionInputText(&menux).toCharArray(optionValue,getOptionInputText(&menux).length()+1);
                  } else {
                    strcpy(optionValue, getSelectOptionValue());
                  }
        		if (optionValue != "") {
                                menux.showMenuOption(lcd);
                                setOptionInputText(&menux, "");
        			doAction(menux.getPresentMenuOption(), optionValue);
        		}
                } else {
                  menux.searchNextOption(menux.getPresentOption(), menux.getPresentMenuOption().getMenuNextCode());
                  menux.showMenuOption(lcd);
                  setOptionInputText(&menux, "");
                }


	} else {
                if (menux.getPresentMenuOption().getActionCode() != NO_ACTION) {
                  menux.getPresentMenuOption().getTextInput()->addChar(key);
                  menux.showMenuOption(lcd, getOptionInputText(&menux));
                }
        }
                
  }
}

void doAction(MenuOption menuOption, char* value){
        int idxDevice = 0;
	switch (menuOption.getActionCode()) {
		case ACTION_ACTIVATE:
			// Ejecuta acciones para la Action ACTIVATE
                        if (devices.activateById(atoi(value)) == true ) {
                          sendMessage(lcd, 0, 0, "MM_ACT_", value);
                        } else {
                          sendMessage(lcd, 0, 0, "ERROR_DISP_", value);
                        }
			break;
		case ACTION_DEACTIVATE:
			// Ejecuta acciones para la Action DEACTIVATE
                        if (devices.deactivateById(atoi(value)) == true ) {
                          sendMessage(lcd, 0, 0, "MM_DACT_", value);
                        } else {
                          sendMessage(lcd, 0, 0, "ERROR_DISP_", value);
                        }
			break;
		case ACTION_ON_OFF:
			// Ejecuta acciones para la Action ON_OFF
                        idxDevice = devices.getDeviceIndex(atoi(value));
                        if (idxDevice >= 0 ) {
                            if ((*(devices.getDevice(idxDevice))).getState() == 0 ) {
                                sendMessage(lcd, 0, 0, "MM_ACT_", value);
                                devices.activateById(atoi(value));
                            } else {
                                sendMessage(lcd, 0, 0, "MM_DACT_", value);
                                devices.deactivateById(atoi(value));
                            }
                        } else {
                          sendMessage(lcd, 0, 0, "ERROR_DISP_", value);
                        }
			break;
		default:
			// Ejecuta otras acciones cuando no se ha definido una Action definida
			break;
	}

}

void goBackMenu() {
	menux.goBackMenu(menux.getPresentOption());
}

void goNextOption() {
	menux.goNextOption(menux.getPresentOption());
}

char* getSelectOptionValue() {
	return menux.getSelectOptionValue(menux.getPresentOption());
}

bool isButtonCancellation(char key) {
  return key == '*';
}

bool isButtonBackRising(char key) {
  return key == '#';
}

bool isButtonOptionRising(char key) {
  return key == 'B';
}

bool isButtonSelectRising(char key) {
  return key == 'D';
}

void deactivateDevice(char* device) {
  // deactivate action del dispositivo
}

void deactivateAllDevices() {
}

/*
  Envía un mensaje a un dispositivo LiquidCrystal colocandolo a partir de la fila y columna indicada en los parmetros
  y concatenando las cadenas messageCode y value.
*/
void sendMessage(LiquidCrystal lcd, int column, int row, String messageCode, char* value) {
  lcd.setCursor( column, row);
  messageCode.concat(value);
  lcd.print(messageCode);
}

String getOptionInputText(Menux * menux){
  return menux->getPresentMenuOption().getTextInput()->getTextBuffer();
}

void setOptionInputText(Menux * menux, String text){
  return menux->getPresentMenuOption().getTextInput()->setTextBuffer(text);
}


