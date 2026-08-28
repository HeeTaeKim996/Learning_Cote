#include "pch.h"
#include "Parser.h"
#include "NumNode.h"
#include "OpBinaryNode.h"
#include <typeinfo>

bool Parser::parse(string query)
{
	reset();

	if (makeNodes(query) == false)
	{
		onFailed();
		return false;
	}

	printf("\n\n\nBefore calculated : \n");
	test1();

	if (calculate() == false)
	{
		onFailed();
		return false;
	}

	printf("\nAfter calculated : \n");
	test1();

	return true;
}




void Parser::reset()
{
	currNode = rootNode;
	currNode->left = currNode;
	currNode->right = currNode;

	level = 0;
	operations.clear();
}

void Parser::test1()
{
	Node* curr = rootNode -> right;
	while (curr != rootNode)
	{
		curr->speakWhoYouAre();
		curr = curr->right;
	}
}

bool Parser::makeNodes(string query)
{
	for (char c : query)
	{
		if (c == ' ')
		{
			continue;
		}
		else if ((c >= '0' && c <= '9')
			|| c == '.')
		{
			if (addressNum(c) == false) return false;
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/'
			|| c == '%' || c == 'q')
		{
			if (addressOpBinary(c) == false) return false;
		}
		else if (c == '(' || c == ')')
		{
			if (addressParentheses(c) == false) return false;
		}
	}

	TryMakeNumNode();

	return true;
}

void Parser::insertNode(Node* newNode)
{
	newNode->right = currNode->right;
	newNode->left = currNode;
	currNode->right = newNode;

	currNode = newNode;
}

bool Parser::addressNum(char c)
{
	if (numContainer.on == false)
	{
		if (c == '.') return false;

		numContainer.on = true;
		numContainer.val = c;
	}
	else
	{
		if (c == '.' && numContainer.isFloat) return false;

		numContainer.isFloat = true;
		numContainer.val += c;
	}
	

	return true;
}





bool Parser::addressOpBinary(char c)
{
	TryMakeNumNode();

	OpBinaryNode* opNode = nullptr;

	switch (c)
	{
	case '+':
		opNode = new OpBinaryNode(OpBinaryType::plus);
		break;
	case '-':
		opNode = new OpBinaryNode(OpBinaryType::minus);
		break;
	case '*':
		opNode = new OpBinaryNode(OpBinaryType::mul);
		break;
	case '/':
		opNode = new OpBinaryNode(OpBinaryType::divv);
		break;
	case '%':
		opNode = new OpBinaryNode(OpBinaryType::res);
		break;
	case 'q':
		opNode = new OpBinaryNode(OpBinaryType::quot);
		break;
	}

	if (opNode == nullptr) return false;

	insertNode(opNode);

	opNode->debugLevel = level; // 디버그 용도

	if (operations.size() <= static_cast<size_t>(level))
	{
		operations.resize(level + 1);
	}

	int priority = static_cast<int>(opNode->getPrority());
	operations[level][priority].push_back(opNode);

	return true;
}

void Parser::TryMakeNumNode()
{
	if (numContainer.on == false) return;

	NumNode* numNode;
	if (numContainer.isFloat)
	{
#ifdef AIM_64
		numNode = new NumNode(stod(numContainer.val));
#elif defined AIM_32
		numNode = new NumNode(stof(numContainer.val));
#endif

	}
	else
	{
#ifdef AIM_64
		numNode = new NumNode(stoll(numContainer.val));
#elif defined AIM_32
		numNode = new NumNode(stoi(numContainer.val));
#endif
	}

	insertNode(numNode);

	numContainer.reset();
}

bool Parser::addressParentheses(char c)
{
	TryMakeNumNode();

	if (c == '(')
	{
		level++;
	}
	else
	{
		if (--level < 0) return false;
	}

	return true;
}






bool Parser::calculate()
{
	for (int i = operations.size() - 1; i >= 0; i--)
	{
		map<int, vector<OpNode*>>& levelOp = operations[i];
		
		for (auto& [priority, opNodes] : levelOp)
		{
			for (OpNode* opNode : opNodes)
			{
				if (opNode == nullptr) continue;

				Node* numNode = opNode->operate();
				if (numNode == nullptr) return false;

				delete(opNode); 
				// 여기서 최종 삭제한다. 
				// linkedList 의 연결 처리는 operate 내부에서 이미 처리됨
				
			}
		}
	}

	return true;
}

void Parser::onFailed()
{
	Node* currNode = rootNode->right;
	while (currNode != rootNode)
	{
		Node* dNode = currNode;
		currNode = currNode->right;
		delete(dNode);
	}
}


