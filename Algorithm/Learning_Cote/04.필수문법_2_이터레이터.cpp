#if 0

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


void main()
{
	printf("04.필수문법_2_이터레이터  \n\n");


	// 순방향
	{
		vector<int> vec = { 10, 20, 30, 40, 50 };

		// 순회하고 출력
		for (auto it = vec.begin(); it < vec.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;


		// 탐색
		auto result = find(vec.begin(), vec.end(), 31);			// ※ vec 은 #include<algorithm> 으로 사용

		if (result != vec.end())
		{
			printf("Found : %d", *result);
		}
		else
		{
			cout << "NO FOUND" << endl;
		}


		map<string, int> myMap = { {"Apple", 1}, {"banana", 2}, {"cherry", 3} };
		auto ret = myMap.find("banana"); // map 은 algorithm 이 아닌, 클래스 내 매서드로 사용

		if (ret != myMap.end())
		{
			printf("Found : %s", ret->first.c_str() );
		}
		else
		{
			cout << "NO FOUND" << endl;
		}
	
		cout << endl << endl << endl;
	}


	// 역방향
	{
		vector<int> vec = { 10, 30, 30, 40, 50 };
		
		for (auto it = vec.rbegin(); it < vec.rend(); it++) // ※ 역방향은 이처럼 rbegin, rend 를 쓴다. 하지만 역방향이라 해도, it < vec.rend(); it++ 처럼 문법은 순방향과 동일하다
		{
			printf("%d  ", static_cast<int>((*it)));
		}
		printf("\n");


		auto ret = find(vec.rbegin(), vec.rend(), 30);	// find 도 마찬가지로 rbegin, rend 사용 가능
		printf("%d,  %d", *ret, ret - vec.rbegin());

	}

}

#endif