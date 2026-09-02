#include "pch.h"
#include "3.1.StringMatch.h"
#include <functional>
#include "Array.h"

void StringMatch::test()
{
#ifndef FLAG_USE_WSTRING
	STRING txt = "Hello Harry, Hi Bori";
	STRING searchs[4] = {
		"Harry", "Hari", "Bori", "Borry"
		// 6,	  -1,	  16,	  -1
	};
#else
	STRING txt = L"Hello Harry, Hi Bori";
	STRING searchs[4] = {
		L"Harry", L"Hari", L"Bori", L"Borry"
		// 6,	  -1,	  16,	  -1
	};

#endif

	auto testMatch = [&](function<int(const STRING&, const STRING&)> matchFunc)-> void
		{
			for (STRING srch : searchs)
			{
				int index = matchFunc(txt, srch);
				printf("%d, ", index);
			}
			printf("\n");
		};


	if (1)
	{
		testMatch(StringMatch::BruoteForce);
	}

	if (1)
	{
		testMatch(StringMatch::KMP);
	}
	if (0)
	{
#ifndef FLAG_USE_WSTRING
		STRING txt = "AABAAABC";
#else
		STRING txt = L"AABAAABC";
#endif

		// KMP 로프 예문
#ifndef FLAG_USE_WSTRING
		printf("%d \n", KMP(txt, "AABAAABC"));
		printf("%d \n", KMP(txt, "ABABABABC"));
#else
		printf("%d \n", KMP(txt, L"AABAAABC"));
		printf("%d \n", KMP(txt, L"ABABABABC"));
#endif
	}

	if (1)
	{
		testMatch(StringMatch::BoyerMoor);
	}
	

}























int StringMatch::BruoteForce(const STRING& txt, const STRING& search)
{
	const int txtEnd = txt.size();
	const int searchEnd = search.size();

	int tp = 0;
	int sp = 0;

	while (tp < txtEnd && sp < searchEnd)
	{
		if (txt[tp] == search[sp])
		{
			tp++;
			sp++;
		}
		else
		{
			tp = tp - sp + 1;
			sp = 0;
		}
	}

	if (sp == searchEnd)
	{
		return tp - sp;
	}
	return -1;
}
















/*
	■ KMP
	BruteForce 는 검색 도중 실패시 tp - sp + 1 로 돌아가여, 매칭이 시작했던 곳 바로 다음으로 이동하여 같은 작업을 반복한다.
	KMP 는 이를 보완하기 위해, search 텍스트를 대상으로 로프 를 만들었다.
	
	클라이밍으로 비유하기 적합한데, 
	BruteForce 는 피벗에서 떨어지면 바닥으로 추락하는 반면,
	KMP 는 기존에 로프로 걸어뒀던 피벗까지만 떨어지는 원리다.
*/

int StringMatch::KMP(const STRING& txt, const STRING& search)
{
	const int txtEnd = txt.size();
	const int searchEnd = search.size();

	int tp = 1;
	int sp = 0;

	Array<int>rope(searchEnd + 1);
	rope[1] = 0;

	while (tp < searchEnd)
	{
		if (search[tp] == search[sp])
		{
			rope[++tp] = ++sp;
		}
		else if (sp == 0)
		{
			rope[++tp] = 0;
		}
		else
		{
			sp = rope[sp];
		}
	}

#if 0
	printf("로프(디버그) : ");
	for (int i = 0; i < rope.size(); i++)
	{
		printf("%d, ", rope[i]);
	}
	printf("\n");
#endif

	tp = 0;
	sp = 0;

	while (tp < txtEnd && sp < searchEnd)
	{
		if (txt[tp] == search[sp])
		{
			tp++;
			sp++;
		}
		else if (sp == 0)
		{
			tp++;
		}
		else
		{
			sp = rope[sp];
		}
	}


	if (sp == searchEnd)
	{
		return tp - sp;
	}
	return -1;
}



















/*
	■ BoyerMoor
	문자의 끝에서부터 시작으로, 왼쪽 방향으로, 일치 여부를 검사.
	검수중 불일치시, 불일치하는 문자를 기준으로 미리 만들어둔 표에 대입하여, 
	최소의 우측 이동량을 결정

	□ 표 만들기
	ABAC 를 검색한다 하자. 그러면 미리 만드는 표는 
	A -> 1. B-> 2. 이며, 그외 문자열 -> 4

	여기서 C는 마지막 문자이므로 표를 갱신하지 않는다. (추후 나오지만 만들어봤자 의미가 없다)
	여기서 A는 뒤 기준 -1 에 위치하기에 1이다. (앞에 있는 A가 아닌, 가장 마지막에 나오는 A를 기준으로 표가 만들어진다)
	여기서 B는 뒤 기준 -2 에 위치하기에 2이다.
	그 외 문자열은 ABAC 의 길이인 4 이다.


	□ 예시
	텍스트 문자열이
	A B C X D E Z C A B A C A B A C 라고 하자.

	1)
	A B C X D E Z C A B A C A B A C
	A B A C
	-> A B A C 의 끝인 C 부터 검사. C != X 이므로, 실패.
	-> X 는 표에 정의되지 않았기에( 엄밀히는 4 로 정의됐기에 ). 4만큼 이동
	   ( 어차피 1, 2, 3 칸을 이동해도, X 는 A, B, A 와 매핑되지 않기에, SKIP 하고 4만큼 이동 )

	2) 
	A B C X D E Z C A B A C A B A C
	        A B A C
	-> 마지막 C == C 는 통과. 하지만 Z != A 이므로 통과 못함 ( 여기서 한번 통과했으므로, 검수 기준점은 Z 에 위치해 있는 상태이다 )
	-> Z 는 표에 정의돼있지 않으므로, 4칸 이동 ( 검수 기준점 Z 기준 4칸 이동 )

	3) 
	A B C X D E Z C A B A C A B A C
	              A B A C
	-> A != C 로 통과 못함. A 는 표에 1로 정의돼있으므로, 기준점 A (한번도 통과못했으므로, 기준점은 여전히 A) 를 기준으로 1칸 이동

	4)
	A B C X D E Z C A B A C A B A C
					A B A C
	-> 통과


	□ 예시 정리
	위 예시를 통해, 정리표의 표는 해당 매핑되지 않은 문자열을 최소로 우측 이동하여, 
	매핑되지 않았던 문자열과 매핑시키도록 하는 역할임을 알 수 있다.

	만약 매핑되는 문자열이 없다면, 어차피 조금씩 이동해도 매핑될 가능성이 없기에, 검색 문자열의 크기 만큼 우측 이동하도록 한다
	[이동시, 1), 3) 처럼 검색 문자열의 첫번째 인덱스 는 매핑부재 문자열의 바로 우측에 위치하게 된다]



	□ 하단 코드의  tp += .. searchLen - sp; 의 우항 설명
	
	위 설명만을 보고 이해한다면, 위 코드는 tp += skip[text[tp]]; 로도 충분할거다.
	
	왜 우항의 searchLen - sp 와 비교하고,
	조건부로 우항을 대입하는지에 대해 설명하면,

	코드를 보면 tp 와 sp 는 루프문에서 함께 -- 되고 있다. 즉, 좌항 tp 와 우항 searchLen - sp 는 동일한 값으로 감소한다.
	감소량을 x라 하고, 위 수식을 풀어보면,
		tp += searchLen - sp
	<-> tp - x += searchLen - (searchLen - 1 - x) = searchLen - searchLen + 1 + x = 1 + x
	<-> tp - x += 1 + x
	<-> tp += 1 
	이다.
	
	즉 루프문으로 인해 tp 가 얼만큼 감소하는 것과 무관하게, tp 가 최소한 우측으로 1만큼을 이동할 수 있음을 보장하는 코드다

	예를 들어
	(텍스트) C B A A D
	(패턴)   B B C A D

	(인덱스) 0 1 2 3 4
	
	라 하자.
	D(tp = 4), A(tp = 3) 두번 검수를 통과한 상태에서, A != C (tp = 2)로 불일치가 발생했다.
	위 상태에서 tp 는 불일치가 발생한 A(tp = 2)에 위치한다. 매핑에서 A-> 1 이므로 1만큼 우측 이동한다면,
	tp = 3 이 되어,

		C B A A D
	  B B C A D

	 -1 0 1 2 3
	
	로 후진하게 되어, 무한 루프에 빠진다.

	우항 코드는 이를 방지하여, 최초 tp 보다 우측으로 최소 1만큼 이동하는 것을 보장하여,

	tp(2) += 3 (검수를 두번 통과햇으므로 1 + 2 = 3)
	로 tp = 5 가 되게하여,
	C B A A D
	  B B C A D(tp = 5)
	
	로 우측으로 1칸 이동하게 된다
	

*/
int StringMatch::BoyerMoor(const STRING& txt, const STRING& search)
{
	const int txtLen = txt.size();
	const int searchLen = search.size();

	if (txtLen == 0) return 0;
	if (txtLen < searchLen) return -1;

	
	int skip[WCHAR_MAX + 1];
	for (int i = 0; i <= WCHAR_MAX; i++)
	{
		skip[i] = searchLen;
	}

	int tp;
	int sp;

	for (tp = 0; tp < searchLen - 1; tp++)
	{
		skip[search[tp]] = searchLen - tp - 1;
	}
	// tp == searchLen - 1

	while (tp < txtLen)
	{
		sp = searchLen - 1;

		while(txt[tp] == search[sp])
		{
			if (sp == 0)
			{
				return tp;
			}

			tp--;
			sp--;
		}
		
		tp += skip[txt[tp]] > searchLen - sp ? skip[txt[tp]] : searchLen - sp;
	}

	return -1;
}
