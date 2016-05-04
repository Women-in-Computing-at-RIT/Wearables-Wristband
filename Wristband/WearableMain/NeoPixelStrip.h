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
typedef union Color {
	uint32_t pixel;
	struct {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t white;
	} components;

	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white = 0) {
		this->pixel = NeoPixel::Color(red, green, blue, white);
	}

	Color(uint32_t hexcode) {
		uint8_t red, green, blue, white = 0;
		if (hexcode <= 0xFFFFFF) {
			red = (hexcode >> 16) & 0xFF;
			green = (hexcode >> 8) & 0xFF;
			blue = hexcode & 0xFF;
		}
		else {
			red = (hexcode >> 24) & 0xFF;
			green = (hexcode >> 16) & 0xFF;
			blue = (hexcode >> 8) & 0xFF;
			white = hexcode & 0xFF;
		}

		this->pixel = NeoPixel::Color(red, green, blue, white);
	}

	Color() {
		pixel = NeoPixel::Color(0, 0, 0, 0);
	}
} Color;

inline boolean isBlackColor(const uint32_t& pixel);
inline boolean isWhiteColor(const uint32_t& pixel);
inline boolean isBlackColor(const Color& color);
inline boolean isWhiteColor(const Color& color);

#endif


