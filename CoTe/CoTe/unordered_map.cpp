
#if 0

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using int64 = long long;

struct Test
{
	bool operator ==(const Test& other) const noexcept
	{
		return xPos == other.xPos && yPos == other.yPos;
	}

	int xPos = 0;
	int yPos = 0;
};

struct Hash_Test
{
	size_t operator()(const Test& test) const noexcept
	{
		int64 ret = static_cast<int64>(test.yPos);
		ret += static_cast<int64>(test.xPos << 32);
		return ret;
	}
};


void main()
{
	unordered_map<Test, int, Hash_Test> testMap;

	Test t1;
	t1.xPos = 10;
	t1.yPos = -10;
	testMap[t1] = 1;

	Test t2;
	t2.xPos = 10;
	t2.yPos = -10;
	if (auto it = testMap.find(t2) != testMap.end())
	{
		testMap[t2]++;
	}

	printf("%d", testMap[t1]);
}


// ※ 이건 통째로 외우자. 유용하다!!

#endif