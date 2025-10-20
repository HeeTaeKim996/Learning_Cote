#if 1
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void main()
{
	printf("04.필수문법_3_   \n\n\n");


	{ // 벡터

		{ // 1차 벡터 초기화
			vector<int> v;
			vector<int> v2 = { 1, 2, 3, 5, 6 };
			vector<int> v3(4, 3);	// ※ 크기 4로, 요소를 모두 3으로 초기화
			vector<int> v4(v3);
		}


		{ // 2차 벡터 초기화
			vector<vector<int>> v1;

			int rows = 3;
			int cols = 4;
			vector<vector<int>> v2(rows, vector<int>(cols)); // !! 초기화 수월

			int val = 9;
			vector<vector<int>> v3(rows, vector<int>(cols, val)); // !! 모든 요소를 val 로 초기화

			vector<vector<int>> v4 =
			{
				{1, 2, 3},
				{4, 5, 6},
				{7, 8, 9}
			};

		}

		{ // 원소 변경
			vector<int> vec = { 1, 2, 3, 4, 5 };

			vec[2] = 10;
		}

		{ // 삽입과 삭제

			vector<int> v = { 2, 3, 4, 5 };

			v.push_back(6);
			v.pop_back();
			
			v.insert(v.begin(), 1);
			v.erase(v.begin());

			auto it = find(v.begin(), v.end(), 3);
			if (it != v.end())
			{
				v.insert(it, 30); // 이렇게 특정 이터레이터 '엎에' 끼워넣기 가능
			}
			for (int i = 0; i < v.size(); i++) printf("%d  ", v[i]);
		}
	}
}


#endif