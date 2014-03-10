#ifndef Device_h
#define Device_h

#include "Arduino.h"
#include "RainPComm.h"

class Device {
public:
	Device();
	Device(int id, int net, RainPComm * pProtocol) ;
 
	void initialize(int id, int  net);
	void initialize(int id, int  net, RainPComm * pProtocol);
	const int getDeviceId() ;
	const int getNetCode() ;
	const byte getState() ;
	bool deactivate(char * command);
	bool activate(char * command);

private:
	int deviceId;
	int netCode;
	RainPComm * pProtocol;
	byte state;	// 0 = No activated; 1 = Activated;
	// Constantes de configuracin de dispositivos
	const int NOT_ASSIGNED_DEVICE_CODE = -1;  // Cdigo de dispositivo para dispositivos sin asignar
	const int NOT_ASSIGNED_NET_CODE = -1;  // Cdigo de red sin asignar
	const int ACTIVE_DEVICE = 1;  // Dispositivo activo
	const int INACTIVE_DEVICE = 0; // Dispositivo inactivo

};
 
#endif
