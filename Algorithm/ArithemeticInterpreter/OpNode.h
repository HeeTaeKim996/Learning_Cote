#pragma once
#include "Node.h"

enum class OpPriority : int // 내림차순으로 우선순위를 둔다
{

	// 산술 연산자
	mul = 30,
	div,
	res,
	quot,

	plus,
	minus,

	// 추후 시프트 연산자?


	// 추후 비트 연산자?
	
};



enum OpType
{
	binary,
	unary
};

class OpNode : public Node
{
	using super = Node;
public:
	OpNode(OpType inOpType, OpPriority InPriority) 
		: super(NodeType::op), opType(inOpType), 
		priority(InPriority)
	{}

public:
	virtual bool checkPriorIsValid(Node* prior) = 0; // 하위에서 처리
	virtual void speakWhoYouAre() = 0; // 하위에서 처리
	virtual Node* operate() = 0;

public:
	OpPriority getPrority() { return priority; }

private:
	OpType opType;
	OpPriority priority;

public:
	int debugLevel = -1;
};

