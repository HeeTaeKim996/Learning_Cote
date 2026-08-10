#if 0
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

// ※ nodes 는 벡터 고정으로 하자. 절대 map 쓰지 말자 [ 성능 낭비 + for(auto.. )할 때 손가락만 아픔 ]. 만약 찾는 node가 있다면, Initialize 때 멤버 로 따로 보관해두면 된다. 아래의 StartNode 예시처럼.

struct Node
{
	Node(int InIndex) : index(InIndex) {}
	int index = -1;
	map<Node*, int> nexts;

	int dist;
	Node* prev;
};

struct Graph
{
	void Initialize(int n, vector<vector<int>>& edges, int start)
	{
		nodes.resize(n, nullptr);

		for (vector<int>& edge : edges)
		{
			int from = edge[0];
			int to = edge[1];
			int cost = edge[2];

			if (nodes[from] == nullptr) nodes[from] = new Node(from);
			if (nodes[to] == nullptr) nodes[to] = new Node(to);

			nodes[from]->nexts[nodes[to]] = cost;
		}

		startNode = nodes[start];
	}

	vector<int> BellmanFord(Node* start)
	{
		for (Node* node : nodes)
		{
			node->dist = INT32_MAX;
			node->prev = nullptr;
		}

		start->dist = 0;

		int repTime = nodes.size() - 1; // 다익스트라랑 마찬가지로, n -1
		while(repTime-- > 0)
		{
			for (Node* from : nodes)
			{
				if (from->dist == INT32_MAX) continue;

				for (auto& [to, cost] : from->nexts)
				{
					int newDistance = from->dist + cost;
					if (newDistance < to->dist)
					{
						to->dist = newDistance;
						to->prev = from;
					}
				}
			}
		}

		// 완성됐지만, 여기서 싸이클 한번 더 돌려서, 여기서 더 최적인 경우가 생긴다는 건, 음의 순환이 있는 것이므로, return vector<1, -1>
		for (Node* from : nodes)
		{
			for (auto& [to, cost] : from->nexts)
			{
				int newDistance = from->dist + cost;
				if (newDistance < to->dist)
				{
					return vector<int>(1, -1);
				}
			}
		}

		for (Node* node : nodes) printf("%2d ", node->dist);
		printf("\n");
		for (Node* node : nodes) printf("%2d ", node->prev != nullptr ? node->prev->index : -1);
		printf("\n");

	}

	Node* startNode;
	vector<Node*> nodes;
};

void main()
{
	printf("11.그래프.알고리즘_밸만포드알고리즘");
	printf("\n\n\n");


	vector<vector<int>> e1 =
	{
		{0, 1, 4}, {0, 2, 3},
		{0, 4, -6}, {1, 3, 5},
		{2, 1, 2}, {3, 0, 7},
		{3, 2, 4}, {4, 2, 2}
	};
	vector<vector<int>> e2
	{
		{0, 1, 5}, {0, 2, -1},
		{1, 2, 2}, {2, 3, -2},
		{3, 0, 2}, {3, 1, 6}
	};

	auto Temp = [&](vector<vector<int>>& e, int n, int start)
		{
			Graph graph;
			graph.Initialize(n, e, start);
			graph.BellmanFord(graph.startNode);
		};

	Temp(e1, 5, 0);
	Temp(e2, 4, 0);
}


#endif