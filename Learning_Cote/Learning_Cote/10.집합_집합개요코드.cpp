#if 0
#include <string>
#include <vector>

using namespace std;

struct Node
{
	Node(int InValue) : value(InValue) { }

	int value;
	int rank = 0;
	Node* parent = nullptr;
};

struct Set
{
	void Initialize(int count)
	{
		for (int i = 0; i < count; i++)
		{
			Node* newNode = new Node(i); // 예제 value 는 대충 index로 했음
			nodes.push_back(newNode);
		}
	}

	Node* Find(Node* node)
	{
		if (node->parent == nullptr) return node;

		node->parent = Find(node->parent);

		return node->parent;
	}

	void UnionSet(Node* x, Node* y)
	{
		Node* root1 = Find(x);
		Node* root2 = Find(y);

		if (root1->rank > root2->rank)
		{
			root2->parent = root1;
		}
		else if (root1->rank < root2->rank)
		{
			root1->parent = root2;
		}
		else
		{
			root2->parent = root1;
			root1->rank++;
		}
	}

	vector<Node*> nodes;




};


void main()
{
	printf("10.집합_집합개요코드");
	printf("\n\n\n");


	Set set;
	set.Initialize(10);
	
	Node* ret = set.Find(set.nodes[7]);
	printf("%d \n", ret->value);

	set.UnionSet(set.nodes[7], set.nodes[8]);
	Node* ret2 = set.Find(set.nodes[8]);
	printf("%d \n", ret2->value);

	set.UnionSet(set.nodes[8], set.nodes[9]);
	Node* ret3 = set.Find(set.nodes[9]);
	printf("%d \n", ret3->value);
}




#endif