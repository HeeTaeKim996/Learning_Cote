#pragma once
#include "OpNode.h"

class NumNode;
class OpBinaryCalc;

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
	OpBinaryNode(OpBinaryType inType, OpBinaryCalc* inCalcFunc)
		:super(OpType::binary, getPriorityFromBinaryType(inType)),
		opBinaryType(inType), calcFunc(inCalcFunc)
	{}

public:
	inline virtual bool checkPriorIsValid(Node* prior) override
	{
		switch (prior->nodeType)
		{
		case NodeType::root:
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
	OpBinaryCalc* calcFunc;

public:
	OpBinaryType opBinaryType;
};














/*---------------------------
		OpBinaryCalc
---------------------------*/
class OpBinaryCalc
{
protected:
	static void checkFloatAndSet(NumNode* resultNode, FLOAT floatVal);

public:
	virtual Node* calc(NumNode* left, NumNode* right) = 0;
};

class AddClac : public OpBinaryCalc 
{
public:
	static AddClac* instance()
	{
		static AddClac* _instance = new AddClac();
		return _instance;
	}

public:
	virtual Node* calc(NumNode* left, NumNode* right) override;
};

class SubClac : public OpBinaryCalc
{
public:
	static SubClac* instance()
	{
		static SubClac* _instance = new SubClac();
		return _instance;
	}

public:
	virtual Node* calc(NumNode* left, NumNode* right) override;
};

class MulClac : public OpBinaryCalc
{
public:
	static MulClac* instance()
	{
		static MulClac* _instance = new MulClac();
		return _instance;
	}

public:
	virtual Node* calc(NumNode* left, NumNode* right) override;
};

class DivClac : public OpBinaryCalc
{
public:
	static DivClac* instance()
	{
		static DivClac* _instance = new DivClac();
		return _instance;
	}

public:
	virtual Node* calc(NumNode* left, NumNode* right) override;
};


class ResClac : public OpBinaryCalc
{
public:
	static ResClac* instance()
	{
		static ResClac* _instance = new ResClac();
		return _instance;
	}

public:
	virtual Node* calc(NumNode* left, NumNode* right) override;
};

class QuotClac : public OpBinaryCalc
{
public:
	static QuotClac* instance()
	{
		static QuotClac* _instance = new QuotClac();
		return _instance;
	}

public:
	virtual Node* calc(NumNode* left, NumNode* right) override;
};