// 
// 
// 

#include "NeoPixelStrip.h"

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

