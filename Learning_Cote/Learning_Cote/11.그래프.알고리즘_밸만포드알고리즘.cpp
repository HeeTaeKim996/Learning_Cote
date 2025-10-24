#if 1
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

struct Node
{
	Node(int InIndex) : index(InIndex) {}
	int index = -1;
	map<Node*, int> nexts;
};

struct Graph
{
	void Initialize(int n, vector<vector<int>>& edges)
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
	}

	vector<int> BellmanFord(Node* start)
	{
		vector<int> prev(nodes.size(), -1); // 마찬가지로 코테에서는 필요 없음
		vector<int> dist(nodes.size(), INT32_MAX);

		dist[start->index] = 0;

		int repTime = nodes.size() - 1; // 다익스트라랑 마찬가지로, n -1
		while(repTime-- > 0)
		{
			for (Node* from : nodes)
			{
				if (dist[from->index] == INT32_MAX) continue;

				for (auto& [to, cost] : from->nexts)
				{
					int newDistance = dist[from->index] + cost;
					if (newDistance < dist[to->index])
					{
						dist[to->index] = newDistance;
						prev[to->index] = from->index;
					}
				}
			}
		}

		// 완성됐지만, 여기서 싸이클 한번 더 돌려서, 여기서 더 최적인 경우가 생긴다는 건, 음의 순환이 있는 것이므로, return vector<1, -1>
		for (Node* from : nodes)
		{
			for (auto& [to, cost] : from->nexts)
			{
				int newDistance = dist[from->index] + cost;
				if (newDistance < dist[to->index])
				{
					return vector<int>(1, -1);
				}
			}
		}

		for (int i : dist) printf("%2d ", i);
		printf("\n");
		for (int i : prev) printf("%2d ", i);
		printf("\n\n");

	}


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
			graph.Initialize(n, e);
			graph.BellmanFord(graph.nodes[start]);
		};

	Temp(e1, 5, 0);
	Temp(e2, 4, 0);
}


#endif