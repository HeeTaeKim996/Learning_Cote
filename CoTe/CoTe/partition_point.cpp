

#if 0

#include <string>
#include <vector>
#include <functional>


using namespace std;

template<typename T>
int partition_point(vector<T> arr, ::function<bool(T)> pred)
{
	int start = 0; // 열린구간
	int end = arr.size(); // 닫힌구간

	while (start < end)
	{
		int mid = start + (end - start) / 2;

		if (pred(arr[mid]))
		{
			start = mid + 1;
		}
		else
		{
			end = mid;
		}
	}

	return start; // 쭉 true였다가, 처음으로 false가 되는 인덱스
}

#include <algorithm>

void main()
{
	//vector<int> arr = { 2,4,5, 1,3, 5 };
	vector<int> arr = { 2, 4, 5 };
	::function<bool(int)> TEMP = [](int a) { return a % 2 == 0; };

	printf("%d\n", partition_point(arr, TEMP));
	printf("%d\n", std::partition_point(arr.begin(), arr.end(), TEMP) - arr.begin()); // ※ #include<algorithm> 에 있는 API (이터레이터 사용)
}


#endif