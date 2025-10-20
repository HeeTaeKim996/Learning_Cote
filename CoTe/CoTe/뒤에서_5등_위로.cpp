/*
뒤에서 5등 위로
제출 내역
문제 설명
정수로 이루어진 리스트 num_list가 주어집니다. num_list에서 가장 작은 5개의 수를 제외한 수들을 오름차순으로 담은 리스트를 return하도록 solution 함수를 완성해주세요.

제한사항
6 ≤ num_list의 길이 ≤ 30
1 ≤ num_list의 원소 ≤ 100
입출력 예
num_list	result
[12, 4, 15, 46, 38, 1, 14, 56, 32, 10]	[15, 32, 38, 46, 56]
입출력 예 설명
입출력 예 #1

[12, 4, 15, 46, 38, 1, 14, 56, 32, 10]를 정렬하면 [1, 4, 10, 12, 14, 15, 32, 38, 46, 56]이 되고, 앞에서 부터 6번째 이후의 수들을 고르면 [15, 32, 38, 46, 56]가 됩니다.
*/

#if 0

#include <string>
#include <vector>

using namespace std;

#if 0
vector<int> solution(vector<int> num_list)
{
	for (int i = 0; i < num_list.size(); i++)
	{
		int min = num_list[i];
		int index = i;

		for (int j = i + 1; j < num_list.size(); j++)
		{
			if (min > num_list[j])
			{
				min = num_list[j];
				index = j;
			}
		}

		if (index != i)
		{
			int temp = num_list[i];
			num_list[i] = num_list[index];
			num_list[index] = temp;
		}
	}


	return vector<int>(num_list.begin() + 5, num_list.end());
}
#else

#include <algorithm>

vector<int> solution(vector<int> num_list)
{
	sort(num_list.begin(), num_list.end());

	return vector<int>(num_list.begin() + 5, num_list.end());
}


// ※ #include <algorithm> 이건 외워두자

#endif


void main()
{
	vector<int> ints = { 1,4,2,3,4,5,6,1,8,7 };

	vector<int> ret = solution(ints);
	for (int i : ret)
	{
		printf("%d  ", i);
	}
}


#endif