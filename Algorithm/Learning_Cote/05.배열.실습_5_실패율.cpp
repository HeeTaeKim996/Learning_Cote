#if 0
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> stages)
{
	struct Temp
	{
		int stage;
		float per;
	};

	::function<bool(const Temp&, const Temp&)> Compare = [](const Temp& t1, const Temp& t2)
		{
			if (t1.per == t2.per)
			{
				return t1.stage < t2.stage;
			}
			return t1.per > t2.per;
		};


	vector<int> cleared(N, 0);
	vector<int> playing(N, 0);
	Temp temp;
	temp.per = 0.f;
	vector<Temp> result(N, temp);

	for (int i : stages)
	{
		for (int j = 0; j < i - 2; j++)
		{
			cleared[j]++;
		}
		if (i < N + 1)
		{
			playing[i - 1]++;
		}
	}
	for (int i = 0; i < N; i++)
	{
		result[i].per = static_cast<float>(playing[i]) / cleared[i];
		result[i].stage = i + 1;
	}

	sort(result.begin(), result.end(), Compare);

	vector<int> ret;
	for (int i = 0; i < result.size(); i++)
	{
		ret.push_back(result[i].stage);
	}
	return ret;
}

void main()
{
	vector<int> v = { 2, 1, 2, 6, 2, 4, 3, 3 };
	vector<int> ret = solution(5, v);

	for (int i = 0; i < ret.size(); i++) printf("%d, ", ret[i]);
}





#endif