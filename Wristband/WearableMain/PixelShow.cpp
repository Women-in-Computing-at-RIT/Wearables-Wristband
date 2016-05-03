// 
// 
// 
#include "PixelShow.h"
#include <math.h>

#define RAINBOW_COLOR_COUNT 4

Color RainbowPattern::RAINBOW_COLORS[RAINBOW_COLOR_COUNT] = {
	Color(30, 0, 0, 0),
	Color(0, 30, 0, 0),
	Color(0, 0, 30, 0),
	Color(0, 0, 0, 30)
};

ColorArray RainbowPattern::RAINBOW = {
	RainbowPattern::RAINBOW_COLORS,
	RAINBOW_COLOR_COUNT
};

RainbowPattern::RainbowPattern(uint16_t nPixels, uint8_t pin, TimeMillis period, ColorArray& colors) :
	ColorPattern(nPixels, pin, period), colors(colors)
{
}

RainbowPattern::RainbowPattern(NeoPixel *pixels, TimeMillis period, ColorArray& colors) :
	ColorPattern(pixels, period), colors(colors)
{
}

RainbowPattern::RainbowPattern(NeoPixel *pixels, TimeMillis period) :
	RainbowPattern(pixels, period, RAINBOW) {}

void RainbowPattern::setColors(const ColorArray& colors)
{
	this->colors = colors;
}

void RainbowPattern::getColors(ColorArray& out)
{
	uint16_t nPixels = getPixels()->numPixels();
	for (size_t i = 0; i < out.size && i < nPixels; i++)
		out.arr[i] = colors.arr[i];
}

void RainbowPattern::apply(NeoPixel& strip, ColorArray& colors)
{
	static uint8_t ticks = 0;
	uint16_t nPixels = strip.numPixels();

	for (uint16_t i = 0; i < nPixels; i++)
	{
		Color& colData = colors.arr[i % colors.size];
		strip.setPixelColor((i + (ticks % colors.size)) % nPixels, colData.components.red, colData.components.green, colData.components.blue, colData.components.white);
	}

	strip.show();
	ticks += 1;
}

void RainbowPattern::act()
{
	static uint8_t ticks = 0;
	NeoPixel strip = *getPixels();
	uint16_t nPixels = strip.numPixels();
	for (uint16_t i = 0; i < nPixels; i++)
	{
		Color& colData = colors.arr[i % colors.size];
		strip.setPixelColor((i + (ticks % colors.size)) % nPixels, colData.components.red, colData.components.green, colData.components.blue, colData.components.white);
	}

	strip.show();
	ticks += 1;
}