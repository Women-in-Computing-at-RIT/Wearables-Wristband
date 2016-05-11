// NeoPixelStrip.h

#ifndef _NEOPIXELSTRIP_H
#define _NEOPIXELSTRIP_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <Adafruit_NeoPixel.h>

typedef Adafruit_NeoPixel NeoPixel;

/// Represents an RGB Color, 
union Color {
	uint32_t pixel;
	struct {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t white;
	} components;
};

Color createColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
Color createColor(uint8_t red, uint8_t green, uint8_t blue);
Color createColor(uint32_t hex);
Color createWhite(uint8_t intensity);
Color createColor();

void dissectColor(Color& c, uint8_t comps[4]);

inline boolean isBlackColor(const uint32_t& pixel);
inline boolean isWhiteColor(const uint32_t& pixel);
inline boolean isBlackColor(const Color& color);
inline boolean isWhiteColor(const Color& color);

#endif


