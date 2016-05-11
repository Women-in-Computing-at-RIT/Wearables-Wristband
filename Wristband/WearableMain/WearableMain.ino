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

#include "WearablesConstants.h"
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

#define NUM_PIXEL_STRAP 2
#define NUM_RAINBOW 3

#define MIN_BEAT_DELAY 200
#define MAX_BEAT_DELAY 1000
#define SLOPE_BEAT_DELAY (15.0/4.0)


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

const Color OFF_COLOR = createColor(0, 0, 24);
const Color ON_COLOR = createColor(0, 128, 0);

Color effect[NUM_RAINBOW] = {
	//createColor(64, 0, 0),
	//createColor(0, 64, 0),
	//createColor(0, 0, 64),
	//createWhite(16),
	createColor(0x4D1F5B),
	createColor(0xEDE8EE),
	createWhite(16)
};

ColorArray rainbowArray = { effect, NUM_RAINBOW };

RainbowFunction rainbowFn = RainbowFunction(rainbowArray);
ChaseFunction chaseFn = ChaseFunction();
PeriodicFunction periodicFn = PeriodicFunction(300);

Color strap[NUM_RAINBOW];
ColorArray strapArray = { strap, NUM_RAINBOW };

void setup() {
#if WiC_DEBUG
	while (!Serial);
	delay(500);
#endif

	WiCLog::info("WiC_DEBUG = %s", WiC_DEBUG ? "YES" : "NO");
	Serial.begin(115200);             // we agree to talk fast!
	interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS

	strip.begin();
	strip.setBrightness(64);
	strip.show();

	board.reset();
	board.setPixelBrightness(48);

#if WiC_DEBUG
	uint8_t compos[4];
	for (size_t i = 0; i < NUM_RAINBOW; i++)
	{
		dissectColor(effect[i], compos);
		WiCLog::debug("R: %03u, G: %03u, B: %03u, W: %03u -- Hex: 0x%02X%02X%02X%02X, Val: %14lu", compos[0], compos[1], compos[2], compos[3], compos[0], compos[1], compos[2], compos[3], effect[i].pixel);
	}

	Color c = createWhite(128);
#endif

	periodicFn.compose(chaseFn);
	strapArray = rainbowFn.mutate(strapArray);
	strapArray.stripOptions.gammaOverride = true;
	strapArray.stripOptions.gamma = 16;
	if (!comms.initialize())
		Serial.println("Failed ot initialize bt");
	else
		Serial.println("Initialized BT");
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

	if (comms.isConnected())
		bluetoothHandler();

	TimeMillis possiblePeriod = MIN_BEAT_DELAY + round(SLOPE_BEAT_DELAY*BPM);
	periodicFn.setPeriod(constrain(possiblePeriod, MIN_BEAT_DELAY, MAX_BEAT_DELAY));
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

#if WiC_LUX_SENSOR_CODE
	luxLoop();
#endif

	applyColorArray(strapArray, strip);
	strip.show(); 

}
