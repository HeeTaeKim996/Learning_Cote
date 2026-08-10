#if 0
#include <string>
#include <vector>

using namespace std;

bool IsPrime(int a)
{
	if (a <= 1) return false;
	
	if (a == 2) return true;

	if (a % 2 == 0) return false;

	for (int i = 3; i * i <= a; i += 2)
	{
		if (a % i == 0) return false;
	}
	return true;
}

void main()
{
	printf("999.기타_4_IsPrime");
	printf("\n\n\n");

	for (int i = 0; i < 20; i++)
	{
		printf("%d : %d\n", i, IsPrime(i));
	}
}




#endif