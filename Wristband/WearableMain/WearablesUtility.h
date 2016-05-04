// WearablesUtility.h

#ifndef _WEARABLESUTILITY_h
#define _WEARABLESUTILITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace WiCMath {
	size_t gcd(size_t a, size_t b);
	int32_t gcd(int32_t a, int32_t b);
}

namespace WiCUtil {
	template<typename T>
	void arrayReverse(T arr[], size_t left, size_t right);

	template<typename T>
	void arrayLeftRotate(T arr[], size_t shift, size_t length);

	template<typename T>
	void arrayRightRotate(T arr[], size_t shift, size_t length);

	template<typename T>
	inline void arrayCopy(const T src[], size_t srcSize, T dst[], size_t dstSize);

	template<typename T>
	inline void arrayCopy(const T src[], size_t srcStart, T dst[], size_t dstStart, size_t count);
}

#include "WearablesUtilityTemplate.h"

#endif

