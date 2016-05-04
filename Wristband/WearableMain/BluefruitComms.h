// BluefruitComms.h

#ifndef _BLUEFRUITCOMMS_h
#define _BLUEFRUITCOMMS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SPI.h>
#if not defined(_VARIANT_ARUDINO_DUE_X_) && not defined(_VARIANT_ARDUINO_ZERO_)
#include <SoftwareSerial.h>
#endif

#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLE.h>
#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE 1

typedef Adafruit_BluefruitLE_UART Bluefruit;

class BluefruitComms
{
public:
	BluefruitComms();
	~BluefruitComms();
	boolean initialize();
	Bluefruit *getBluefruit();
private:
	void factoryReset(void);
	Bluefruit *communicator;
	boolean connected;
};

#endif


