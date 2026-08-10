#if 0
#include <string>
#include <vector>

using namespace std;
using uint32 = unsigned long;

/*
	- 아래 nCr에서, 연산 순서가  ret * (n - r + i) / i 로 오버플로우 여지를 남기며, 수리 공식에 익숙한 높은 차수에서 내려가지 않고, for(int i = 1; i <= r; i++) 로 낮은 차수에서 높은 차수로 올라가는 이유눈,
	  위 두 조건을 만족해야, 정수 나눗샘에서 절사가 일어나지 않기 때문.
	- 위 내용을 수리적으로 증명가능하다는데, 증명하지는 않음. 
	- 곱샘을 먼저하고 나눗샘을 먼저 하기에, 오버플로우 가능성이 있음. 그래서 통상적으로 용량? 의 2배가 되는 타입을 사용한다 함. int64 가 리턴이면, __int128 을 사용한다 함
	
	- 아무튼 정리하면, 1) 곱샘 후 나눗샘 연산. 2) 낮은 차수에서 높은 차수로 연산 3) 리턴에 사용되는 변수는 용량 2배 변수 사용
	  위 셋을 꼭 기억하자
	*/

int nCr(int n, int r)
{
	if (r > n) return 0;

	if (n - r < r) r = n - r;

	uint32 ret = 1;

	for (int i = 1; i <= r; i++)
	{
		ret = ret * (n - r + i) / i;
	}

	return ret;
}


int nHr(int n, int r)
{
	return nCr(n + r - 1, r);
}


int main()
{
	printf("999.기타_3_nCr_nHr");
	printf("\n\n\n");

	printf("nCr :  %d \n", nCr(5, 2));

	printf("nHr : %d \n", nHr(5, 2));

	return 0;
}


#endif