#pragma once

#include <vector>
#include <map>
#include "Node.h"
#include "RootNode.h"

class OpNode;

class NumContainer
{
public:
	void reset()
	{
		on = false;
		val = "";
		isFloat = false;
	}

public :
	bool on = false;
	string val = "";
	bool isFloat = false;
};

class Parser
{
private:
	Parser() {}
public:
	inline static Parser* instance()
	{
		static Parser* _instance = new Parser();
		return _instance;
	}



public:
	bool parse(string query);

private:
	void reset();

private:
	void test1();

private:
	bool makeNodes(string query);
	void insertNode(Node* newNode);
	bool addressNum(char c);
	bool addressOpBinary(char c);
	void TryMakeNumNode();
	bool addressParentheses(char c);

private:
	bool calculate();
	void onFailed();
	

public:
	RootNode* rootNode = new RootNode();
	Node* currNode;
	vector<map<int, vector<OpNode*>>> operations;
	int level = 0;
	NumContainer numContainer;
};

