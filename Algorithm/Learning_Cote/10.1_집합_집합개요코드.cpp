#if 0
#include <string>
#include <vector>

using namespace std;

struct Node
{
	Node(int InValue) : value(InValue) { }

	int value;
	int rank = 0;
	Node* root = nullptr;
};

struct Set
{
	static Node* getRoot(Node* node)
	{
		if (node->root == nullptr) return node;

		node->root = getRoot(node->root);

		return node->root;
	}

	static void Union(Node* a, Node* b)
	{
		Node* rootA = getRoot(a);
		Node* rootB = getRoot(b);

		if (rootA == rootB) return;

		if (rootA->rank > rootB->rank)
		{
			rootB->root = rootA;
		}
		else if (rootA->rank < rootB->rank)
		{
			rootA->root = rootB;
		}
		else
		{
			rootB->root = rootA;
			rootA->rank++;
		}
	}
};


void main()
{
	printf("10.집합_집합개요코드");
	printf("\n\n\n");

	int count = 10;

	vector<Node*> nodes;
	nodes.reserve(10);
	for (int i = 0; i < count; i++)
	{
		Node* newNode = new Node(i); // 예제 value 는 대충 index로 했음
		nodes.push_back(newNode);
	}

	
	Node* ret = Set::getRoot(nodes[7]);
	printf("%d \n", ret->value);

	Set::Union(nodes[7], nodes[8]);
	Node* ret2 = Set::getRoot(nodes[8]);
	printf("%d \n", ret2->value);

	Set::Union(nodes[8], nodes[9]);
	Node* ret3 = Set::getRoot(nodes[9]);
	printf("%d \n", ret3->value);
}




#endif