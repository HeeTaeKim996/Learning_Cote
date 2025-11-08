#if 1

/*
	- 트리에서 노드 사이 삽입, 부모에 삽입 하면 코드가 번거로워지는데, 코테에서는 Sort + Compare 로 인해 필요 없다
	 -> Tree 를 만든다 해도, 자식만 생성하는 아래와 같은 구조만 외우면 됨

	- 트리가 나오는 경우는 매우 드문데, 트리를 만들어봤자, Sort + Compare 로 인해, 대부분 왼쪽 자식 없이 오른쪽 자식만 나열된 경우가 대부분이기 때문
	- 따라서 자식 부모를 직접 주는 문제나, https://school.programmers.co.kr/learn/courses/30/lessons/42892 처럼 2차원 의 데이터일 때 등에서 제한적으로 사용됨

	- 아무튼 정리하면, Sort + Compare 로 인해, Tree 는 아래 구조만 외워도 충분하다

	 ※ FindEmpty 에서 리턴값과 매개변수가 Node* 가 아닌, Node*& 임에만 주의하자 !
*/


#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct Node
{
	int value;
	int y;
	int x;
	Node* left = nullptr;
	Node* right = nullptr;
};


struct Tree
{
	Node*& FindEmpty(Node*& node, int x)
	{
		if (node == nullptr) return node;

		if (x < node->x)
		{
			return FindEmpty(node->left, x);
		}
		else
		{
			return FindEmpty(node->right, x);
		}
	}

	void Add(int x, int value)
	{
		Node*& node = FindEmpty(root, x);
		node = new Node();
		node->x = x;
		node->value = value;
	}
	void InOrder(Node* node)
	{
		if (node == nullptr) return;

		InOrder(node->left);
		printf("%d, ", node->value);
		InOrder(node->right);
	}
	void PreOrder(Node* node)
	{
		if (node == nullptr) return;

		printf("%d, ", node->value);
		PreOrder(node->left);
		PreOrder(node->right);
	}
	void PostOrder(Node* node)
	{
		if (node == nullptr) return;
		PostOrder(node->left);
		PostOrder(node->right);
		printf("%d, ", node->value);
	}
	bool Have(Node* node, int x)
	{
		if (node == nullptr) return false;
		if (node->x == x) return true;

		if (Have(node->left, x) == true) return true;
		if (Have(node->right, x) == true) return true;
		return false;
	}


	Node* root = nullptr;
};

struct Temp
{
	int value;
	int y;
	int x;
};


void main()
{
	printf("09.트리.필요알고리즘");
	printf("\n\n\n");

	auto Compare = [&](const Temp& a, const Temp& b)
		{
			if (a.y == b.y) return a.x < b.x;
			return a.y > b.y;
		};

	// ※ 아래 데이터는 https://school.programmers.co.kr/learn/courses/30/lessons/42892 에서 가져옴
	vector<vector<int>> data = {
		{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}
	};
	vector<Temp> temps;
	temps.reserve(data.size());
	for (int i = 0; i < data.size(); i++)
	{
		Temp temp;
		temp.value = i + 1;
		temp.x = data[i][0];
		temp.y = data[i][1];
		temps.push_back(temp);
	}

	sort(temps.begin(), temps.end(), Compare);

	Tree tree;
	for (Temp& temp : temps)
	{
		tree.Add(temp.x, temp.value);
	}

	tree.PreOrder(tree.root);
	printf("\n");
	tree.InOrder(tree.root);
	printf("\n");
	tree.PostOrder(tree.root);
	printf("\n");

	printf("Have : %d\n", tree.Have(tree.root, 13));
	printf("Have : %d\n", tree.Have(tree.root, 15));
}






#endif