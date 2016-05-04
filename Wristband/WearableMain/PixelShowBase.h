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
struct ColorArray
{
	Color *arr;
	uint8_t size;
	struct {
		boolean gammaOverride = false;
		uint8_t gamma = 0;
		float colorScale = 1.0f;
	} stripOptions;
};

ColorArray createColorArray(Color arr[], uint8_t size);
ColorArray copyColorArray(const ColorArray& original);
void createColorArray(ColorArray& colorArray, Color arr[], uint8_t size);
void copyColorArray(const ColorArray& original, ColorArray& cpy);
void applyColorArray(ColorArray& colorArray, NeoPixel& strip);

/// <summary>
/// Simple utility class for managing the state of things that are attached to the Flora Board itself like the 
/// onboard NeoPixel and the onboard LED.
/// </summary>
class FloraBoard
{
public:
	FloraBoard();
	~FloraBoard();
	void setPixelBrightness(uint8_t brightness);
	void setOnboardPixel(const Color& color);
	void setOnboardLed(boolean on);
	uint8_t getPixelBrightness(void);
	uint32_t getOnboardPixel(void);
	boolean getOnboardLed(void);
	void reset(void);
private:
	uint32_t pixColor;
	boolean ledOn;
	NeoPixel onboardPixel;
};

/// <summary>
/// A layout of a function that takes an input and returns an input in an immutable fashion. Functions can be composed.
/// </summary>
/// <remarks>
/// Although the input is taken as a reference to a ColorArray, a copy is created using the ColorArray Copy Constructor and 
/// the copy is mutated and returned. This allows functions to have mutable logic but still reduce side effects.
/// </remarks>
class ColorFunction {
public:
	ColorFunction();
	virtual ColorArray& apply(ColorArray& input);
	ColorArray& operator()(ColorArray& input);
	void compose(ColorFunction &inner);
	virtual ColorArray& mutate(ColorArray& input);
protected:
	ColorFunction(ColorFunction *inner);
	ColorFunction *inner = nullptr;
};

/*
	Takes a pixel strip and wipes all the pixels to a single color.
*/
void pixelColorWipe(NeoPixel& strip, Color& color);

#endif