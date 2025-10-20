/*
문자열 바꿔서 찾기
제출 내역
문제 설명
문자 "A"와 "B"로 이루어진 문자열 myString과 pat가 주어집니다. myString의 "A"를 "B"로, "B"를 "A"로 바꾼 문자열의 연속하는 부분 문자열 중 pat이 있으면 1을 아니면 0을 return 하는 solution 함수를 완성하세요.

제한사항
1 ≤ myString의 길이 ≤ 100
1 ≤ pat의 길이 ≤ 10
myString과 pat는 문자 "A"와 "B"로만 이루어진 문자열입니다.
입출력 예
myString	pat	result
"ABBAA"	"AABB"	1
"ABAB"	"ABAB"	0
입출력 예 설명
입출력 예 #1

"ABBAA"에서 "A"와 "B"를 서로 바꾸면 "BAABB"입니다. 여기에는 부분문자열 "AABB"가 있기 때문에 1을 return 합니다.
입출력 예 #2

"ABAB"에서 "A"와 "B"를 서로 바꾸면 "BABA"입니다. 여기에는 부분문자열 "BABA"가 없기 때문에 0을 return 합니다.
※ 2023년 05월 15일 제한사항 및 테스트 케이스가 수정되었습니다. 기존에 제출한 코드가 통과하지 못할 수 있습니다.
*/

#if 0

#include <string>
#include <vector>

using namespace std;

#if 0
int solution(string myString, string pat)
{
	int size = myString.size();
	int patSize = pat.size();
	int diff = size - patSize;

	if (diff < 0) return 0;

	for (int i = 0; i < size; i++)
	{
		if (myString[i] == 'A') myString[i] = 'B';
		else myString[i] = 'A';
	}

	for (int i = 0; i < size; i++)
	{
		if (myString.substr(i, patSize) == pat) return 1;
	}
	return 0;
}
//※ 역시나 string 에 너무 약하다
#else
int solution(string myString, string pat)
{
	for (int i = 0; i < myString.size(); i++)
	{
		if (myString[i] == 'A') myString[i] = 'B';
		else myString[i] = 'A';
	}

	return myString.find(pat) != string::npos;
}

#endif


void main()
{
	string st1 = "ABAB";
	string pat1 = "BABA";

	string st2 = "AABBB";
	string pat2 = "BBB";

	printf("%d, %d", solution(st1, pat1), solution(st2, pat2));
}



#endif