#include "pch.h"
#include "Search.h"


#include <vector>

void Search::test()
{
	int arrs[] = {0, 1, 2, 3, 4, 5};


	auto compare = [](const int& a, const int& b) -> int
		{
			if (a == b)		return 0;
			else if (a < b) return -1;
			else			return 1;
		};





	for (int i = -1; i <= 6; i++)
	{
		int index = binarySearch<int>(Array<int>(arrs), compare, i);
		printf("%d, ", index);
	}
	printf("\n");



	for (int i = -1; i <= 6; i++)
	{
		int index = binarySearch(Array<int>(arrs), i);
		printf("%d, ", index);
	}

}

int Search::binarySearch(const Array<int>& arrs, const int& target)
{
	static auto compare = [](const int& a, const int& b) -> int
		{
			if (a == b)		return 0;
			else if (a < b) return -1;
			else			return 1;
		};
	return binarySearch<int>(arrs, compare, target);
}
