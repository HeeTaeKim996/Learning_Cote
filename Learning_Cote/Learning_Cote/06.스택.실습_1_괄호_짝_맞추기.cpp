#if 0


#include <string>
#include <vector>

using namespace std;

bool solution(string s)
{
	vector<bool> stack;

	for (char ch : s)
	{
		if (ch == '(')
		{
			stack.push_back(true);
		}
		else if (ch == ')')
		{
			if (stack.empty()) return false;
			stack.pop_back();
		}
		else
		{
			continue;
		}
	}

	return stack.empty();
}


void main()
{
	printf("06.스택.실습_1_괄호_짝_맞추기");
	printf("\n\n\n");

	string s1 = "()";
	string s2 = "())";
	string s3 = "(())()";
	string s4 = "((())()";
	printf("%d \n", solution(s1)); // 1 리턴해야 함
	printf("%d \n", solution(s2)); // 0 리턴해야 함
	printf("%d \n", solution(s3)); // 1 리턴해야 함
	printf("%d \n", solution(s4)); // 0 리턴해야 함
}



#endif