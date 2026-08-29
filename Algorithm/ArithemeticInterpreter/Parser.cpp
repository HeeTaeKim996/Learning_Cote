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
		clearNodes();
		return false;
	}

#ifdef DEBUG_SPEAK
	printf("\n\n\nBefore calculated : \n");
	test1();
#endif

	if (calculate() == false)
	{
		clearNodes();
		return false;
	}

#ifdef DEBUG_SPEAK
	printf("\nAfter calculated : \n");
	test1();
#endif
	

	// 이전에 결과를 String 등으로 준비 필요
	clearNodes();

#ifdef DEBUG_SPEAK
	MemoryTracker::printState();
#endif

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

	if (TryMakeNumNode() == false) return false;

	return true;
}

bool Parser::insertNode(Node* newNode)
{
	// 여기서 인접 노드끼리 유효 검수
	if (newNode->checkPriorIsValid(currNode) == false) return false;

	newNode->right = currNode->right;
	newNode->left = currNode;
	currNode->right = newNode;

	currNode = newNode;

	return true;
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
	if (TryMakeNumNode() == false) return false;

	OpBinaryNode* opNode = nullptr;

	switch (c)
	{
	case '+':
		opNode = TrackNew<OpBinaryNode>(OpBinaryType::plus, AddClac::instance());
		break;
	case '-':
		opNode = TrackNew<OpBinaryNode>(OpBinaryType::minus, SubClac::instance());
		break;
	case '*':
		opNode = TrackNew<OpBinaryNode>(OpBinaryType::mul, MulClac::instance());
		break;
	case '/':
		opNode = TrackNew<OpBinaryNode>(OpBinaryType::divv, DivClac::instance());
		break;
	case '%':
		opNode = TrackNew<OpBinaryNode>(OpBinaryType::res, ResClac::instance());
		break;
	case 'q':
		opNode = TrackNew<OpBinaryNode>(OpBinaryType::quot, QuotClac::instance());
		break;
	}

	if (opNode == nullptr) return false;

	if (insertNode(opNode) == false) return false;

	opNode->debugLevel = level; // 디버그 용도

	if (operations.size() <= static_cast<size_t>(level))
	{
		operations.resize(level + 1);
	}

	int priority = static_cast<int>(opNode->getPrority());
	operations[level][priority].push_back(opNode);

	return true;
}

bool Parser::TryMakeNumNode()
{
	if (numContainer.on == false) return true; // 정상 종료!

	NumNode* numNode;
	if (numContainer.isFloat)
	{
#ifdef AIM_64
		numNode = TrackNew<NumNode>(stod(numContainer.val));
#elif defined AIM_32
		numNode = TrackNew<NumNode>(stof(numContainer.val));
#endif

	}
	else
	{
#ifdef AIM_64
		numNode = TrackNew<NumNode>(stoll(numContainer.val));
#elif defined AIM_32
		numNode = TrackNew<NumNode>(stoi(numContainer.val));
#endif
	}

	if (insertNode(numNode) == false) return false; // 실패 종료

	numContainer.reset();

	return true; // 정상 종료
}

bool Parser::addressParentheses(char c)
{
	if (TryMakeNumNode() == false) return false;

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

				TrackDelete(opNode); 
				// 여기서 최종 삭제한다. 
				// linkedList 의 연결 처리는 operate 내부에서 이미 처리됨
				
			}
		}
	}

	return true;
}

void Parser::clearNodes()
{
	Node* currNode = rootNode->right;
	while (currNode != rootNode)
	{
		Node* dNode = currNode;
		currNode = currNode->right;
		TrackDelete(dNode);
	}
}


