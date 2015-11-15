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

#include <Adafruit_NeoPixel.h>

using NeoPixel = Adafruit_NeoPixel;

//  Variables
const int pulsePin = 10;                 // Pulse Sensor purple wire connected to analog pin 0
const int blinkPin = 6;                // pin to blink led at each beat
const int fadePin = 12;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

								  // Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

typedef const struct Color {
	using PixelColor = uint32_t;
	
	byte red;
	byte green;
	byte blue;
	PixelColor pixel;

	Color(byte red, byte green, byte blue) : red(red), green(green), blue(blue) {
		pixel = NeoPixel::Color(red, green, blue);
	}
} Color;

NeoPixel pixel = NeoPixel(1, blinkPin, NEO_GRB + NEO_KHZ800);
Color OFF_COLOR = { 255, 0, 0 };
Color ON_COLOR = { 0, 255, 0 };

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


void setup() {
	Serial.begin(115200);             // we agree to talk fast!
	interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 

	pixel.begin();
	pixel.setPixelColor(1, 255, 0, 0);
	pixel.setBrightness(128);
	pixel.show();

}


//  Where the Magic Happens
void loop() {
	serialOutput();

	if (QS == true) {     //  A Heartbeat Was Found
						  // BPM and IBI have been Determined
						  // Quantified Self "QS" true when arduino finds a heartbeat
		pixel.setPixelColor(0, ON_COLOR.pixel);
		fadeRate = 255;         // Makes the LED Fade Effect Happen
								// Set 'fadeRate' Variable to 255 to fade LED with pulse
		serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
		QS = false;                      // reset the Quantified Self flag for next time    
	}
	else {
		pixel.setPixelColor(0, OFF_COLOR.pixel);
	}

	pixel.show();
	ledFadeToBeat(); 
	delay(10);
}