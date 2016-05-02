// 
// 
// 

#include <math.h>
#include "PixelShow.h"

#define RAINBOW_COLOR_COUNT 4

Color RainbowPattern::RAINBOW_COLORS[RAINBOW_COLOR_COUNT] = {
	Color(150, 0, 0, 0),
	Color(0, 150, 0, 0),
	Color(0, 0, 150, 0),
	Color(0, 0, 0, 150)
};

ColorArray RainbowPattern::RAINBOW = {
	RainbowPattern::RAINBOW_COLORS,
	RAINBOW_COLOR_COUNT
};

RainbowPattern::RainbowPattern(uint16_t nPixels, uint8_t pin, double velocity, ColorArray colors,ColorPattern *decorator) :
	ColorPattern(nPixels, pin, decorator), velocity(velocity), colors(colors)
{}

RainbowPattern::RainbowPattern(NeoPixel *pixels, double velocity, ColorArray colors, ColorPattern *decorator) :
	ColorPattern(pixels, decorator), velocity(velocity), colors(colors)
{}

RainbowPattern::RainbowPattern(NeoPixel *pixels, double velocity, ColorPattern *decorator) :
	RainbowPattern(pixels, velocity, RAINBOW, decorator) {}

ColorArray *RainbowPattern::setColors(ColorArray& colors)
{
	this->colors = colors;
}

void RainbowPattern::act(TimeMillis dt)
{
	// This moving rainbow algorithm is implemented using an extremely simple parametric equation
	// of X(t) = i + vt, where i is the initial position at t = 0, v is the velocity and t is the accumulated time.
	static TimeMillis accTime = 0;
	accTime += dt;

	NeoPixel strip = *this->getPixels();
	size_t nColors = this->colors.size;
	uint16_t nPixels = strip.numPixels();

	// Establish parameters
	uint8_t pixelsPerColor = floor(nPixels / nColors);
	unsigned long parameter = accTime * velocity; // Variable side of equation

	// Assign grouped colors according to above parameters
	for (size_t i = 0; i < nColors; i++)
		for (uint8_t j = 0; j < pixelsPerColor; j++)
			strip.setPixelColor((uint16_t)(i*pixelsPerColor + j), this->colors.arr[(i + parameter) % nColors].pixel);

	// Determine error and fill untouched pixels with end color
	size_t lastPixelTouched = pixelsPerColor * nColors;
	while (lastPixelTouched++ < nPixels)
		strip.setPixelColor((uint8_t)lastPixelTouched, this->colors.arr[(nColors - 1 + parameter) % nColors].pixel);

	strip.show();
}