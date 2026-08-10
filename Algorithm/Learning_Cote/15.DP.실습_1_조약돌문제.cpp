#if 0
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> v)
{
	int n = v[0].size();
	vector<vector<int>> dp(4, vector<int>(n));

	dp[0][0] = v[0][0];
	dp[1][0] = v[1][0];
	dp[2][0] = v[2][0];
	dp[3][0] = v[0][0] + v[2][0];

	for (int i = 1; i < n; i++)
	{
		dp[0][i] = v[0][i] + std::max( { dp[1][i - 1], dp[2][i - 1] } );
		dp[1][i] = v[1][i] + std::max( { dp[0][i - 1], dp[2][i - 1], dp[3][i - 1] } );
		dp[2][i] = v[2][i] + std::max({ dp[0][i - 1], dp[1][i - 1] });
		dp[3][i] = v[0][i] + v[2][i] + dp[1][i - 1];
	}

	int z = dp[0][n - 1];
	int f = dp[1][n - 1];
	int s = dp[2][n - 1];
	int t = dp[3][n - 1];
	return std::max({ z, f, s, t });
}



void main()
{
	printf("15.DP.실습_1_조약돌문제");
	printf("\n\n\n");

	vector<vector<int>> v1 = { {1, 3, 3, 2}, {2, 1, 4, 1}, {1, 5, 2, 3} };
	vector<vector<int>> v2 = { {1, 7, 13, 2, 6}, {2, -4, 2, 5, 4}, {5, 3, 5, -3, 1} };

	printf("%d\n", solution(v1));
	printf("%d\n", solution(v2));
}
#endif