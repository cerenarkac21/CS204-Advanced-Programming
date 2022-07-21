#include <iostream>
#include "DynamicQueue.h"

using namespace std;

/***************************************************************
In this .cpp file, for all of the functions below,             *
the lecture codes from week5 (DynIntQueue.cpp) were followed up.                 *
****************************************************************/

dynamicQueue::dynamicQueue()
{
	front = NULL;  
	rear = NULL;   
	// empty queue
}


void dynamicQueue::enqueue(studentNode stu)
{       
	if (isEmpty())   //if the queue is empty this will be the head
	{	
		front = new studentNode(stu);
		rear = front;
	}
	else  //if the queue is not empty add it after rear (to the end)
	{
		rear->next = new studentNode(stu);
		rear = rear->next;
	} 
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void dynamicQueue::dequeue(studentNode & dequeuedStu)
{
	studentNode * temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else 
	{	
		dequeuedStu = studentNode(front->name, front->id, front->funcName);  // copy the data in advance
		temp = front;
		front = front->next;
		temp->next = NULL;
		delete temp;      
	}
}

bool dynamicQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

// releive the allocated memory from heap
void dynamicQueue::clear()
{
	studentNode dequeuedStu;// Dummy variable for dequeue

	while(!isEmpty())
		dequeue(dequeuedStu); //delete all elements

}
