#if 0
#include <string>
#include <vector>
#include <functional>

using namespace std;

vector<vector<int>> Rotate(vector<vector<int>> v, bool clockwise)
{
	int rowMax = v.size();
	int colMax = v[0].size();

	vector<vector<int>> ret(colMax, vector<int>(rowMax, -1));

	if (clockwise)
	{
		for (int y = 0; y < rowMax; y++)
		{
			for (int x = 0; x < colMax; x++)
			{
				ret[x][colMax - 1 - y] = v[y][x];
			}
		}
	}
	else
	{
		for (int y = 0; y < rowMax; y++)
		{
			for (int x = 0; x < colMax; x++)
			{
				ret[colMax - 1 - x][y] = v[y][x];
			}
		}
	}

	return ret;
}


void main()
{
	printf("14.시뮬레이션.실습_1_행렬회전");
	printf("\n\n\n");

	auto PrintMat = [&](vector<vector<int>> vecs)
		{
			for (vector<int>& vec : vecs)
			{
				for (int i : vec) printf("%2d ", i);
				printf("\n");
			}
			printf("\n");
		};

	vector<vector<int>> v1 =
	{
		{1, 2, 3, 4},
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};
	/*
	  출력값
	  13 9 5 1
	  14 10 6 2
	  15 11 7 3
	  16 12 8 4
	*/
	vector<vector<int>> r1 = Rotate(v1, true);
	PrintMat(r1);

	vector<vector<int>> v2 =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};
	vector<vector<int>> r2 = Rotate(v2, false);
	PrintMat(r2);

	/*
	  출력값
	  4 8 12 16
	  3 7 11 15
	  2 6 10 14
	  1 5 9 13
	*/
}



#endif