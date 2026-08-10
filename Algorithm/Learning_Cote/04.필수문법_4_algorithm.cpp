

#if 0

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


void main()
{
	printf("04.필수문법_4_algorithm");
	printf("\n\n\n");

	{ // Count

		vector<int> v = { 1, 4, 3, 4, 5, 4, 5 };

		int ret = count(v.begin(), v.end(), 5);		// ※ 해당 요소의 인자 갯수를 카운트 !

		printf("%d\n", ret);
	}

	{ // Sort

		vector<int> v = { 4, 2, 5, 3, 1 };
		
		sort(v.begin(), v.end());
		for (int i = 0; i < v.size(); i++) printf("%d, ", v[i]);
		printf("\n");

		sort(v.rbegin(), v.rend()); // ※ sort 역순도 가능
		for (int i = 0; i < v.size(); i++) printf("%d, ", v[i]);
		printf("\n");
	}


	{ // Sort + Compare

		struct Point
		{
			Point(int InX, int InY) : x(InX), y(InY) {}
			int x, y;
		};
		
		auto Compare = [](const Point& a, const Point& b) // ※ 정렬 기준. 첫번째가 두번째보다 작다면, true. 크거나 같다면, false
			{
				if (a.x == b.x)
				{
					return a.y < b.y;
				}
				return a.x < b.x;
			};

		vector<Point> points = { {3, 4}, {1, 2}, {3, 1}, {2, 5} };

		sort(points.begin(), points.end(), Compare); // ※ 사용자 정의 함수를 기준으로 정렬 !!

		for (const Point& p : points) printf("%d, %d \n", p.x, p.y);
		printf("\n");
	}

	{ // next_permutation

		vector<int> v = { 1, 2, 3 };
		do
		{
			for (int i : v) printf("%d, ", i);
			printf("\n");
		} while (next_permutation(v.begin(), v.end())); // ※ 사전순으로 정렬된 데이터를 대상으로, 가능한 모든 순열을 생성

		printf("\n");

		vector<int> v2 = { 3, 2, 1 };
		do
		{
			for (int i : v2) printf("%d, ", i);
			printf("\n");
		} while (next_permutation(v.begin(), v.end())); // ※ 사전순으로 정렬되지 않은 데이터기 때문에, 순열이 제대로 생성되지 않음
		
		printf("\n");
	}


	{ // min, max		->		 실수 a, b, c.. 가 주어졌을 때 { a, b, c .. } 형태로 입력하여 min, max 를 구함

		printf("Min : %d \n", std::min({ 1, 3, 5}));
		printf("Max : %d \n", std::max({ 1, 3, 5 }));
	}


	{ // max_element, min_element		->		벡터로 실수들이 주어졌을 때, 벡터를 통째로 넣어 비교할 때 사용

		vector<int> v = { 1, 3, 5, 7, 2, 4, 6 };

		auto maxIt = max_element(v.begin(), v.end());
		auto minIt = min_element(v.begin(), v.end());

		printf("%d, %d \n", *minIt, *maxIt);
	}

	{ // swap
		vector<int> v = { 1, 2, 3, 4 };
		std::swap(v[1], v[3]);
		printf("swap : ");
		for (int i : v) printf("%d ", i);
		printf("\n");
	}


	{ // unique

		vector<int> v = { 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5 };
		
		auto newEnd = unique(v.begin(), v.end());		// ※ unique 사용시, 중복되지 않은 요소들을 앞의 요소에 스왑하여 (중복되는 원소는 뒤러 밀어냄) 배치함
		for (auto it = v.begin(); it != newEnd; it++)
		{
			printf("%d, ", *it);						// ※ 벡터 사이즈는 동일하지만, newEnd까지는 중복되지 않은 요소들만 배치됨
		}
		printf("\n\n");

		for (auto it = v.begin(); it != v.end(); it++)	// ※ 전체를 출력해보면, 이해할 수 있음. 스왑이 일어남
		{
			printf("%d, ", *it);
		}
		printf("\n\n");
	}

	{ // binary_search

		vector<int> v = { 1, 2, 3, 4, 5 };

		printf("%d\n", binary_search(v.begin(), v.end(), 3));
		printf("%d\n", binary_search(v.begin(), v.end(), 7));
	}



}


#endif