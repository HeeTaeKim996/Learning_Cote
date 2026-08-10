#if 0
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


string solution(int decimal)
{
	string ret;

	while (decimal > 0)
	{
		if ((decimal & 1) == 1) ret += '1';
		else					ret += '0';

		decimal >>= 1;
	}



	return string(ret.rbegin(), ret.rend());
}


void main()
{
	printf("06.스택_실습_2_10진수를_2진수로_변환하기");
	printf("\n\n\n");


	printf("%s,\t", solution(10).c_str());
	printf("%s,\t", solution(27).c_str());
	printf("%s,\t", solution(12345).c_str());
}





#endif