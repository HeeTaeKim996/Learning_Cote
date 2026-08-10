#if 0

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


vector<int> solution(vector<int> numbers)
{
	numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end() );

	set<int> sum;
	
	for (int i = 0; i < numbers.size(); i++)
	{
		for (int j = i + 1; j < numbers.size(); j++)
		{
			sum.insert(numbers[i] + numbers[j]);
		}
	}

	return vector<int>(sum.begin(), sum.end());
}

void main()
{
	printf("05.배열.실습_3_두_수를_뽑아서_더하기");
	printf("\n\n\n");


	vector<int> v = { 2, 1, 3, 4, 1 };
	vector<int> ans = solution(v);
	for (int i : ans) printf("%d, ", i);
	printf("\n");
}

#endif