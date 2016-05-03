#include "PixelShowBase.h"

ColorPattern::ColorPattern(uint16_t numPixels, uint8_t pin, TimeMillis period)
{
	this->alloc = true;
	this->strip = new NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
	this->start = millis();
	this->period = period;
	this->ticks = 0;
}

ColorPattern::ColorPattern(NeoPixel *pixels, TimeMillis period)
{
	this->alloc = false;
	this->strip = pixels;
	this->start = millis();
	this->period = period;
	this->ticks = 0;
}

ColorPattern::~ColorPattern()
{
	if (this->alloc)
		delete this->strip;
}

void ColorPattern::tick(void)
{
	TimeMillis stop = millis();
	TimeMillis diff = stop - start;
	static char buff[500];
	sprintf(buff, "Start: %ld Stop: %ld Diff: %ld Period: %ld Ticks: %ld", start, stop, diff, period, this->ticks);
	Serial.println(buff);
	if (diff >= period)
	{
		start = stop;
		this->act();
		this->ticks += 1;
	}
}

size_t ColorPattern::getTicks(void)
{
	return ticks;
}

NeoPixel *ColorPattern::getPixels(void)
{
	return this->strip;
}

FloraBoard::FloraBoard() : onboardPixel{ 1, ONBOARD_PIXEL_PIN, NEO_GRB + NEO_KHZ800 }, ledOn(false), pixColor(0)
{
	this->onboardPixel.begin();
	this->onboardPixel.show();

	pinMode(ONBOARD_LED_PIN, OUTPUT);
}

void FloraBoard::setOnboardPixel(const Color& color)
{
	this->onboardPixel.setPixelColor(0, this->pixColor = color.pixel);
	this->onboardPixel.show();
}

void FloraBoard::setOnboardLed(boolean on)
{
	digitalWrite(ONBOARD_LED_PIN, (ledOn = on) ? HIGH : LOW);
}

uint32_t FloraBoard::getOnboardPixel(void)
{
	return this->pixColor;
}

boolean FloraBoard::getOnboardLed(void)
{
	return this->ledOn;
}

void pixelColorWipe(NeoPixel& strip, const Color& color)
{
	for (uint16_t i = 0; i < strip.numPixels(); i++)
		strip.setPixelColor(i, color.pixel);
}

void pixelColorWipe(ColorPattern& pattern, const Color& color)
{
	pixelColorWipe(*pattern.getPixels(), color);
}