#pragma once
#include "Node.h"

class RootNode : public Node
{
public:
	RootNode() : Node(NodeType::root)
	{

	}

public:
	virtual bool checkPriorIsValid(Node* prior) override { return false; }
	virtual void speakWhoYouAre() { printf("Im Root\n"); }
};

