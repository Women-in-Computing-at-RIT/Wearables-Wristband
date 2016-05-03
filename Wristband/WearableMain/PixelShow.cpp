// 
// 
// 
#include "PixelShow.h"
#include <math.h>

#define RAINBOW_COLOR_COUNT 4

const Color RainbowFunction::RAINBOW_ARR[RAINBOW_ARR_SIZE] = {
	Color(48, 0, 0, 0),
	Color(0, 48, 0, 0),
	Color(0, 0, 48, 0),
	Color(0, 0, 0, 48)
};

const ColorArray RainbowFunction::RAINBOW = ColorArray(RainbowFunction::RAINBOW_ARR, RAINBOW_ARR_SIZE);

RainbowFunction::RainbowFunction(const ColorArray& colors) :
	ColorFunction(), colors(colors) {}

RainbowFunction::RainbowFunction() : RainbowFunction(RainbowFunction::RAINBOW) {}

ColorArray& RainbowFunction::mutate(ColorArray& pixels) const
{
	uint8_t nPixels = pixels.size();
	uint8_t nColors = colors.size();

	for (uint8_t i = 0; i < nPixels; i++)
		pixels.set(i, this->colors.get(i % nColors));
}

ColorArray& ChaseFunction::mutate(ColorArray& pixels) const
{
	uint8_t nPixels = pixels.size();
	
	Color last = pixels.get(nPixels - 1);
	for (uint8_t i = 0; i < nPixels - 1; i++)
		pixels.set(i + 1, pixels.get(i));

	pixels.set(0, last);
	return pixels;
}

DeferFunction::DeferFunction(uint16_t deferrals) : defers(deferrals) {}
ColorArray& DeferFunction::_apply(ColorArray& input)
{
	if (defers <= 0)
		return ColorFunction::_apply(input);
	else
	{
		defers--;
		return input;
	}
}

PeriodicFunction::PeriodicFunction(TimeMillis period)
{
	this->start = millis();
	this->period = period;
}

ColorArray& PeriodicFunction::_apply(ColorArray& input)
{
	TimeMillis stop = millis();
	TimeMillis diff = stop - start;

	if (diff >= period)
	{
		start = stop;
		return ColorFunction::_apply(input);
	}
	else
		return input;
}