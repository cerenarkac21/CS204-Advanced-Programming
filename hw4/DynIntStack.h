#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H

/*******************************************************************************
In this .h file, the lecture codes from week5 (DynIntStack.h) were followed up.*
********************************************************************************/

#include <string>
using namespace std;

struct StackNode
{
	string variableName;
	string funcName;
	StackNode * next;

	StackNode::StackNode(string variableName_ = "", string funcName_ = "", StackNode * next_ = NULL)
		: variableName(variableName_), funcName(funcName_), next(next_){}
};

class DynIntStack
{
private:
	StackNode * top;

public:
	DynIntStack();
	void push(string variable, string funcName);
	void pop(string & variable, string & funcName);
	bool isEmpty(void);
	string getTopFuncName();
	void clear();
};

#endif
