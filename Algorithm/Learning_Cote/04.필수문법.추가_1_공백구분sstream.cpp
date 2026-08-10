

#if 0

#include <string>
#include <vector>

using namespace std;

#if 0
vector<string> solution(string input)
{
	vector<string> ret;

	string st = "";
	for (int i = 0; i < input.length(); i++)
	{
		char ch = input[i];
		if (ch == ' ')
		{
			if (st != "")
			{
				ret.push_back(st);
				st = "";
			}
		}
		else
		{
			st += ch;
		}
	}

	if (st != "") ret.push_back(st);

	return ret;
}

// 위 방법은 코드도 길고 성능도 떨어진다. 아래 방법을 추천
#else
#include <sstream>

vector<string> solution(string input)
{
	vector<string> ret;
	stringstream ss(input);
	string word;
	while (ss >> word)
	{
		ret.push_back(word);
	}

	return ret;
}



#endif




void main()
{
	printf("04.필수문법.추가_1_공백구분sstream  \n\n\n");


	string st1 = "HEllo World";
	vector<string> ans1 = solution(st1);
	for (string st : ans1) printf("%s\n", st.c_str());

	string st2 = "     A    BB  CCC                 D EE   FFFFF   GG            ";
	vector<string> ans2 = solution(st2);
	for (string st : ans2) printf("%s\n", st.c_str());
}








#endif