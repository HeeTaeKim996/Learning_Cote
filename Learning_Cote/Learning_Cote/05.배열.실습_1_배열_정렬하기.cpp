
#if 0
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr)
{
	sort(arr.begin(), arr.end());
	return arr;
}


void main()
{
	printf("05.배열.실습_1_배열정렬하기");
	printf("\n\n\n");

	vector<int> v = { 1, -5, 2, 4, 3 };
	vector<int> ans = solution(v);
	for (int i : ans) printf("%d, ", i);
	printf("\n");

}





#endif
