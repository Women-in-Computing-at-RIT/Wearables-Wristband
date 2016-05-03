// PixelShow.h

#ifndef _PIXELSHOW_h
#define _PIXELSHOW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PixelShowBase.h"
#define RAINBOW_ARR_SIZE 4

class RainbowFunction : public ColorFunction
{
public:
	static const Color RAINBOW_ARR[RAINBOW_ARR_SIZE];
	static const ColorArray RAINBOW;
	RainbowFunction(const ColorArray& colors);
	RainbowFunction();
	ColorArray& mutate(ColorArray& input) const override;
private:
	const ColorArray& colors;
};

class ChaseFunction : public ColorFunction
{
public:
	ColorArray& mutate(ColorArray& input) const override;
};

class DeferFunction : public ColorFunction
{
public:
	DeferFunction(uint16_t deferrals);
	ColorArray& _apply(ColorArray& input) override;
private:
	uint16_t defers;
};

class PeriodicFunction : public ColorFunction
{
public:
	PeriodicFunction(TimeMillis period);
	ColorArray& _apply(ColorArray& input) override;
private:
	TimeMillis start;
	TimeMillis period;
};
#endif

