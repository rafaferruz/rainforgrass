/*
rain_z01
 
 Proyecto para automatización de sistemas de riegos.
 
 Fase 1: Activación de una electroválvula controlada por una placa Arduino Uno.
 
 Descripción de la Fase 1:
 
 	- Aunque el objetivo de esta fase consista en la activación y desactivación del solenoide de una electroválvula
          de riego, el desarrollo del software fue derivando hacia la presentacin sobre un display LCD de 2 filas por
          16 columnas de un menu de opciones de control del solenoide. La placa Arduino lee el estado de tres pulsadores
          para la navegación a través del menú de la aplicación. Este menú debera proporciona funcionalidad para la 
          activación y desactivación de la electroválvula aunque no se ha implementado en esta fase.
 
 
 Fase 2: Introducción del uso de un teclado de 16 teclas para la entrada de órdenes y valores de datos.
 
 Descripción de la Fase 2:
 
 	- Se pretende el uso de un teclado de 16 teclas para la entrada de órdenes de ejecución y valores de datos de configuración. El menú inicial a usar y mostrar en el display es bastante sencillo y solamente permitirá la activación de un dispositivo o electroválvula y su desactivación. Otras opciones se muestran solamente como soporte básico en la construcción del nivel superior del Menú Principal. No obstante, será posible indicar mediante un número entre 1 y 4 el dispositivo que debería ser activado en el supuesto de que se conectasen cuatro dispositivos el circuito. El software de control de la activación de los dispositivos no será desarrollado en esta fase.
 */

// La librera Keypad proporciona funcionalidad para la entrada de datos desde teclados o keypads matriciales
#include <Keypad.h>

// La librería Bounce nos proporciona funcionalidad para comprobar el estado de los botones de control de la aplicación.
#include <Bounce.h>
// Se utiliza la librería LiquidCrystal.h para controlar el display LCD
#include "LiquidCrystal.h"

// Se incluyen las librerías MenuOption y Menux que permiten la creación de menús utilizando un display LCD de 16x2
#include <MenuOption.h>
#include <Menux.h>


// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// Inicializamos las variables del programa
bool showAction = false;
String optionValue = 0;
MenuOption presentMenuOption;

LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);


// Creamos un objeto para controlar el menú de opciones
Menux menux = Menux();

// Creamos un objeto para controlar entrada de rdenes desde un keypad
char keys[KEYPAD_ROWS][KEYPAD_COLUMNS];
Keypad keypad = Keypad( makeKeymap( keys), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLUMNS); 


// Fin de inicializacion de variables

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println(SERIAL_SPEED);
  // se definen el número de columnas y filas del LCD
  lcd.begin(LCD_COLUMNS, LCD_ROWS);

  // Rellenamos las opciones del menú de la aplicación
  menux.addMenuOption( MenuOption( 1, "MODO MANUAL", 0, 2, "", 0));
  menux.addMenuOption( MenuOption( 2, "Disp.: ", 1, 0, "STOP", 1));
  menux.addMenuOption( MenuOption( 1, "MODO PROGRAMA", 0, 3, "", 0));
  menux.addMenuOption( MenuOption( 3, "No disponible 3", 1, 1, "", 0));
  menux.addMenuOption( MenuOption( 1, "MODO CONFIGURACION", 0, 4, "", 0));
  menux.addMenuOption( MenuOption( 4, "No disponible 4", 1, 1, "", 0));

  // Definimos el código del menú inicial a mostrar
  menux.setPresentMenuCode(MENU_START_CODE);
  menux.setTitleMenuOption(MENU_MAIN_TITLE);

  menux.searchNextOption( 0, MENU_START_CODE);
  menux.showMenuOption(lcd);
  
  // Inicializacin del keypad
  Serial.println(KEYPAD_ROWS);
  Serial.println(KEYPAD_COLUMNS);
  Serial.println(KEYPAD_USER_KEY_MAP);
  int i, j;
  for (i = 0; i < KEYPAD_ROWS; i++) {
    for (j = 0; i < KEYPAD_COLUMNS; j++) {
      keys[i][j] = KEYPAD_USER_KEY_MAP.charAt( KEYPAD_COLUMNS * i + j); 
    }
  }
  // Creamos una instancia de la clase Keypad
  keypad.begin( makeKeymap( keys));  

}

void loop() {

	// Hacemos un delay de DELAY_CHECK_KEYS milisegundos entre consultas de pulsaciones
	delay(DELAY_CHECK_KEYS);
  // Consultamos si se ha pulsado alguna tecla
  char key = keypad.waitForKey();
//  char key = keypad.getKey();
    Serial.println("key: " + key);
  if (key != 0) {
	// Consultamos si se ha pulsado algún botón
	if (isButtonBackRising(key)) {
		goBackMenu();
                menux.showMenuOption(lcd);
	} else if (isButtonOptionRising(key)) {
		goNextOption();
                menux.showMenuOption(lcd);
	} else if (isButtonSelectRising(key)) {
		presentMenuOption = menux.getPresentMenuOption();
		// Recibimos el valor de la opción validada o un valor vacío si se trata de navegación a submenú
		optionValue = goSelectOption();
                menux.showMenuOption(lcd);

		if (optionValue != 0) {
			doAction(presentMenuOption, optionValue);
		}
	}
  }
}

void doAction(MenuOption menuOption, String value){
	switch (menuOption.getActionCode()) {
		case ACTION_ACTIVATE:
			// Ejecuta acciones para la Action ACTIVATE
			Serial.println("Activando solenoide");
			break;
		case ACTION_DEACTIVATE:
			// Ejecuta acciones para la Action DEACTIVATE
			Serial.println("Desactivando solenoide");
			break;
		default:
			// Ejecuta acciones cuando no se ha definido una Action definida
			break;
	}

}

void goBackMenu() {
	menux.goBackMenu(menux.getPresentOption());
}

void goNextOption() {
	menux.goNextOption(menux.getPresentOption());
}

String goSelectOption() {
	return menux.goSelectOption(menux.getPresentOption());
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
