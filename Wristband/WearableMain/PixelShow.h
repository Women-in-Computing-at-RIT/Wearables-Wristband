// PixelShow.h

#ifndef _PIXELSHOW_h
#define _PIXELSHOW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PixelShowBase.h"

class RainbowPattern : public ColorPattern {
public:
	RainbowPattern(uint16_t nPixels, uint8_t pin, double velocity, ColorArray colors, ColorPattern *decorator);
	RainbowPattern(NeoPixel *pixels, double velocity, ColorArray colors, ColorPattern *decorator);
	RainbowPattern(NeoPixel *pixels, double velocity, ColorPattern *decorator);
	ColorArray *setColors(ColorArray& colors);
protected:
	void act(TimeMillis dt) override;
private:
	static Color RAINBOW_COLORS[];
	static ColorArray RAINBOW;
	ColorArray& colors;
	double velocity;
};

#endif

