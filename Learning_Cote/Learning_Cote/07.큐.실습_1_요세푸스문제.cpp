#if 0


#include <string>
#include <vector>

using namespace std;

#if 0
struct Node
{
	int index;
	Node* front;
	Node* rear;
};
int solution(int n, int k)
{
	// Member : Nodes, curr
	vector<Node> nodes(n);

	nodes[0].index = 0;
	nodes[0].front = &nodes[n - 1];
	nodes[0].rear = &nodes[1];
	for (int i = 1; i < n - 1; i++)
	{
		nodes[i].index = i;
		nodes[i].front = &nodes[i - 1];
		nodes[i].rear = &nodes[i + 1];
	}
	nodes[n - 1].index = n - 1;
	nodes[n - 1].front = &nodes[n - 2];
	nodes[n - 1].rear = &nodes[0];

	int curr = 0;

	while (true)
	{
		int rep = k - 1;

		Node* nextNode = &nodes[curr];

		if (nextNode == nextNode->rear) return (nextNode->index + 1);

		while (rep-- > 0)
		{
			nextNode = nextNode->rear;
		}
		printf("%d, ", nextNode->index + 1);

		nextNode->front->rear = nextNode->rear;
		nextNode->rear->front = nextNode->front;

		curr = nextNode->rear->index;
	}
}

// ※ 위처럼 해봤는데, 성능이 안좋다 함. 무시.

#else
#include <queue>
int solution(int n, int k)
{
	queue<int> q;

	for (int i = 1; i <= n; i++) q.push(i);

	while (q.size() > 1)
	{
		for (int i = 0; i < k - 1; i++)
		{
			q.push(q.front());
			q.pop();
		}
		q.pop();
	}

	return q.front();
}
// 세그먼트 트리로 하면 성능이 좋지만, 교재에서 예시를 위해 큐를 사용
#endif




void main()
{
	printf("07.큐.실습_1_요세푸스문제");
	printf("\n\n\n");

	printf("result : %d\n", solution(5, 2));
}

#endif