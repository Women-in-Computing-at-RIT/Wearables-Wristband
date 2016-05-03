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

/// <summary>
/// A wrapper around an array of colors, keeps track of size and can be extended for further
/// enhancement.
///</summary>
class ColorArray {
public:
	ColorArray(const Color arr[], uint8_t size);
	ColorArray(const ColorArray& orig);
	~ColorArray();
	Color& get(uint8_t i) const;
	void set(uint8_t i, Color& color);
	uint8_t size(void) const;
	void apply(NeoPixel& strap);
private:
	Color *arr;
	uint8_t length;
};

/// <summary>
/// Simple utility class for managing the state of things that are attached to the Flora Board itself like the 
/// onboard NeoPixel and the onboard LED.
/// </summary>
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

/// <summary>
///
/// </summary>
class ColorFunction {
public:
	ColorFunction();
	ColorArray apply(const ColorArray& input);
	ColorFunction operator+(ColorFunction& f);
	ColorFunction operator()(ColorFunction& g);
	ColorArray operator()(ColorArray& input);
	virtual ColorArray& _apply(ColorArray& input);
	virtual ColorArray& mutate(ColorArray& input) const;
protected:
	ColorFunction(ColorFunction *inner);
	ColorFunction *inner;
};

class CombinedColorFunction : public ColorFunction {
public:
	CombinedColorFunction(ColorFunction& f, ColorFunction& g);
	ColorArray& _apply(ColorArray& input) override;
	ColorArray& mutate(ColorArray& input) const override;
	ColorFunction& f;
	ColorFunction& g;
};

void pixelColorWipe(NeoPixel& strip, Color& color);

#endif