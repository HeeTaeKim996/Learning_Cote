#if 0
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2)
{
	int row = arr1.size();
	int col = arr2[0].size();
	int common = arr1[0].size();

	vector<vector<int>> ret(row, vector<int>(col));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int sum = 0;
			for (int k = 0; k < common; k++)
			{
				sum += arr1[i][k] * arr2[k][j];
			}

			ret[i][j] = sum;
		}
	}

	return ret;
}

void main()
{
	printf("05.배열.실습_5_행렬의_곱셈");
	printf("\n\n\n");

	vector<vector<int>> arr1 =
	{
		{2, 3, 2},
		{4, 2, 4},
		{3, 1, 4}
	};
	vector<vector<int>> arr2 =
	{
		{5, 4, 3},
		{2, 4, 1},
		{3, 1, 1}
	};

	vector<vector<int>> ans = solution(arr1, arr2);
	for (int i = 0; i < ans.size(); i++)
	{
		for (int j = 0; j < ans[0].size(); j++)
		{
			printf("%d, ", ans[i][j]);
		}
		printf("\n");
	}
}

#endif