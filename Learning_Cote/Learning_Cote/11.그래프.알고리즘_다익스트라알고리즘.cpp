#if 0
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;



struct Node
{
	Node(int InIndex) : index(InIndex) {}
	int index;
	map<Node*, int> nexts;
};

struct Graph
{
	void Initialize(int n, vector<vector<int>>& edges)
	{
		nodes.resize(n, nullptr);

		for (auto& edge : edges)
		{
			int from = edge[0];
			int to = edge[1];
			int cost = edge[2];
			if (nodes[from] == nullptr) nodes[from] = new Node(from);
			if (nodes[to] == nullptr) nodes[to] = new Node(to);

			nodes[from]->nexts[nodes[to]] = cost;
		}
	}

	vector<int> Dijkstra(int start)
	{
		vector<int> dist(nodes.size(), INT32_MAX);
		vector<int> prev(nodes.size(), -1);	// 코테에서는 필요 없음
		vector<bool> visited(nodes.size(), false);

		dist[start] = 0;

		int repTime = nodes.size() - 1; // start 는 갱신할 필요 없으니, n - 1번
		while (repTime-- > 0)
		{
			int closest = -1;
			int min = INT32_MAX;

			for (int i = 0; i < nodes.size(); i++)
			{
				if (visited[i] == false && dist[i] < min)
				{
					min = dist[i];
					closest = i;
				}
			}

			visited[closest] = true;
			
			Node* node = nodes[closest];
			for (auto& [to, cost] : node->nexts)
			{
				int newDistance = dist[closest] + cost;
				if (newDistance < dist[to->index])
				{
					dist[to->index] = newDistance;
					prev[to->index] = node->index;
				}
			}
		}

		for (int i : dist) printf("%d ", i);
		printf("\n");
		for (int i : prev) printf("%d ", i);
		printf("\n\n");

		return dist;
	}

	


	vector<Node*> nodes;
};



void main()
{
	printf("임시");
	printf("\n\n\n");


	vector<vector<int>> e1 = { {0, 1, 9}, {0, 2, 3}, {1, 0, 5}, {2, 1, 1} };
	vector<vector<int>> e2 = { {0, 1, 1}, {1, 2, 5}, {2, 3, 1} };

	auto Temp = [&](vector<vector<int>>& e, int start, int n)
		{
			Graph graph;
			graph.Initialize(n, e);
			map<Node*, Node*> prev;
			graph.Dijkstra(start);

		};

	Temp(e1, 0, 3);
	Temp(e2, 0, 4);
}





#endif