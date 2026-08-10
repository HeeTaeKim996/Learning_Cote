#if 0
#include <string>
#include <vector>

using namespace std;

template<typename T>
void CombinationWithRepetition(int start, int n, int k, const vector<T>& arr, vector<T>& curr, vector<vector<T>>& ret)
{
	if (curr.size() == k)
	{
		ret.push_back(curr);
		return;
	}

	for (int i = start; i < n; i++)
	{
		curr.push_back(arr[i]);
		
		CombinationWithRepetition(i, n, k, arr, curr, ret); // ※ 기존 Combination 알고리즘과 거의 같지만, 이 줄에서 단 하나의 차이가 있는데, start 를 i + 1 이 아닌, i 로 하면, CombinationWithRepetition

		curr.pop_back();
	}
}

int main()
{
	printf("999.기타_2_CombinationWithRepetition");
	printf("\n\n\n");

	vector<int> arr = { 1, 2, 3, 4, 5 };
	vector<vector<int>> ret;
	vector<int> curr;
	CombinationWithRepetition(0, 5, 2, arr, curr, ret);
	for (const vector<int>& r : ret)
	{
		for (int i : r) printf("%d ", i);
		printf("\n");
	}


	return 0;
}





#endif