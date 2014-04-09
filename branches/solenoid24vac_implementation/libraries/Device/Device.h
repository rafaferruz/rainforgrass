#ifndef Device_h
#define Device_h

#include "Arduino.h"
#include "RainPComm.h"

// Constantes de configuracin de dispositivos
extern const int NOT_ASSIGNED_DEVICE_CODE;  // Cdigo de dispositivo para dispositivos sin asignar
extern const int NOT_ASSIGNED_NET_CODE;  // Cdigo de red sin asignar
extern const int ACTIVE_DEVICE;  // Dispositivo activo
extern const int INACTIVE_DEVICE; // Dispositivo inactivo
// Constantes de tipos de dispositivos
extern const int ELECTRO_VALVE;  // Electroválvula
extern const int HUMIDITY_SENSOR;  // Sensor de humedad
extern const int TEMPERATURE_SENSOR;  // Sensor de temperatura

class Device {
public:
	Device();
	Device(unsigned int id, unsigned int net, RainPComm * pProtocol) ;
	virtual ~Device();
 
	void initialize( unsigned int id, unsigned int  net);
	void initialize( unsigned int id, unsigned int  net, RainPComm * pProtocol);
	const unsigned short getDeviceType() ;
	const unsigned int getDeviceId() ;
	const unsigned int getNetCode() ;
	const byte getState() ;
	virtual bool deactivate(char * command) ;
	virtual bool activate(char * command) ;

protected:
	unsigned short deviceType;
	unsigned int deviceId;
	unsigned int netCode;
	RainPComm * pProtocol;
	byte state;	// INACTIVE_DEVICE = No activated; ACTIVE_DEVICE = Activated;


};
 
#endif
