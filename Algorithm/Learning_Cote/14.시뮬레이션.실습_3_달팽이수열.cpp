#if 0
#include <string>
#include <vector>
#include <functional>

using namespace std;

struct Pos
{
	int state = 0;
	int y = 0;
	int x = 0;
};

void solution(int n)
{
	vector<vector<int>> v(n, vector<int>(n, -1));
	Pos pos;
	int index = 1;


	int sRow = 0;
	int eRow = n - 1;
	int sCol = 0;
	int eCol = n - 1;
	int num = 1;
	while (true)
	{
		if (sCol > eCol) break;
		for (int x = sCol; x <= eCol; x++)
		{
			v[sRow][x] = num++;
		}
		sRow++;

		if (sRow > eRow) break;
		for (int y = sRow; y <= eRow; y++)
		{
			v[y][eCol] = num++;
		}
		eCol--;

		if (sCol > eCol) break;
		for (int x = eCol; x >= sCol; x--)
		{
			v[eRow][x] = num++;
		}
		eRow--;

		if (sRow > eRow) break;
		for (int y = eRow; y >= sRow; y--)
		{
			v[y][sCol] = num++;
		}
		sCol++;
	}

	auto PrintMat = [&](vector<vector<int>> vecs)
		{
			for (vector<int>& vec : vecs)
			{
				for (int i : vec) printf("%3d ", i);
				printf("\n");
			}
			printf("\n");
		};

	PrintMat(v);
}

void main()
{
	printf("14.시뮬레이션.실습_3_달팽이수열");
	printf("\n\n\n");

	solution(3);
	solution(4);
	solution(5);
	//solution(10);
}


#endif