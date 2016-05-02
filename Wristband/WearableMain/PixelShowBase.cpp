#include "PixelShowBase.h"

ColorPattern::ColorPattern(uint16_t numPixels, uint8_t pin, ColorPattern *decorator) :
	alloc(true), wrapper(decorator), timestamp(millis())
{
	this->strip = new NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
}

ColorPattern::ColorPattern(NeoPixel *pixels, ColorPattern *decorator) : 
	alloc(false), strip(pixels), wrapper(decorator), timestamp(millis()) 
{}

ColorPattern::~ColorPattern()
{
	if (this->alloc)
		delete this->strip;
}

void ColorPattern::tick(TimeMillis forcedDelta)
{
	// If we are given a delta time then we are wrapping a primary pattern, use theirs to synchronize
	TimeMillis dt;
	if (forcedDelta != 0)
		dt = forcedDelta;
	else
		dt = millis() - timestamp;

	if (this->wrapper != nullptr)
		this->wrapper->tick(dt); // Force wrappers to use same delta time

	this->act(dt);

	// If we were forced lets not waste our time retrieving our own timestamp
	if(forcedDelta != 0)
		timestamp = millis();
}

void ColorPattern::tick()
{
	tick(0);
}

NeoPixel *ColorPattern::getPixels(void)
{
	return this->strip;
}

void pixelColorWipe(NeoPixel& strip, Color& color)
{
	for (uint16_t i = 0; i < strip.numPixels(); i++)
		strip.setPixelColor(i, color.pixel);
}

void pixelColorWipe(ColorPattern& pattern, Color& color)
{
	pixelColorWipe(*pattern.getPixels(), color);
}

static NeoPixel onboard = { 1, ONBOARD_PIXEL_PIN, NEO_GRB + NEO_KHZ800 };
void setOnboardPixel(const Color& color)
{
	static boolean init = false;

	if (!init)
	{
		onboard.begin();
		init = true;
	}

	onboard.setPixelColor(0, color.pixel);
	onboard.show();
}

void setOnboardLed(boolean on)
{
  static boolean init = false;
  if(!init)
  {
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    init = true;
  }

  digitalWrite(ONBOARD_LED_PIN, (on ? HIGH : LOW));
}

