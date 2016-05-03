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
/// A layout of a function that takes an input and returns an input in an immutable fashion. Functions can be composed
/// (using '+' or f(g)).
/// </summary>
/// <remarks>
/// Although the input is taken as a reference to a ColorArray, a copy is created using the ColorArray Copy Constructor and 
/// the copy is mutated and returned. This allows functions to have mutable logic but still reduce side effects.
/// </remarks>
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

/// <summary>
/// A composition of two functions, applying the second then the first. (f(x), g(x)) is executed as f(g(x)).
/// </summary>
class CombinedColorFunction : public ColorFunction {
public:
	CombinedColorFunction(ColorFunction& f, ColorFunction& g);
	ColorArray& _apply(ColorArray& input) override;
	ColorArray& mutate(ColorArray& input) const override;
	ColorFunction& f;
	ColorFunction& g;
};

/*
	Takes a pixel strip and wipes all the pixels to a single color.
*/
void pixelColorWipe(NeoPixel& strip, Color& color);

#endif