

#if 0

#include <string>
#include <vector>
#include <map>

using namespace std;

struct TEST
{
	bool operator<(const TEST& other) const noexcept
	{
		if (y != other.y) return y < other.y;
		return x < other.x;
	}

	int y;
	int x;
};

void main()
{
	::map<TEST, int> testMap;

	TEST t1;
	t1.y = 10;
	t1.x = 5;
	testMap[t1] = 1;


	TEST t2;
	t2.y = 10;
	t2.x = 5;
	auto it = testMap.find(t2);
	if (it != testMap.end())
	{
		testMap[t2]++;
	}
	

	printf("%d", testMap[t1]);
}




#endif