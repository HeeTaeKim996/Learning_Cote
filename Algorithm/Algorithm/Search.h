#pragma once

#include "Array.h"
#include <functional>

class Search
{
public:
	static void test();


private:
	template<typename T>
	static int binarySearch(const Array<T>& arrs, function<int(const T& t1, const T& t2)> compare, 
		const T& target);
	
	static int binarySearch(const Array<int>& arrs, 
		const int& target);
	
};


template<typename T>
static inline int Search::binarySearch(const Array<T>& arrs,
	function<int(const T& t1, const T& t2)> compare, const T& target)
{
	int start = 0;
	int end = arrs.size() - 1;

	while (start <= end)
	{
		int mid = (start + end) / 2;
		int comp = compare(target, arrs[mid]);
		if (comp == 0)
		{
			return mid;
		}
		else if (comp < 0)
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}

	return -1;
}
