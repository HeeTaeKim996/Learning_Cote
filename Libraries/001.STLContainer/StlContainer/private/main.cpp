#include "pch.h"
#include "Std.h"
#include "Vector.h"

int main()
{
	//StdExplain::test();

	Vector<int> vecs;
	vecs.push_back(1);
	vecs.push_back(2);
	vecs.push_back(3);

	vecs.insert(vecs.begin() + 1, 9);

	for (int i = 0; i < vecs.size(); i++)
	{
		printf("%d, ", vecs[i]);
	}
}

