#pragma once
#include "Node.h"

class NumNode : public Node
{
	using super = Node;
public:
	NumNode() : super(NodeType::num)
	{}
	NumNode(INT InIntVal) : super(NodeType::num) 
	{
		intVal = InIntVal;
	}
	NumNode(FLOAT inFloatVAl) : super(NodeType::num)
	{
		isFloat = true;
		floatVal = inFloatVAl;
	}


public:
	inline virtual bool checkPriorIsValid(Node* prior) override
	{
		switch (prior->nodeType)
		{
		case NodeType::root:
		case NodeType::op:
			return true;

		case NodeType::none:
		case NodeType::num:
		default:
			return false;
		}
	}

	virtual void speakWhoYouAre() override;

public:
	bool isFloat = false;
	union
	{
		INT intVal;
		FLOAT floatVal;
	};

};

