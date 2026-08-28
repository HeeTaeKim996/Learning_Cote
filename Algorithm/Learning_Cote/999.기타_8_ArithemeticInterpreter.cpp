#if 1

#include <stdio.h>
#include <string>

using namespace std;

enum NodeType
{
	none,
	root,
	num,
	op // 연산자는 이항 연산자만 가정한다
};

class Node
{
public:
	Node(NodeType inNodeType)
	{
		nodeType = inNodeType;
	}

public:
	virtual bool checkPriorIsValid(Node prior) = 0;

public:
	Node* left;
	Node* right;
	NodeType nodeType;
};

class NumNode : Node
{
	using super = Node;

public:
	NumNode() : super(NodeType::num){}

public:
	virtual bool checkPriorIsValid(Node prior) override
	{
		switch (prior.nodeType)
		{
		case NodeType::op:
			return true;

		case NodeType::none:
		case NodeType::num:
		default:
			return false;
		}
	}

public:
	bool isFloat = false;
	union 
	{
		int intVal;
		float floatVAl;
	};
};

class OpNode : Node
{
	using super = Node;
public:
	OpNode() : super(NodeType::op) {}

public:
	enum OpEnum
		// 높은 값이 우선순위가 높도록 처리되기에, 연산 우선순위가 높은 걸 뒤에 배치하자
	{
		none,

		plus,
		minus,
			
		mul,
		div,
		res,
	};
	
public:
	virtual bool checkPriorIsValid(Node prior) override
	{
		switch (prior.nodeType)
		{
		case NodeType::num:
			return true;

		case NodeType::none:
		case NodeType::op:
		default:
			return false;
		}
	}

	void operate()
	{
		// TODO : OPERATE 후 자신의 Node* 자리에 자신을 삭제하고 NumNode* 로 Node* 에 할당해야 한다. 
	}

private:
	OpEnum opEnum;

};











int main()
{


	return 0;
}

#endif