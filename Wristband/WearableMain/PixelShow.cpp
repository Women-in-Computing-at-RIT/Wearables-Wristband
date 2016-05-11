// 
// 
// 
#include <math.h>
#include "PixelShow.h"
#include "WearablesConstants.h"
#include "WearablesUtility.h"

#define RAINBOW_COLOR_COUNT 4

Color RainbowFunction::RAINBOW_ARR[RAINBOW_ARR_SIZE] = {
	createColor(48, 0, 0, 0),
	createColor(0, 48, 0, 0),
	createColor(0, 0, 48, 0),
	createColor(0, 0, 0, 48)
};

ColorArray RainbowFunction::RAINBOW = { RainbowFunction::RAINBOW_ARR, RAINBOW_ARR_SIZE };

RainbowFunction::RainbowFunction(const ColorArray& colors) :
	ColorFunction(), colors(colors) {}

RainbowFunction::RainbowFunction() : RainbowFunction(RainbowFunction::RAINBOW) {}

ColorArray& RainbowFunction::mutate(ColorArray& pixels)
{
	const ColorArray& colors = this->colors;
	uint8_t nPixels = pixels.size;
	uint8_t nColors = colors.size;

	static char buf[500];
	for (uint8_t i = 0; i < nPixels; i++) {
		pixels.arr[i] = colors.arr[i % nColors];
		sprintf(buf, "PIXEL %d is COLOR %d which is %ld", i, i % nColors, colors.arr[i%nColors].pixel);
		Serial.println(buf);
	}

	return pixels;
}

ColorArray& ChaseFunction::mutate(ColorArray& pixels)
{
	WiCUtil::arrayRightRotate(pixels.arr, 1, pixels.size);
	return pixels;
}

DeferFunction::DeferFunction(uint16_t deferrals) : defers(deferrals) {}
ColorArray& DeferFunction::apply(ColorArray& input)
{
	if (defers <= 0)
		return ColorFunction::apply(input);
	else
	{
		defers--;
		return input;
	}
}

PeriodicFunction::PeriodicFunction(TimeMillis period) : start(millis()), period(period)
{}

ColorArray& PeriodicFunction::apply(ColorArray& input)
{
	TimeMillis stop = millis();
	TimeMillis diff = stop - start;

	if (diff >= period)
	{
		start = stop;
		return ColorFunction::apply(input);
	}
	else
		return input;
}

TimeMillis PeriodicFunction::getPeriod(void) const
{
	return this->period;
}

void PeriodicFunction::setPeriod(TimeMillis millis)
{
	this->period = period;
}

void PeriodicFunction::delay(TimeMillis ms)
{
	this->start = millis() + ms;
}

void PeriodicFunction::reset(void)
{
	this->start = millis();
}