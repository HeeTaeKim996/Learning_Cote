#if 0
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <set>

using namespace std;

struct Node
{
	Node(char InC) : c(InC) {}
	char c;
	vector<Node*> nexts;
};

struct Graph
{
	void Add(pair<char, char> pair)
	{
		auto fIt = nodes.find(pair.first);
		if (fIt == nodes.end()) nodes[pair.first] = new Node(pair.first);
		auto sIt = nodes.find(pair.second);
		if (sIt == nodes.end()) nodes[pair.second] = new Node(pair.second);

		nodes[pair.first]->nexts.push_back(nodes[pair.second]);
	}

	void DepthSearch(Node* node)
	{
		visited.clear();
		DepthRecur(node);
	}
	void DepthRecur(Node* node)
	{
		printf("%c, ", node->c);
		visited.insert(node);
		
		for (Node* next : node->nexts)
		{
			auto it = visited.find(next);
			if(it == visited.end()) DepthRecur(next);
		}
	}

	void BreadthSearch(Node* InNode)
	{
		visited.clear();
		queue<Node*> queue;
		queue.push(InNode);

		while (!queue.empty())
		{
			Node* node = queue.front();
			queue.pop();

			auto it = visited.find(node);
			if (it != visited.end()) continue;

			printf("%c, ", node->c);
			visited.insert(node);

			for (Node* next : node->nexts)
			{
				queue.push(next);
			}
		}
	}



	map<char, Node*> nodes;
	set<Node*> visited;
};


void main()
{
	printf("11.그래프.알고리즘_기본");
	printf("\n\n\n");

	vector<pair<char, char>> gr1 = { {'A', 'B'}, {'B', 'C'}, {'C', 'D'}, {'D', 'E'} };
	vector<pair<char, char>> gr2 = { {'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'B', 'E'}, {'C', 'F'}, {'E', 'F'} };

	auto Temp = [&](vector<pair<char, char>> gr)
		{
			Graph graph;
			for (pair<char, char>& pair : gr) graph.Add(pair);

			graph.DepthSearch(graph.nodes['A']);
			printf("\n");
			graph.BreadthSearch(graph.nodes['A']);
			printf("\n\n");
		};

	Temp(gr1);
	Temp(gr2);
}





#endif