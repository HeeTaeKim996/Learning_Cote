#pragma once

enum NodeType
{
	none,
	root,
	num,
	op
};
class Node
{


public:
	Node(NodeType inNodeType)
	{
		nodeType = inNodeType;
	}

public:
	virtual bool checkPriorIsValid(Node* prior) = 0;
	virtual void speakWhoYouAre() = 0;


public:
	Node* left;
	Node* right;
	NodeType nodeType;

};

