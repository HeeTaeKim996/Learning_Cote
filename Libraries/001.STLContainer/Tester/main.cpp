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

	struct Temp
	{
		Temp(int inI, int inJ) : i(inI), j(inJ) {}
		Temp() {}
		int i;
		int j = 0;
	};

	printf("\n\nTemps : \n");
	Vector<Temp> temps;
	temps.push_back(Temp(1, 0));
	temps.push_back(Temp(2, 0));
	temps.push_back(Temp(3, 0));

	temps.insert(temps.begin() + 1, Temp(9, 0));
	temps.emplace(temps.begin() + 1, 7, 0);

	for (int i = 0; i < temps.size(); ++i)
	{
		printf("%d, ", temps[i].i);
	}

}

