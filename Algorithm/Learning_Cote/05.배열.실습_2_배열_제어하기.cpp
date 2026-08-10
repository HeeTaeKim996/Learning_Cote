#if 0
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

vector<int> solution(vector<int> lst)
{
	sort(lst.rbegin(), lst.rend());

	lst.erase(unique(lst.begin(), lst.end()), lst.end());

	return lst;
}


void main()
{
	printf("05.배열.실습_2_배열_제어하기");
	printf("\n\n\n");

	vector<int> v = { 4, 2, 2, 1, 3, 4 };
	vector<int> ans = solution(v);
	for (int i = 0; i < ans.size(); i++) printf("%d, ", ans[i]);
}
#endif