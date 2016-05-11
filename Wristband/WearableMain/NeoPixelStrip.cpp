// 
// 
// 

#include "WearablesConstants.h"
#include "NeoPixelStrip.h"
#include "WearablesUtility.h"

inline boolean isBlackColor(const uint32_t& pixel)
{
	return pixel == 0;
}

inline boolean isWhiteColor(const uint32_t& pixel)
{
	return pixel == 0xFFFFFFu;
}

inline boolean isBlackColor(const Color& color)
{
	return color.pixel == 0;
}

inline boolean isWhiteColor(const Color& color)
{
	return color.pixel == 0xFFFFFFu;
}

Color createColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) 
{
	Color c;
	c.pixel = NeoPixel::Color(blue, green, red, white);

	return c;
}

Color createColor(uint8_t red, uint8_t green, uint8_t blue)
{
	return createColor(red, green, blue, 0);
}

Color createColor(uint32_t hexcode) 
{
	Color c;
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

	return createColor(red, green, blue, white);
}

Color createWhite(uint8_t intensity)
{
	uint32_t i = intensity;

	Color c = createColor((i << 24) | (i << 16) | (i << 8));

#if WiC_DEBUG
	uint8_t compos[4];
	dissectColor(c, compos);
	WiCLog::debug("i << 24: 0x%08X, i << 16: 0x%08X, i << 8: 0x%08X, i: 0x%08X", i << 24, i << 16, i << 8, i);
	WiCLog::debug("R: %03u, G: %03u, B: %03u, W: %03u -- Hex: 0x%02X%02X%02X%02X, Val: %14lu", compos[0], compos[1], compos[2], compos[3], compos[0], compos[1], compos[2], compos[3], c.pixel);
	return c;
#else
	return c;
#endif
}

Color createColor() {
	Color c;
	c.pixel = NeoPixel::Color(0, 0, 0, 0);
	return c;
}

void dissectColor(Color& c, uint8_t comps[4])
{
	comps[0] = c.components.red;
	comps[1] = c.components.green;
	comps[2] = c.components.blue;
	comps[3] = c.components.white;
}