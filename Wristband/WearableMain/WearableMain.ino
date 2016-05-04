/*
  Name:		WearableMain.ino
  Created:	11/10/2015 11:04:47 PM
  Author:	Matthew
*/

/*
  ----------------------Notes----------------------  ----------------------
  This code :
  1) Blinks an LED to User's Live Heartbeat
  3) Determines BPM
  4) Prints All of the Above to Serial

  Read Me :
  https ://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md
  ----------------------       ----------------------  ----------------------
*/

#include "WearablesUtility.h"
#include <SPI.h>
#if not defined(_VARIANT_ARUDINO_DUE_X_) && not defined(_VARIANT_ARDUINO_ZERO_)
#include <SoftwareSerial.h>
#endif

#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_NeoPixel.h>

#include "BluefruitConfig.h"
#include "BluefruitComms.h"
#include "NeoPixelStrip.h"
#include "PixelShow.h"

#define NUM_PIXEL_STRAP 3


// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse


//  Variables
const int pulsePin = A10;
const int blinkPin = A7;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

NeoPixel strip = NeoPixel(NUM_PIXEL_STRAP, blinkPin, NEO_GRB + NEO_KHZ800);
BluefruitComms comms;
FloraBoard board;

const Color OFF_COLOR(24, 0, 0);
const Color ON_COLOR(0, 128, 0);

Color effect[NUM_PIXEL_STRAP] = {
	Color(64, 0, 0, 0),
	Color(0, 64, 0, 0),
	Color(0, 0, 64, 0)
};

RainbowFunction rainbowFn = RainbowFunction();
ChaseFunction chaseFn = ChaseFunction();
PeriodicFunction periodicFn = PeriodicFunction(2000);

ColorArray effectArr = { effect, NUM_PIXEL_STRAP };
ColorArray strapArray = { effect, NUM_PIXEL_STRAP };

void setup() {
	while (!Serial);
	delay(500);
	Serial.begin(115200);             // we agree to talk fast!
	interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS

	strip.begin();
	strip.setBrightness(12);
	strip.show();

	board.reset();
	board.setPixelBrightness(48);

	delay(2000);

	periodicFn.compose(chaseFn);
	strapArray = rainbowFn.mutate(strapArray);
	//comms.initialize();

}

//  Where the Magic Happens
void loop() {
	serialOutput();

	if (QS == true) {     //  A Heartbeat Was Found
	  // BPM and IBI have been Determined
	  // Quantified Self "QS" true when arduino finds a heartbeat
		serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
		QS = false;                      // reset the Quantified Self flag for next time
	}

	periodicFn.apply(strapArray);

	if (Pulse)
	{
		board.setOnboardPixel(ON_COLOR);
		board.setOnboardLed(true);
	}
	else
	{
		board.setOnboardPixel(OFF_COLOR);
		board.setOnboardLed(false);
	}

	applyColorArray(strapArray, strip);
	strip.show(); 

	delay(10);
}
