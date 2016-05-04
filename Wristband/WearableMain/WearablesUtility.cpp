// 
// 
// 

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