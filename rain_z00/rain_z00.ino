// La librería Bounce nos proporciona funcionalidad para comprobar el estado de los botones de control de la aplicación.
#include <Bounce.h>
// Se utiliza la librería LiquidCrystal.h para controlar el display LCD
#include "LiquidCrystal.h"

// Se incluyen las librerías MenuOption y Menux que permiten la creación de menúas utilizando un display LCD de 16x2
#include <MenuOption.h>
#include <Menux.h>


/*
rain_z00
 
 Proyecto para automatización de sistemas de riegos.
 
 Fase 1: Activación de una electroválvula controlada por una placa Arduino Uno.
 
 Descripción de la Fase 1:
 
 	- Esta fase consiste en la activación y desactivación del solenoide de una electroválvula de riego. La placa Arduino lee el estado de tres pulsadores para la navegación a través del menú de la aplicación. Este menú proporciona funcionalidad para la activación y desactivación de la electroválvula.
 
 */

// Se utiliza un fichero de configuración externo para aportar los estados iniciales.
#include "constants.h"

// Inicializamos las variables del programa
bool showAction = false;
String optionValue = 0;
MenuOption presentMenuOption;

LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);


// Creamos un objeto para controlar el menú de opciones
Menux menux = Menux();

// Instantiate Bounce objects with a 5 millisecond debounce time
Bounce bouncerBack = Bounce( BUTTON_PREVIOUS,5 ); 
Bounce bouncerOption = Bounce( BUTTON_OPTION,5 ); 
Bounce bouncerSelect = Bounce( BUTTON_SELECT,5 ); 

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println(SERIAL_SPEED);
  // se definen el número de columnas y filas del LCD
  lcd.begin(LCD_COLUMNS, LCD_ROWS);

  // se definen los pines de entrada de los pulsadores
  pinMode(BUTTON_PREVIOUS, INPUT);
  pinMode(BUTTON_OPTION, INPUT);
  pinMode(BUTTON_SELECT, INPUT);

	// Rellenamos las opciones del menú de la aplicación
  menux.addMenuOption( MenuOption( 1, "OPERACIONES", 0, 2, "", 0));
  menux.addMenuOption( MenuOption( 2, "Activar", 1, 0, "ON", 1));
  menux.addMenuOption( MenuOption( 2, "Desactivar", 1, 0, "OFF", 2));
  menux.addMenuOption( MenuOption( 1, "CONFIGURACION", 0, 50, "", 0));
  menux.addMenuOption( MenuOption( 50, "FECHA", 1, 51, "", 0));
  menux.addMenuOption( MenuOption( 51, "Día", 50, 0, "01", 0));
  menux.addMenuOption( MenuOption( 51, "Mes", 50, 0, "01", 0));
  menux.addMenuOption( MenuOption( 51, "Año", 50, 0, "2012", 0));
  menux.addMenuOption( MenuOption( 50, "HORA", 1, 52, "", 0));
  menux.addMenuOption( MenuOption( 52, "Hora", 50, 0, "23", 0));
  menux.addMenuOption( MenuOption( 52, "Minuto", 50, 0, "59", 0));
  menux.addMenuOption( MenuOption( 52, "Segundo", 50, 0, "59", 0));

	// Definimos el código del menú inicial a mostrar
  menux.setPresentMenuCode(MENU_START_CODE);
  menux.setTitleMenuOption(MENU_MAIN_TITLE);

  menux.searchNextOption( 0, MENU_START_CODE);
  menux.showMenuOption(lcd);

}

void loop() {

	// Hacemos un delay de DELAY_CHECK_BUTTONS milisegundos entre consultas de pulsaciones
	delay(DELAY_CHECK_BUTTONS);
	// Consultamos si se ha pulsado algún botón
	if (isButtonBackRising()) {
		goBackMenu();
                menux.showMenuOption(lcd);
	} else if (isButtonOptionRising()) {
		goNextOption();
                menux.showMenuOption(lcd);
	} else if (isButtonSelectRising()) {
		presentMenuOption = menux.getPresentMenuOption();
		// Recibimos el valor de la opción validada o un valor vacío si se trata de navegación a submenú
		optionValue = goSelectOption();
                menux.showMenuOption(lcd);

		if (optionValue != 0) {
			doAction(presentMenuOption, optionValue);
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

bool isButtonBackRising() {
  // Update the debouncer
  bouncerBack.update();

  // Get the risingEdge status
  return bouncerBack.risingEdge();
}

bool isButtonOptionRising() {
  // Update the debouncer
  bouncerOption.update();

  // Get the risingEdge status
  return bouncerOption.risingEdge();
}

bool isButtonSelectRising() {
  // Update the debouncer
  bouncerSelect.update();

  // Get the risingEdge status
  return bouncerSelect.risingEdge();
}
