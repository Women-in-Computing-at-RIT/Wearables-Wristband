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
	RainbowPattern(uint16_t nPixels, uint8_t pin, TimeMillis period, ColorArray& colors);
	RainbowPattern(NeoPixel *pixels, TimeMillis period, ColorArray& colors);
	RainbowPattern(NeoPixel *pixels, TimeMillis period);
	void setPeriod(TimeMillis period);
	void setColors(const ColorArray& colors);
	void getColors(ColorArray& out);
	void apply(NeoPixel& strip, ColorArray& cols);
	static ColorArray RAINBOW;
protected:
	void act() override;
private:
	static Color RAINBOW_COLORS[];
	ColorArray& colors;
};

#endif

