#if 0

#include <string>
#include <vector>

using namespace std;


struct Node
{	
	int parent;
	int left = -1;
	int right = -1;
	int value;
};

struct Tree
{
	std::vector<Node> nodes;
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

	void PreOrder(int index)
	{
		Node& node = nodes[index];

		printf("%d\t", node.value);
		if (node.left != -1) PreOrder(node.left);
		if (node.right != -1) PreOrder(node.right);
	}
	void InOrder(int index)
	{
		Node& node = nodes[index];
		if (node.left != -1) InOrder(node.left);
		printf("%d\t", node.value);
		if (node.right != -1) InOrder(node.right);
	}
	void PostOrder(int index)
	{
		Node& node = nodes[index];
		if (node.left != -1) PostOrder(node.left);
		if (node.right != -1) PostOrder(node.right);
		printf("%d\t", node.value);
	}
};






void main()
{
	printf("09.트리.실습_1_기본이진트리");
	printf("\n\n\n");

	Tree tree;
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
	for (int i : v)
	{
		tree.Add(i);
	}
	tree.PreOrder(tree.rootIndex);
	printf("\n");
	tree.InOrder(tree.rootIndex);
	printf("\n");
	tree.PostOrder(tree.rootIndex);
}


#endif