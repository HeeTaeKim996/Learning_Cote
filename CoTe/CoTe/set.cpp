


#if 0
#include <string>
#include <vector>
#include <set>

using namespace std;


struct Test
{
	bool operator<(const Test& other) const noexcept
	{
		if (y != other.y) return y < other.y;
		return x < other.x;
	}

	int y;
	int x;
};


void main()
{
	set<Test> testSet;

	Test t1;
	t1.y = 10;
	t1.x = 5;
	testSet.insert(t1);

	Test t2;
	t2.y = 10;
	t2.x = 5;

	auto it = testSet.find(t2);
	if (it != testSet.end())
	{
		printf("CHECK");
	}


}






#endif