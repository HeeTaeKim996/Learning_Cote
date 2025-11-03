#if 0
#include <string>
#include <vector>
#include <functional>


using namespace std;



void Dfs(vector<int> arr, vector<vector<int>>& ret, int start, int n)
{
	int sum = 0;
	for (int i : arr)
	{
		sum += i;
	}

	if (sum > 10) return;

	if (sum == 10)
	{
		ret.push_back(arr); 
		return;
	}

	for (int i = start; i <= n; i++)
	{
		arr.push_back(i);
		Dfs(arr, ret, i + 1, n);
		arr.pop_back();
	}
	
}


void solution(int n)
{
	vector<vector<int>> ret;
	vector<int> arr;
	Dfs(arr, ret, 1, n);

	for (const vector<int>& vec : ret)
	{
		for (int i : vec)
		{
			printf("%2d ", i);
		}
		printf("\n");
	}

}

void main()
{
	printf("12.백트래킹.실습_1_몸풀기문제");
	printf("\n\n\n");

	solution(7);

}

















#endif