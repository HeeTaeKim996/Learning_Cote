#include "pch.h"
#include "OpBinaryNode.h"
#include "NumNode.h"
#include <cmath>

void OpBinaryNode::speakWhoYouAre()
{
	char c = '\0';

	switch (opBinaryType)
	{
	case OpBinaryType::plus:
		c = '+';
		break;
	case OpBinaryType::minus:
		c = '-';
		break;
	case OpBinaryType::mul:
		c = '*';
		break;
	case OpBinaryType::divv:
		c = '/';
		break;
	case OpBinaryType::res:
		c = '%';
		break;
	case OpBinaryType::quot:
		c = 'q';
		break;
	default:
		break;
	}

	printf("OpBinary : type(%c), priority(%d), debugLevel(%d)\n", c, 
		static_cast<int>(getPrority()), debugLevel);
}

Node* OpBinaryNode::operate()
{
	if (left == nullptr || right == nullptr
		|| left->nodeType != NodeType::num
		|| right->nodeType != NodeType::num) return nullptr;

	Node* retNode = nullptr;

	switch (opBinaryType)
	{
	case OpBinaryType::plus:
		retNode = calcPlus();
		break;
	case OpBinaryType::minus:
		retNode = calcMinus();
		break;
	case OpBinaryType::mul:
		retNode = calcMul();
		break;
	case OpBinaryType::divv:
		retNode = calcDiv();
		break;
	case OpBinaryType::res:
		retNode = calcRes();
		break;
	case OpBinaryType::quot:
		retNode = calcQuot();

	}

	if (retNode == nullptr) return nullptr; // 실패시, return nullptr

	// LinkedList 연결 조정 후, left, right는 즉시 삭제. 
	// 본인 은 호출자가 retNode == nullptr 여부 확인 후 삭제
	retNode->left = left->left;
	retNode->right = right->right;

	left->left->right = retNode;
	right->right->left = retNode;

	delete(left);
	delete(right);
	
	return retNode;
}

Node* OpBinaryNode::calcPlus()
{
	NumNode* leftNum = static_cast<NumNode*>(left);
	NumNode* rightNum = static_cast<NumNode*>(right);

	NumNode* resultNode = new NumNode();
	if (leftNum->isFloat || rightNum->isFloat)
	{
		float floatVal
			= (leftNum->isFloat ?  leftNum->floatVal : leftNum->intVal)
			+ (rightNum->isFloat ?  rightNum->floatVal : rightNum->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		resultNode->intVal = leftNum->intVal + rightNum->intVal;
	}

	return resultNode;
}

Node* OpBinaryNode::calcMinus()
{
	NumNode* leftNum = static_cast<NumNode*>(left);
	NumNode* rightNum = static_cast<NumNode*>(right);
	
	NumNode* resultNode = new NumNode();
	if (leftNum->isFloat || rightNum->isFloat)
	{
		float floatVal
			= (leftNum->isFloat ? leftNum->floatVal : leftNum->intVal)
			- (rightNum->isFloat ? rightNum->floatVal : rightNum->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		resultNode->intVal = leftNum->intVal - rightNum->intVal;
	}

	return resultNode;
}

Node* OpBinaryNode::calcMul()
{
	NumNode* leftNum = static_cast<NumNode*>(left);
	NumNode* rightNum = static_cast<NumNode*>(right);

	NumNode* resultNode = new NumNode();
	if (leftNum->isFloat || rightNum->isFloat)
	{
		float floatVal
			= (leftNum->isFloat ? leftNum->floatVal : leftNum->intVal)
			* (rightNum->isFloat ? rightNum->floatVal : rightNum->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		resultNode->intVal = leftNum->intVal * rightNum->intVal;
	}

	return resultNode;
}

Node* OpBinaryNode::calcDiv()
{
	NumNode* leftNum = static_cast<NumNode*>(left);
	NumNode* rightNum = static_cast<NumNode*>(right);

	NumNode* resultNode = new NumNode();
	if (leftNum->isFloat || rightNum->isFloat)
	{
		if (rightNum->floatVal == 0.f) return  nullptr;

		float floatVal
			= (leftNum->isFloat ? leftNum->floatVal : leftNum->intVal)
			/ (rightNum->isFloat ? rightNum->floatVal : rightNum->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		if (rightNum->intVal == 0) return nullptr;

		resultNode->intVal = leftNum->intVal / rightNum->intVal;
	}

	return resultNode;
}

Node* OpBinaryNode::calcRes()
{
	NumNode* leftNum = static_cast<NumNode*>(left);
	NumNode* rightNum = static_cast<NumNode*>(right);

	NumNode* resultNode = new NumNode();
	if (leftNum->isFloat || rightNum->isFloat)
	{
		int leftInt = leftNum->isFloat ? static_cast<int>(leftNum->floatVal) : leftNum->intVal;
		int rightInt = rightNum->isFloat ? static_cast<int>(rightNum->floatVal) : rightNum->intVal;

		resultNode->isFloat = false;
		resultNode->intVal = leftInt % rightInt;
	}
	else
	{
		resultNode->intVal = leftNum->intVal % rightNum->intVal;
	}


	return resultNode;
}

Node* OpBinaryNode::calcQuot()
{
	NumNode* leftNum = static_cast<NumNode*>(left);
	NumNode* rightNum = static_cast<NumNode*>(right);

	NumNode* resultNode = new NumNode();
	if (leftNum->isFloat || rightNum->isFloat)
	{
		float floatVal
			= (leftNum->isFloat ? leftNum->floatVal : leftNum->intVal)
			/ (rightNum->isFloat ? rightNum->floatVal : rightNum->intVal);

		resultNode->isFloat = false;
		resultNode->intVal = static_cast<int>(floatVal);
	}
	else
	{
		resultNode->intVal = leftNum->intVal / rightNum->intVal;
	}

	return resultNode;
}

void OpBinaryNode::checkFloatAndSet(NumNode* resultNode, float floatVal)
{
	if (floor(floatVal) == floatVal)
	{
		resultNode->isFloat = false;
		resultNode->intVal = static_cast<int>(floatVal);
	}
	else
	{
		resultNode->isFloat = true;
		resultNode->floatVal = floatVal;
	}
}
