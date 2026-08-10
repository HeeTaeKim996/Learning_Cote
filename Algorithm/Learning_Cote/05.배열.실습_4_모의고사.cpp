#if 0
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int>answers)
{
	vector<vector<int>> vecs =
	{
		{ 1, 2, 3, 4, 5},
		{2, 1, 2, 3, 2, 4, 2, 5},
		{3, 3, 1, 1, 2, 2, 4, 4, 5, 5}
	};


	vector<int> ret;
	int max = 0;
	for (int i = 0; i < vecs.size(); i++)
	{
		int score = 0;
		for (int j = 0; j < answers.size(); j++)
		{
			int index = j % vecs[i].size();
			if (vecs[i][index] == answers[j]) score++;
		}

		if (score > max)
		{
			ret.clear();
			ret.push_back(i + 1);
			max = score;
		}
		else if (score == max)
		{
			ret.push_back(i + 1);
		}
	}

	return ret;
}

void main()
{
	printf("05.배열.실습_4_모의고사");
	printf("\n\n\n");


	//vector<int> v = { 1, 2, 3, 4, 5 };
	vector<int> v = { 1, 3, 2, 4, 2 };

	vector<int> ans = solution(v);
	for (int i : ans) printf("%d, ", i);
	printf("\n");
}



#endif