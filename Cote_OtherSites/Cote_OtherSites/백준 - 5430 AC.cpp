#if 1

// https://www.acmicpc.net/problem/5430

#include <string>
#include <vector>

using namespace std;

struct AC
{
	AC(vector<int> InData) 
	{ 
		data = InData; 
		startIndex = 0; 
		lastIndex = data.size() - 1; 
	}

	void R()
	{
		if (dead) return;
		reversed = !reversed;
	}

	void D()
	{
		if (dead) return;
		if (!reversed) startIndex++;
		else lastIndex--;

		if (lastIndex < startIndex)
		{
			dead = true;
		}
	}

	void Print()
	{
		if (dead)
		{
			printf("error\n");
		}
		else
		{
			if (!reversed)
			{
				for (int i = startIndex; i <= lastIndex; i++)
				{
					printf("%d,\t", data[i]);
				}
				printf("\n");
			}
			else
			{
				for (int i = lastIndex; i >= startIndex; i--)
				{
					printf("%d, ", data[i]);
				}
				printf("\n");
			}

		}
	}

	bool dead = false;
	bool reversed = false;
	int startIndex;
	int lastIndex;
	vector<int> data;
};	

void solution(string orders, vector<int> arr)
{
	AC ac(arr);

	for (char ch : orders)
	{
		if (ch == 'R')
		{
			ac.R();
		}
		else
		{
			ac.D();
		}
	}

	ac.Print();
}


int main()
{
	printf("https://www.acmicpc.net/  __  백준 - 5430 AC  \n\n\n");


	vector<int> v1 = { 1,2,3,4 };
	solution("RDD", v1);

	vector<int> v2 = { 42 };
	solution("DD", v2);

	vector<int> v3 = { 1, 1, 2, 3, 5, 8 };
	solution("RRD", v3);

	vector<int> v4 = {};
	solution("D", v4);

	return 0;
}







#endif