// WearablesUtility.h

#ifndef _WEARABLESUTILITY_h
#define _WEARABLESUTILITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "WearablesConstants.h"

#define LOG_FMT_MAX_SIZE 256
#define LOG_OUT(logstr) Serial.println(logstr);

#ifdef WiC_DEBUG
#define WiC_MUTE_LOG false
#else
#define WiC_MUTE_LOG false
#endif

namespace WiCMath {
	size_t gcd(size_t a, size_t b);
	int32_t gcd(int32_t a, int32_t b); 
}

namespace WiCLog {
	enum LogLevel { LOG_VERBOSE = 0, LOG_DEBUG = 1, LOG_INFO = 2, LOG_WARN = 3, LOG_ERROR = 4};

	void log(LogLevel level, const char *fmt, ...);
	void debug(const char *fmt, ...);
	void info(const char *fmt, ...);
	void warn(const char *fmt, ...);
	void error(const char *fmt, ...);

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

