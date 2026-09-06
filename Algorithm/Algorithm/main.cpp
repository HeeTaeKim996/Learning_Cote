#include "pch.h"
#include <iostream>
#include "Search.h"
#include "Sort.h"
#include "Array.h"
#include "3.1.StringMatch.h"
#include "3.2.Trie.h"

#include "use_vector.h"
#include "use_priority_queue.h"

int main()
{
	//Search::test();
	//Sort::test();
	//test_Array();
	//StringMatch::test();
	//Trie::test();


	vector<int> vec;
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(2);

	for (int i = 0; i < vec.size(); i++)
	{
		printf("%d, ", vec[i]);
	}

	priority_queue<int> pq;
	pq.push(1);
	pq.push(3);
	pq.push(2);
	printf("\npq : ");
	while (pq.empty() == false)
	{
		int top = pq.top();
		printf("%d, ", top);
		pq.pop();
	}
}


