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

#define setOnboard(state) do { pinMode(ONBOARD_LED_PIN, state); } while(0)

void setOnboardPixel(const Color& color);
void setOnboardLed(boolean on);

typedef unsigned long int TimeMillis;

typedef struct {
	Color *arr;
	size_t size;
} ColorArray;

class ColorPattern 
{
public:
    ColorPattern(uint16_t pixelCount, uint8_t pin, ColorPattern *decorator);
    ColorPattern(NeoPixel *pixels, ColorPattern *decorator);
    ~ColorPattern();
    void tick(TimeMillis forcedDelta);
	void tick();
	friend void pixelColorWipe(ColorPattern&, Color&);
protected:
	NeoPixel *getPixels(void);
    virtual void act(TimeMillis deltaTime) = 0;
private:
	boolean alloc;
    NeoPixel *strip;
	ColorPattern *wrapper;
	TimeMillis timestamp;
};

void pixelColorWipe(NeoPixel& strip, Color& color);
void pixelColorWipe(ColorPattern& pattern, Color& color);

#endif

