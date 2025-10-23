
#if 0

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void DebugFunc(vector<int> arr)
{
	for (int i : arr) printf("%d, ", i);
	printf("\n\n");
}





vector<int> sort(vector<int> arr) // ※ 정렬
{
	sort(arr.begin(), arr.end());
	return arr;
}





vector<int> unique(vector<int> arr) // ※ unique 요소만 남기기
{
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	return arr;
}



struct Temp
{
	int stage;
	float per;
};
vector<int> sort_compare(vector<Temp> arr) // ※ 사용자 정의 구조체를 sort 에 사용하고 싶을 때 사용 !!
{
	auto Compare = [](const Temp& t1, const Temp& t2)
		{
			if (t1.per == t2.per)
			{
				return t1.stage < t2.stage;
			}
			return t1.per > t2.per;
		};

	sort(arr.begin(), arr.end(), Compare);

	vector<int> ret(arr.size());
	for (int i = 0; i < arr.size(); i++)
	{
		ret[i] = arr[i].stage;
	}

	return ret;
}




void main()
{
	printf("05.배열_배열알고리즘_기본_다루기");
	printf("\n\n\n");

	vector<int> v = { 1, 2, 2, 5, 3, 3, 3};
	
	DebugFunc(sort(v));

	DebugFunc(unique(v));


	vector<Temp> temps = { {1, 0.1}, {2, 0}, {3, 0.8}, {4, 0}, {5, 0.7} };
	DebugFunc(sort_compare(temps));
}


#endif