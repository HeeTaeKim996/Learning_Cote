/*
공백으로 구분하기 2
제출 내역
문제 설명
단어가 공백 한 개 이상으로 구분되어 있는 문자열 my_string이 매개변수로 주어질 때, my_string에 나온 단어를 앞에서부터 순서대로 담은 문자열 배열을 return 하는 solution 함수를 작성해 주세요.

제한사항
my_string은 영소문자와 공백으로만 이루어져 있습니다.
1 ≤ my_string의 길이 ≤ 1,000
my_string의 맨 앞과 맨 뒤에도 공백이 있을 수 있습니다.
my_string에는 단어가 하나 이상 존재합니다.
입출력 예
my_string	result
" i    love  you"	["i", "love", "you"]
"    programmers  "	["programmers"]
입출력 예 설명
입출력 예 #1

예제 1번의 my_string은 " i    love  you"로 공백을 기준으로 단어를 나누면 "i", "love", "you" 3개의 단어가 있습니다. 따라서 ["i", "love", "you"]를 return 합니다.
입출력 예 #2

예제 2번의 my_string은 "    programmers  "로 단어는 "programmers" 하나만 있습니다. 따라서 ["programmers"]를 return 합니다.
*/

#if 0


#include <string>
#include <vector>

using namespace std;

#if 0
vector<string> solution(string my_string)
{
	vector<string> answer;

	auto startAuto = my_string.begin();

	for (auto it = my_string.begin(); it < my_string.end(); it++)
	{
		if (*it == ' ')
		{
			if (startAuto < it)
			{
				answer.push_back(string(startAuto, it));
			}
			startAuto = it + 1;
		}
	}

	if (startAuto != my_string.end())
	{
		answer.push_back(string(startAuto, my_string.end()));
	}

	return answer;
}
#else

vector<string> solution(string my_string)
{
	vector<string> answer;

	string st = "";
	for (char ch : my_string)
	{
		if (ch == ' ')
		{
			if (st != "")
			{
				answer.push_back(st);
				st = "";
			}
		}
		else
		{
			st += ch;
		}
	}

	if (st != "")
	{
		answer.push_back(st);
	}

	return answer;
}

// ※ 처음 봐서 그런가 구조가 재밌네

#endif

void main()
{
	string st1 = " i    love  you";
	string st2 = "    programmers  ";

	vector<string> ans1 = solution(st1);
	for (string st : ans1) printf("%s\t", st.c_str());
	printf("\n");
	vector<string> ans2 = solution(st2);
	for (string st : ans2) printf("%s\t", st.c_str());

}




#endif