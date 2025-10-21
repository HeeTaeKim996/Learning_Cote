
#if 1

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void DebugFunc(vector<int> arr)
{
	for (int i : arr) printf("%d, ", i);
	printf("\n");
}

vector<int> sort(vector<int> arr) // 정렬
{
	sort(arr.begin(), arr.end());
	return arr;
}

vector<int> unique(vector<int> arr) // unique 요소만 남기기
{
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	return arr;
}


void main()
{
	printf("05.배열_배열_기본_다루기");
	printf("\n\n\n");

	vector<int> v = { 1, 2, 2, 5, 3, 3, 3};
	
	DebugFunc(sort(v));

	DebugFunc(unique(v));
}


#endif