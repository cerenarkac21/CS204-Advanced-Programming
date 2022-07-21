#ifndef INTQUEUE_H
#define INTQUEUE_H

#include <string>
#include <vector>
using namespace std;

/***************************************************************
In this .h file, the lecture codes from week5 (IntQueue.h) were followed up.*
****************************************************************/
struct instructorNode
{
	string name;
	int id;
	string funcName;

	instructorNode::instructorNode(string name_ = "", int id_ = 0, string funcName_ = "")
		: name(name_), id(id_), funcName(funcName_){}
};

class IntQueue
{
private:
	vector <instructorNode> instructors;
	int queueSize; // 5 for this hw
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	IntQueue();
	void enqueue(instructorNode instructor); 
  	void dequeue(instructorNode & dequeuedInst);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif
