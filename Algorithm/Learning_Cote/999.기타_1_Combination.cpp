#if 0

#include <string>
#include <vector>

using namespace std;


template<typename T>
void Combination(const vector<T>& arr, int k, int start, vector<T>& curr, vector<vector<T>>& ret)
{
	if (curr.size() == k)
	{
		ret.push_back(curr);
		return;
	}

	for (int i = start; i < arr.size(); i++)
	{
		curr.push_back(arr[i]);
		Combination(arr, k, i + 1, curr, ret);
		curr.pop_back();
	}
}


void main()
{
	printf("999.기타_1_Combination");
	printf("\n\n\n");


	vector<int> v = { 1, 2, 3, 4, 5 };
	vector<int> curr;
	vector<vector<int>> ret;
	Combination(v, 2, 0, curr, ret);
	for (vector<int>& re : ret)
	{
		for (int i : re)
		{
			printf("%d ", i);
		}
		printf("\n");
	}
}







#endif