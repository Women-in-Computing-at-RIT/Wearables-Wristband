// 
// 
// 

#include <stdarg.h>>
#include "WearablesConstants.h"
#include "WearablesUtility.h"

template<typename T>
static T internal_gcd(T A, T B)
{
	T a = max(A, B), b = min(A, B);

	T r;

	while (b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

namespace WiCMath {
	size_t gcd(size_t a, size_t b)
	{
		return internal_gcd(a, b);
	}

	uint32_t gcd(uint32_t a, uint32_t b)
	{
		return internal_gcd(a, b);
	}
}

static const char *LEVEL_NAMES[] = {
	"VERBOSE",
	"DBUG",
	"INFO",
	"WARN",
	"ERRO"
};

static char buffer[LOG_FMT_MAX_SIZE];

static inline void internal_log(const char *level, const char *fmt, va_list& fmtArgs)
{
	char tmp[LOG_FMT_MAX_SIZE];

	vsnprintf(tmp, LOG_FMT_MAX_SIZE-1, fmt, fmtArgs);
	snprintf(buffer, LOG_FMT_MAX_SIZE - 1, "[%s]: %s", level, tmp);

	LOG_OUT(buffer);
}

static inline void internal_log(WiCLog::LogLevel level, const char *fmt, va_list& args)
{
	if (!WiC_MUTE_LOG)
		internal_log(LEVEL_NAMES[level], fmt, args);
}

namespace WiCLog{

	void log(LogLevel level, const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		internal_log(level, fmt, args);
		va_end(args);
	}

	void debug(const char *fmt, ...) {
#if WiC_DEBUG
		va_list args;
		va_start(args, fmt);
		internal_log(LOG_DEBUG, fmt, args);
		va_end(args);
#endif
	}
	void info(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		internal_log(LOG_INFO, fmt, args);
		va_end(args);
	}

	void warn(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		internal_log(LOG_WARN, fmt, args);
		va_end(args);
	}

	void error(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		internal_log(LOG_ERROR, fmt, args);
		va_end(args);
	}

}