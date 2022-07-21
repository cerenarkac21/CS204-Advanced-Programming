#include <iostream>
#include "IntQueue.h"
using namespace std;

/***************************************************************
In this .cpp file, for all of the functions below,             *
the lecture codes from week5 (IntQueue.cpp) were followed up.                 *
****************************************************************/

IntQueue::IntQueue() // constructor
{
	for (int i = 0; i < 5; i++) // initiliaze the vector with default constructor values
	{
		instructorNode instNode;
		instructors.push_back(instNode);
	}
	front = -1;
	rear = -1;
	numItems = 0;
	queueSize = instructors.size();
}

// this function takes an instructorNode object and put it to the end (rear)
void IntQueue::enqueue(instructorNode instructor)
{
	if (isFull())
    { 
		cout << "The queue is full. " << endl;
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.

		instructors[rear] = instructor;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void IntQueue::dequeue(instructorNode & dequeuedInst)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		dequeuedInst = instructors[front];
		// Retrieve the front item.
		// Update item count.
		numItems--;
	}
}

bool IntQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

bool IntQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void IntQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;

}
