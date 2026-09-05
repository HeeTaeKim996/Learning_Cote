#include "pch.h"
#include "Std.h"
#include "Vector.h"

#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	//StdExplain::test();

	Vector<int> vecs;
	vecs.push_back(1);
	vecs.push_back(2);
	vecs.push_back(3);

	vecs.insert(vecs.begin() + 1, 9);

	for (int i = 0; i < vecs.size(); ++i)
	{
		printf("%d, ", vecs[i]);
	}
	printf("\n");
	for (auto it = vecs.begin(); it != vecs.end(); ++it)
	{
		printf("%d, ", *it);
	}
	printf("\nReverse: \n");
	for (auto it = vecs.rbegin(); it != vecs.rend(); ++it)
	{
		printf("%d, ", *it);
	}

	vector<int> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(2);
	sort(v.begin(), v.end());

	v.begin();

	v.insert(v.begin() + 2, 3);
}

