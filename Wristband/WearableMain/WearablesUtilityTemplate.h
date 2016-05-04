#pragma once

namespace WiCUtil {
	template<typename T>
	void arrayReverse(T arr[], size_t left, size_t right)
	{
		while (left < right)
		{
			T temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			left++;
			right--;
		}
	}

	template<typename T>
	void arrayRightRotate(T arr[], size_t shift, size_t length)
	{
		arrayReverse(arr, 0, length - 1);
		arrayReverse(arr, 0, shift - 1);
		arrayReverse(arr, shift, length - 1);
	}

	template<typename T>
	void arrayLeftRotate(T arr[], size_t shift, size_t length)
	{
		arrayReverse(arr, shift, length - 1);
		arrayReverse(arr, 0, shift - 1);
		arrayReverse(arr, 0, length - 1);
	}

	template<typename T>
	inline void arrayCopy(const T src[], size_t srcSize, T dst[], size_t dstSize)
	{
		memcpy(dst, src, min(srcSize, dstSize) * sizeof(T));
	}

	template<typename T>
	inline void arrayCopy(const T src[], size_t srcStart, T dst[], size_t dstStart, size_t count)
	{
		memcpy(dst + srcStart, src + dstStart, count * sizeof(T));
	}
}