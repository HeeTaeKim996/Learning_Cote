
// https://www.acmicpc.net/problem/1764

#if 1


#include <string>
#include <vector>
#include <set>

using namespace std;

void solution(vector<string> input)
{
	// Member : stSet
	set<string> stSet;

	// Play : First Line
	string st0 = input[0];
	size_t blankPos = st0.find(" ");
	int n = stoi( st0.substr(0, blankPos));
	int m = stoi(st0.substr(blankPos + 1, st0.length() - blankPos));

	
	// Play
	vector<string> detbo;
	for (int i = 1; i < 1 + n; i++)
	{
		stSet.insert(input[i]);
	}
	for (int i = n + 1; i < input.size(); i++)
	{
		auto it = stSet.find(input[i]);
		if (it != stSet.end())
		{
			detbo.push_back(input[i]);
		}
	}

	printf("Count : %d\n", detbo.size());
	for (string st : detbo) printf("%s,\t", st.c_str());

}



int main()
{
	printf("https://www.acmicpc.net/  __  백준 - 1764 듣보잡		\n\n\n");

	vector<string> ex1 =
	{
		"3 4",
		"ohhenrie",
		"charlie",
		"baesangwook",
		"obama",
		"baesangwook",
		"ohhenrie",
		"clinton"
	};

	solution(ex1);
}




#endif