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

	if (calcFunc != nullptr)
	{
		retNode = calcFunc->calc(
			static_cast<NumNode*>(left), 
			static_cast<NumNode*>(right));
	}
	

	if (retNode == nullptr) return nullptr; // 실패시, return nullptr

	// LinkedList 연결 조정 후, left, right는 즉시 삭제. 
	// 본인 은 호출자가 retNode == nullptr 여부 확인 후 삭제
	retNode->left = left->left;
	retNode->right = right->right;

	left->left->right = retNode;
	right->right->left = retNode;

	TrackDelete(left);
	TrackDelete(right);
	
	return retNode;
}














/*---------------------------
		OpBinaryCalc
---------------------------*/
void OpBinaryCalc::checkFloatAndSet(NumNode* resultNode, FLOAT floatVal)
{
	if (floor(floatVal) == floatVal)
	{
		resultNode->isFloat = false;
		resultNode->intVal = static_cast<INT>(floatVal);
	}
	else
	{
		resultNode->isFloat = true;
		resultNode->floatVal = floatVal;
	}
}

Node* AddClac::calc(NumNode* left, NumNode* right)
{
	NumNode* resultNode = TrackNew<NumNode>();
	if (left->isFloat || right->isFloat)
	{
		FLOAT floatVal
			= (left->isFloat ? left->floatVal : left->intVal)
			+ (right->isFloat ? right->floatVal : right->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		resultNode->intVal = left->intVal + right->intVal;
	}

	return resultNode;
}

Node* SubClac::calc(NumNode* left, NumNode* right)
{
	NumNode* resultNode = TrackNew<NumNode>();
	if (left->isFloat || right->isFloat)
	{
		FLOAT floatVal
			= (left->isFloat ? left->floatVal : left->intVal)
			- (right->isFloat ? right->floatVal : right->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		resultNode->intVal = left->intVal - right->intVal;
	}

	return resultNode;
}

Node* MulClac::calc(NumNode* left, NumNode* right)
{
	NumNode* resultNode = TrackNew<NumNode>();
	if (left->isFloat || right->isFloat)
	{
		FLOAT floatVal
			= (left->isFloat ? left->floatVal : left->intVal)
			* (right->isFloat ? right->floatVal : right->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		resultNode->intVal = left->intVal * right->intVal;
	}

	return resultNode;
}

Node* DivClac::calc(NumNode* left, NumNode* right)
{

	NumNode* resultNode = TrackNew<NumNode>();
	if (left->isFloat || right->isFloat)
	{
		if (right->floatVal == 0.f) return  nullptr;

		FLOAT floatVal
			= (left->isFloat ? left->floatVal : left->intVal)
			/ (right->isFloat ? right->floatVal : right->intVal);

		checkFloatAndSet(resultNode, floatVal);
	}
	else
	{
		if (right->intVal == 0) return nullptr;

		resultNode->intVal = left->intVal / right->intVal;
	}

	return resultNode;
}

Node* ResClac::calc(NumNode* left, NumNode* right)
{
	NumNode* resultNode = TrackNew<NumNode>();
	if (left->isFloat || right->isFloat)
	{
		INT leftInt = left->isFloat ? static_cast<INT>(left->floatVal) : left->intVal;
		INT rightInt = right->isFloat ? static_cast<INT>(right->floatVal) : right->intVal;

		resultNode->isFloat = false;
		resultNode->intVal = leftInt % rightInt;
	}
	else
	{
		resultNode->intVal = left->intVal % right->intVal;
	}


	return resultNode;
}

Node* QuotClac::calc(NumNode* left, NumNode* right)
{
	NumNode* resultNode = TrackNew<NumNode>();
	if (left->isFloat || right->isFloat)
	{
		FLOAT floatVal
			= (left->isFloat ? left->floatVal : left->intVal)
			/ (right->isFloat ? right->floatVal : right->intVal);

		resultNode->isFloat = false;
		resultNode->intVal = static_cast<INT>(floatVal);
	}
	else
	{
		resultNode->intVal = left->intVal / right->intVal;
	}

	return resultNode;
}
