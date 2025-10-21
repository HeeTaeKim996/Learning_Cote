#if 0

#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

#include <unordered_set>
#include <unordered_map>

using namespace std;


void main()
{
	printf("04.필수문법_3_벡터_셋_맵   \n\n\n");


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

		printf("\n\n\n");
	}


	{ // Set

		{ // 선언 및 초기화

			set<int> s1;
			set<int> s2 = { 3, 1, 3, 2, 5 };
			set<int> s3(s2);
		}

		{ // 원소 탐색

			set<int> numbers = { 1,2,3,4,5 };
			int targets[] = { 3, 7 };

			for (int target : targets)
			{
				auto it = numbers.find(target);

				if (it != numbers.end())
				{
					printf("원소 %d 를 찾았습니다. 값 : %d\n", target, *it);
				}
				else
				{
					printf("원소 %d 를 찾지 못했습니다\n", target);
				}
			}
		}

		{ // 원소의 삽입과 삭제

			set<int> s = { 1, 3, 2, 1, 5 };
			s.insert(4);
			s.erase(2); // ※ 값을 직접 삭제 가능

			auto it = s.find(4);
			if (it != s.end())
			{
				s.erase(it); // ※ 이터레이터를 사용해서 삭제도 가능
			}

		}
		printf("\n\n\n");
	}

	{ // Map

		{ // 생성 및 키 접근
			map<string, double> employeeSalaries;

			map<string, double> studentGrades =
			{
				{"John", 3.7},
				{"Emma", 3.9},
				{"Sophia", 4.0}
			};

			float grade1 = studentGrades["John"];
			printf("%f\n", grade1);

			float grade2 = studentGrades["rabbit"];
			printf("%f\n", grade2); // ※ 키가 없는 경우, 0 리턴!

			auto it = studentGrades.find("Sophia");
			if (it != studentGrades.end())
			{
				printf("%f\n", it->second); // 이터레이터로 키에 접근
			}
		}

		{ // 값 변경
			map<string, int> myMap = { {"Apple", 1}, {"Banana", 2}, {"Cherry", 3} };
			myMap["Banana"] = 10;
		}

		{ // 삽입과 삭제

			map<int, string> myMap;

			myMap.insert(make_pair(1, "Apple"));
			myMap.insert({ 2, "Banana" });
			myMap[3] = "Cherry";

			for (const auto& pair : myMap)
			{
				printf("%d : %s\n", pair.first, pair.second.c_str());
			}


			myMap.erase(2); // ※ 키값으로 직접 삭제

			auto it = myMap.find(3);
			if (it != myMap.end())
			{
				myMap.erase(it); // ※ 이터레이터로 삭제
			}

			for (const auto& pair : myMap)
			{
				printf("%d : %s\n", pair.first, pair.second.c_str());
			}
		}
		printf("\n\n\n");
	}



	{ // 이부분은 생략해도 된다. unordered_set, unordered_map 인데, set, map 과 각각 문법은 동일하다. 정렬 기능이 빠졌기 때문에, 삽입 삭제에서 성능이 좋지만, 코테에서는 사용할 필요가 거의 없다 한다.

		{ // unordered_set

			unordered_set<int> unorderedSet;

			unorderedSet.insert(3);
			unorderedSet.insert(1);
			unorderedSet.insert(4);
			unorderedSet.insert(2);

			for (int num : unorderedSet) printf("%d ", num);
			printf("\n");
		}

		{ // unordered_map
			
			unordered_map<string, int> unorderedMap;

			unorderedMap["apple"] = 3;
			unorderedMap["banana"] = 1;
			unorderedMap["cherry"] = 4;
			unorderedMap["data"] = 2;

			for (const auto& pair : unorderedMap)
			{
				printf("%7s : %d\n", pair.first.c_str(), pair.second);
			}
		}

	}
}


#endif