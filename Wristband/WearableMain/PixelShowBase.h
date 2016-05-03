// PixelShow.h

#ifndef _PIXELSHOW_BASE_h
#define _PIXELSHOW_BASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <stdlib.h>
#include "NeoPixelStrip.h"

#define ONBOARD_LED_PIN 7
#define ONBOARD_PIXEL_PIN 8

// TODO STOP TRYING TO CONTROL EVERYTHING! Make Patterns functions that can be composed together as opposed to animation engines!

typedef unsigned long int TimeMillis;

struct ColorArray {
	Color *arr;
	size_t size;
};

class FloraBoard
{
public:
	FloraBoard();
	void setOnboardPixel(const Color& color);
	void setOnboardLed(boolean on);
	uint32_t getOnboardPixel(void);
	boolean getOnboardLed(void);
private:
	uint32_t pixColor;
	boolean ledOn;
	NeoPixel onboardPixel;
};

class ColorFunction {
public:
	ColorArray apply(ColorArray& input);
};

class ColorPattern 
{
public:
    ColorPattern(uint16_t pixelCount, uint8_t pin, TimeMillis period);
    ColorPattern(NeoPixel *pixels, TimeMillis period);
    ~ColorPattern();
	void tick(void);
	size_t getTicks(void);
	NeoPixel *getPixels(void);
	friend void pixelColorWipe(ColorPattern&, Color&);
protected:
	TimeMillis period;
    virtual void act() = 0;
private:
	boolean alloc;
    NeoPixel *strip;
	TimeMillis start;
	size_t ticks;
};

void pixelColorWipe(NeoPixel& strip, const Color& color);
void pixelColorWipe(ColorPattern& pattern, const Color& color);

#endif

