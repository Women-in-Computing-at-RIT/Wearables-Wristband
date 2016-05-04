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
	static Color RAINBOW_ARR[RAINBOW_ARR_SIZE];
	static ColorArray RAINBOW;
	RainbowFunction(const ColorArray& colors);
	RainbowFunction();
	ColorArray& mutate(ColorArray& input) override;
private:
	const ColorArray& colors;
};

class ChaseFunction : public ColorFunction
{
public:
	ColorArray& mutate(ColorArray& input) override;
};

class DeferFunction : public ColorFunction
{
public:
	DeferFunction(uint16_t deferrals);
	ColorArray& apply(ColorArray& input) override;
private:
	uint16_t defers;
};

class PeriodicFunction : public ColorFunction
{
public:
	PeriodicFunction(TimeMillis period);
	ColorArray& apply(ColorArray& input) override;
	TimeMillis getPeriod(void) const;
	void setPeriod(TimeMillis millis);
	void delay(TimeMillis millis);
	void reset(void);
private:
	TimeMillis start;
	TimeMillis period;
};

// PulseFunction by measuring delta time and scaling the brightness linearly (This is pretty similar to periodic)

#endif
