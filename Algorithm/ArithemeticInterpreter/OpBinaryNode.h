#pragma once
#include "OpNode.h"

class NumNode;

enum class OpBinaryType
{
	plus,
	minus,
	
	mul,
	divv,
	res,
	quot
};

class OpBinaryNode : public OpNode
{
	using super = OpNode;
private:
	static OpPriority getPriorityFromBinaryType(OpBinaryType bType)
	{
		switch (bType)
		{
		case OpBinaryType::plus:
			return OpPriority::plus;
		case OpBinaryType::minus:
			return OpPriority::minus;
		case OpBinaryType::mul:
			return OpPriority::mul;
		case OpBinaryType::divv:
			return OpPriority::div;
		case OpBinaryType::res:
			return OpPriority::res;
		case OpBinaryType::quot:
			return OpPriority::quot;
		default:
			return OpPriority::plus;
		}
	}

public:
	OpBinaryNode(OpBinaryType inType) 
		:super(OpType::binary, getPriorityFromBinaryType(inType))
	{
		
		opBinaryType = inType;
	}

public:
	inline virtual bool checkPriorIsValid(Node* prior) override
	{
		switch (prior->nodeType)
		{
		case NodeType::num:
			return true;

		case NodeType::none:
		case NodeType::op:
		default:
			return false;
		}
	}
	virtual void speakWhoYouAre() override;

	virtual Node* operate() override;

private:
	Node* calcPlus();
	Node* calcMinus();
	Node* calcMul();
	Node* calcDiv();
	Node* calcRes();
	Node* calcQuot();

private:
	void checkFloatAndSet(NumNode* resultNode, float floatVal);


public:
	OpBinaryType opBinaryType;

};

