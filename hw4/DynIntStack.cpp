#include <iostream>
#include <string>
#include "DynIntStack.h"
using namespace std;

/***************************************************************
In this .cpp file, for all of the functions below,             *
the lecture codes from week5 (DynIntStack.cpp) were followed up.                 
****************************************************************/

DynIntStack::DynIntStack()  // constructor generated an empty stack (linked list)
{
	top = NULL; 
}
// put node from top
void DynIntStack::push(string variable, string funcName)
{
	StackNode *newNode = NULL;
	newNode = new StackNode(variable, funcName);

	if (isEmpty()) // if the stack is empty, make next of this node to point NULL.
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top and link to the rest.
	{
		newNode->next = top;
		top = newNode;
	}
}

// pop from top
void DynIntStack::pop(string & variable, string & funcName)
{
	StackNode *temp = NULL;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else
	{
		variable = top->variableName;  // take the data before deletion
		funcName = top->funcName;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

// This function accesesed the  funcName field of the node which top is pointing to.
string DynIntStack::getTopFuncName()

{
	if (!isEmpty())
	{
		return top->funcName;
	}
	else
	{
		string message = "The stack is empty";
		return message;
	}
}

// this function was created to be used at the end of the main to relieve the allocated memory from heap.
void DynIntStack::clear()
{
	string dummy1, dummy2;// Dummy variable for dequeue

	while(!isEmpty())
		pop(dummy1, dummy2); //delete all elements
}
