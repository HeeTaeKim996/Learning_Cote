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
	int index;
	map<Node*, int> nexts;

	bool visited;
	int dist;
	Node* prev;
};

struct Graph
{
	void Initialize(int n, vector<vector<int>>& edges, int start)
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

		startNode = nodes[start];
	}

	vector<int> Dijkstra(Node* sNode)
	{
		// 초기화
		for (Node* node : nodes)
		{
			node->visited = false;
			node->dist = INT32_MAX;
			node->prev = nullptr;
		}

		sNode->dist = 0;

		int repTime = nodes.size() - 1; // start 는 갱신할 필요 없으니, n - 1번
		while (repTime-- > 0)
		{
			Node* closest = nullptr;
			int min = INT32_MAX;

			for (Node* node : nodes)
			{
				if (node->visited == true) continue;

				if (node->dist < min)
				{
					min = node->dist;
					closest = node;
				}
			}

			if (closest == nullptr) break; // 더이상 갱신 불가, 탈출
			closest->visited = true;
			
			for (auto& [to, cost] : closest->nexts)
			{
				int newDistance = closest->dist + cost;
				if (newDistance < to->dist)
				{
					to->dist = newDistance;
					to->prev = closest;
				}
			}
		}

		// DEBUG
		for (Node* node : nodes) printf("%2d ", node->dist);
		printf("\n");
		for (Node* node : nodes) printf("%2d ", node->prev != nullptr ? node->prev->index : -1);
		printf("\n");
		
		vector<int> answer(nodes.size());
		for (int i = 0; i < nodes.size(); i++)
		{
			answer[i] = nodes[i]->dist;
		}

		return answer;
	}

	

	Node* startNode;
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
			graph.Initialize(n, e, start);
			map<Node*, Node*> prev;
			graph.Dijkstra(graph.startNode);

		};

	Temp(e1, 0, 3);
	Temp(e2, 0, 4);
}





#endif