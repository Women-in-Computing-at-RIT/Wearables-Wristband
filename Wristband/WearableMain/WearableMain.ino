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

#include "NeoPixelStrip.h"
#include "PixelShow.h"

//using NeoPixel = Adafruit_NeoPixel;

//  Variables
const int pulsePin = A10;
const int blinkPin = A7;
const int fadePin = 12;
int fadeRate = 0;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

NeoPixel strip = NeoPixel(5, blinkPin, NEO_GRB + NEO_KHZ800);
const Color OFF_COLOR(24, 0, 0);
const Color ON_COLOR(0, 128, 0);

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse

RainbowPattern pattern(&strip, 1.0 / 10000.0, nullptr);

void setup() {
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS

  strip.begin();
  strip.setPixelColor(2, ON_COLOR.pixel);
//  strip.setPixelColor(1, 255, 0, 0);
//  strip.setBrightness(128);
  strip.show();

}

void colorWipe(NeoPixel, Color);
//  Where the Magic Happens
void loop() {
  serialOutput();

  if (QS == true) {     //  A Heartbeat Was Found
    // BPM and IBI have been Determined
    // Quantified Self "QS" true when arduino finds a heartbeat
    colorWipe(strip, ON_COLOR);
    fadeRate = 255;         // Makes the LED Fade Effect Happen
    // Set 'fadeRate' Variable to 255 to fade LED with pulse
    serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
    QS = false;                      // reset the Quantified Self flag for next time
  }
  else {
    colorWipe(strip, OFF_COLOR);
  }

  strip.show();
  pattern.tick();

  if (Pulse)
	  setOnboardPixel(ON_COLOR);
  else
	  setOnboardPixel(OFF_COLOR);

  delay(10);
}

void colorWipe(NeoPixel strip, Color color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    if(i == 2)
      continue;
    strip.setPixelColor(i, color.pixel);
  }
  strip.show();
}
