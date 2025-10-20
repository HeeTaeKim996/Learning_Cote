
#if 0
#include <string>
#include <vector>
#include <functional>

using namespace std;

template<typename T>
int BinarySearch(vector<T> arr, T searched, std::function<int(T, T)> pred)
{
	int start = 0;
	int end = arr.size(); // 검색은 항상 닫힌구간을 전제로 하자 ( 보통 api가 이터레이터의 end를 인자로 받으니

	while (start < end)
	{
		int mid = start + (end - start) / 2;

		int ret = pred(arr[mid], searched);

		if (ret == 0)		return mid;
		else if (ret > 0)	start = mid + 1;
		else				end = mid;
	}

	return -1;
}

#include <algorithm>

void main()
{
	vector<int> arr = { 1,2,3,4,5 };

	::function<int(int, int)> temp = [](int a, int b)
		{
			if (a < b) return 1;
			else if (a > b) return -1;
			return 0;
		};

	printf("%d\n", BinarySearch(arr, 0, temp));
	printf("%d\n", ::binary_search(arr.begin(), arr.end(), 3)); // 같은 이름으로 있긴 한데, 있는지 여부를 true/false 반환만 한다
	

	// 검색 알고리즘은 binary_search는 있는지 여부만 알려준다. upper_bound, lower_bound 는 연속형에도 사용가능하기에, 위 함수의 역할을 대신할 수는 있지만, 굳이 여기까지 외워야하나 싶다. 위 함수는 직접 구현하는 게 낫지 않을까 싶음
}
#endif