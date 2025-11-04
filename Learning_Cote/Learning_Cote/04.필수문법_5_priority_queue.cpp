#if 0
#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;


/*
	- pq 는 힙정렬을 기반으로 작동.
	- pq 의 탑은 루트 노드
	- pq 의 Comparator 의 operator 가 true일시, a, b 에서 a를 b의 자식 노드로 설정 ( a 가 b 보다 top 에서 멀어지도록 )
*/

struct Node
{
	Node(string s, int i) : name(s), num(i) {}
	Node() {}


	string name;
	int num;
};

struct Comparator
{
	bool operator()(const Node& a, const Node& b)
	{
		if (a.name == b.name) return a.num > b.num;
		return a.name > b.name;
	}
};




int main()
{
	printf("04.필수문법_5_priority_queue");
	printf("\n\n\n");

	Node node1("harry", 15);
	Node node2("harry", 2);
	Node node3("borry", 13);
	Node node4("borry", 12);
	Node node5("heetae", 29);
	Node node6("heetae", 3);
	

	priority_queue<Node, vector<Node>, Comparator> pq;
	pq.push(node3);
	pq.push(node1);
	pq.push(node5);
	pq.push(node4);
	pq.push(node6);
	pq.push(node2);

	while (!pq.empty())
	{
		const Node& node = pq.top();
		printf("%s : %d\n", node.name.c_str(), node.num);

		pq.pop();
	}


	return 0;
}




#endif