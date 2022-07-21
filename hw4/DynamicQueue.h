#ifndef _DYNAMICQUEUE_H
#define _DYNAMICQUEUE_H
using namespace std;

/***************************************************************
In this .h file, for all of the functions below,               *
the lecture codes from week5 (DynIntQueue.h) were followed up. * 
****************************************************************/

struct studentNode
{
	string name;
	int id;
	string funcName;
	studentNode * next;

	studentNode::studentNode(string name_ = "", int id_ = 0, string funcName_ = "", studentNode * next_ = NULL)
		: name(name_), id(id_), funcName(funcName_), next(next_){};
};

class dynamicQueue
{

public:
	dynamicQueue(); // constructor definition
	void enqueue(studentNode stu);
	void dequeue(studentNode & dequeuedStu);
	bool isEmpty() const;     
	void clear();

private:
	studentNode *front;
	studentNode *rear;
};


#endif
