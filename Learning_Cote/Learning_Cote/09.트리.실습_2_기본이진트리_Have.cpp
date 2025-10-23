#if 1
#include <string>
#include <vector>

using namespace std;


struct Node
{
	int parent;
	int left;
	int right;
	int value;
};

struct Tree
{
	vector<Node> nodes;
	int rootIndex = -1;

	void Add(int value)
	{
		if (rootIndex == -1)
		{
			nodes.push_back({ -1, -1, -1, value });
			rootIndex = 0;
			return;
		}

		int curr = rootIndex;
		while (true)
		{
			Node& node = nodes[curr];

			if (node.value > value)
			{
				if (node.left == -1)
				{
					node.left = nodes.size();
					nodes.push_back({ curr, -1, -1, value });
					return;
				}
				curr = node.left;
			}
			else
			{
				if (node.right == -1)
				{
					node.right = nodes.size();
					nodes.push_back({ curr, -1, -1, value });
					return;
				}
				curr = node.right;
			}
		}
	}

	bool Have(int index, int val)
	{
		Node& node = nodes[index];
		if (node.value == val) return true;
		if (node.left != -1) if (Have(node.left, val)) return true;
		if (node.right != -1) if (Have(node.right, val)) return true;

		if (index == rootIndex) return false;
	}



};


#include <functional>

void main()
{
	printf("09.트리.실습_2_기본이진트리_Have");
	printf("\n\n\n");

	auto Temp = [&](vector<int> v, vector<int> c)
		{
			Tree tree;
			for (int i : v)
			{
				tree.Add(i);
			}

			for (int i : c)
			{
				printf("%d, ", tree.Have(0, i));
			}
			printf("\n");
		};


	vector<int> v1 = { 5, 3, 8, 4, 2, 1, 7, 10 };
	vector<int> c1 = { 1, 2, 5, 6 };

	vector<int> v2 = { 1, 3, 5, 7, 9 };
	vector<int> c2 = { 2, 4, 6, 8, 10 };

	Temp(v1, c1);
	Temp(v2, c2);
}




#endif