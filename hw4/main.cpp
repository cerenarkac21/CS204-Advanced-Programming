// Ceren Arkac
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include "DynamicQueue.h"
#include "IntQueue.h"
#include "DynIntStack.h"

using namespace std;

struct Command
{
	string commandString;
	Command * nextCom;

	// constructor
	Command::Command(string commandString_, Command * next_ = NULL)
		: commandString(commandString_), nextCom(next_){}
};

struct Function
{
	string funcName;
	Command * commands;
	Function * next;


	// constructor
	Function::Function(string funcName_, Command * commands_ = NULL, Function * next_ = NULL)
		: funcName(funcName_), commands(commands_), next(next_){}

};

/***********************************************************
this function checks the last ":"s and ";". 
And assign these to function name and commands, respectively. 
According to this data, forms the linked list.
************************************************************/

Function * readFile(ifstream & in, string filename, Function * head){
	Function * temp = head;
	Command * temp2 = NULL;
	string line;
	string funcName;
	int lastDoublePoint;
	getline(in, line);
	lastDoublePoint = line.rfind(":");
	funcName = line.substr(0, lastDoublePoint);
	if (temp == NULL)
	{
		head = new Function(funcName);
		temp = head;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new Function(funcName);
		temp = temp->next;
	}
	while (getline(in, line))
	{
		if (line != "\r" && line != "") // checks the empty lines
		{
			string command;
			lastDoublePoint = line.rfind(";");
			command = line.substr(0, lastDoublePoint);
			if (temp->commands == NULL)
			{
				temp->commands = new Command(command);
				temp2 = temp->commands;
			}
			else
			{
				temp2->nextCom = new Command(command);
				temp2 = temp2->nextCom;
			}
		}
	}
	return head;
}

void PrintLinkedList(Function * head){
	Function * ptr = head;
	Command * ptrForCommands = NULL;
	while (ptr != NULL)
	{
		ptrForCommands = ptr->commands;
		cout << ptr->funcName << ":" << endl;
		while (ptrForCommands != NULL)
		{
			if (ptrForCommands->nextCom == NULL)
			{
				cout << ptrForCommands->commandString << "." << endl;
			}
			else
			{
				cout << ptrForCommands->commandString << ", ";
			}
			ptrForCommands = ptrForCommands->nextCom;
		}
		ptr = ptr->next;
		cout << endl;
	}
}

/********************************************************
This function allocated the memory used for LL from heap 
*********************************************************/

void deleteList(Function * head){
	Function * temp = head;
	Command * temp2 = NULL;
	while (head != NULL)
	{
		temp = head->next;
		Command * ptrForCommands = head->commands;
		temp2 = ptrForCommands;
		while (ptrForCommands != NULL)
		{
			temp2 = ptrForCommands->nextCom;
			delete ptrForCommands;
			ptrForCommands = temp2;
		}
		delete head;
		head = temp;
	}
}

// this function traverse the linked list and 
//if it finds service as the name of the Function node, returns true.
bool serviceExistenceCheck(string service, Function * head){
	Function * temp = head;
	while (temp != NULL)
	{
		if (temp->funcName == service)
		{
			return true;
		}
		else
		{
			temp = temp->next;
		}
	}
	return false;
}

void addInstructorRequest(Function * head, IntQueue & instructorsQueue){
	if (!instructorsQueue.isFull()){  // first, check if the instructors queue is full
		string service;
		cout << "Add a service <function> that the instructor wants to use: " << endl;
		cin >> service;
		if (serviceExistenceCheck(service, head))
		{
			string name;
			int idNum;
			cout << "Give instructor's name: " << endl;
			cin >> name;
			cout << "Give instructor's ID <an int>: " << endl;
			cin >> idNum;
			instructorsQueue.enqueue(instructorNode(name, idNum, service));
			cout << "Prof " << name << "'s service request of " << service << " has been put in the instuctor's queue. " << endl;
			cout << "Waiting to be served..." << endl;
		}
		else
		{
			cout << "The requested service does not exist." << endl;
			cout << "GOING BACK TO MAIN MENU" << endl;
		}
	}
	else
	{
		cout << "The instructors queue is full." << endl;
	}
}

void addStudentRequest(Function * head, dynamicQueue & studentsQueue){
	string service;
	cout << "Add a service <function> that the student wants to use: " << endl;
	cin >> service;
	if (serviceExistenceCheck(service, head))
	{
		string name;
		int idNum;
		cout << "Give student's name: " << endl;
		cin >> name;
		cout << "Give student's ID <an int>: " << endl;
		cin >> idNum;
		cout << name << "'s service request of " << service << " has been put in the student's queue. " << endl;
		studentsQueue.enqueue(studentNode(name, idNum, service));
		cout << "Waiting to be served..." << endl;
	}
	else
	{
		cout << "The requested service does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU: " << endl;
	}
}

void processARequest(string functionName, Function * head, DynIntStack & commonStack)
{
	Function * temp = head;
	Command * ptrToCommandsOfFuncName = NULL;
	while (temp != NULL) // finds the corresponding functionName and its commands
	{
		if (temp->funcName == functionName)
		{
			ptrToCommandsOfFuncName = temp->commands;
		}
		temp = temp->next;
	}
	while (ptrToCommandsOfFuncName != NULL) // traverse all the commands
	{
		istringstream ss(ptrToCommandsOfFuncName->commandString);
		string commandPart1, commandPart2;
		ss >> commandPart1 >> commandPart2;
		if(commandPart1 =="define")
		{
			commonStack.push(commandPart2, functionName);
		}
		else if (commandPart1 =="call")
		{
			cout << "Calling function " << commandPart2 << " from " << functionName << endl;
			processARequest(commandPart2, head, commonStack);
		}
		else{
			cout << "PRINTING THE STACK TRACE: " << endl;
			if (commonStack.isEmpty())
			{
				cout << "The stack is empty" << endl;
			}
			else
			{
				string tempVariableName; // print the content of the stack as WE SAW IN MIDTERM ANSWER KEY
				string tempFunctionName;
				DynIntStack tempStack;
				while (!commonStack.isEmpty())
				{
					commonStack.pop(tempVariableName, tempFunctionName); 
					tempStack.push(tempVariableName, tempFunctionName); 
				}
				while(!tempStack.isEmpty())
				{
					tempStack.pop(tempVariableName, tempFunctionName);
					cout << tempFunctionName << ": " << "define " << tempVariableName << endl; 
					commonStack.push(tempVariableName, tempFunctionName);
				}
			}
		}
		ptrToCommandsOfFuncName = ptrToCommandsOfFuncName->nextCom;
	}
	cout << functionName << " is finished. Clearing the stack from it's data... " <<endl;
	system("pause");
	// delete this function’s data from the top of the stack
	while (commonStack.getTopFuncName() == functionName)  
	{
		string dummy1 = "";
		string dummy2 = "";
		commonStack.pop(dummy1, dummy2);
	}
	if (commonStack.isEmpty())
	{
		cout << "The stack is empty" << endl;
	} 
}
void processARequest(IntQueue & instructorsQueue, dynamicQueue & studentsQueue, Function * head, DynIntStack & commonStack)
{
	if (!instructorsQueue.isEmpty())
	{
		instructorNode currentInst;
		instructorsQueue.dequeue(currentInst); // takes the requested which will be processed
		processARequest(currentInst.funcName, head, commonStack);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studentsQueue.isEmpty())
	{
		cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		studentNode currentStu; 
		studentsQueue.dequeue(currentStu);
		cout << "Processing " << currentStu.name << "'s request " << "<with ID " << currentStu.id << "> " << "of service " << "<function> " << currentStu.funcName << ": " << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		processARequest(currentStu.funcName, head, commonStack);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else
	{
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl;
		cout <<"GOING BACK TO MAIN MENU"<<endl;
	}
}

int main(){
	bool atBeginQuit = true; // checks whether y/Y or another key pressed as the first input
	string yOry;
	cout << "If you want to open a service <function> defining file, then press <Y/y> for 'yes', otherwise press any single key" << endl;
	cin >> yOry;
	Function * head = NULL;
	bool fileFail = false;
	while ((yOry == "y" || yOry =="Y") && fileFail == false) // take filenames until y/Y
	{
		atBeginQuit = false;
		string filenameX;
		cout << "Enter the input file name: ";
		cin >> filenameX;
		ifstream in;
		in.open(filenameX.c_str());
		if (!in.fail())
		{
			head = readFile(in, filenameX, head);  // process each file and update the linked list 
			cout << "Do you want to open another service defining file?" << endl; 
			cout << "Press <Y/y> for 'yes', otherwise press anykey" << endl;
			cin >> yOry;
		}
		else
		{
			cout << "Couldn't open file!" << endl;
			fileFail = true;
		}
	}
	if (fileFail == false && atBeginQuit == false)
	{
		cout << "-------------------------------------------------------------------" << endl;
		cout << "PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS" << endl;
		cout << "-------------------------------------------------------------------" << endl;

		PrintLinkedList(head);

		IntQueue instructorsQueue;
		dynamicQueue studentsQueue;
		DynIntStack commonStack;

		while (true)
		{
			cout << endl;
			cout<<"**********************************************************************"<<endl
				<<"**************** 0 - EXIT PROGRAM *************"<<endl
				<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
				<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
				<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
				<<"**********************************************************************"<<endl;
			cout << endl;
			int option;
			cout << "Pick an option from above (int number from 0 to 3): ";
			cin>>option;
			switch (option)
			{
			case 0:
				cout<<"PROGRAM EXITING ... "<<endl;
				system("pause");
				studentsQueue.clear();
				deleteList(head);
				head = NULL;

				exit(0);
			case 1:
				addInstructorRequest(head, instructorsQueue);
				break;
			case 2:
				addStudentRequest(head, studentsQueue);
				break;
			case 3:
				processARequest(instructorsQueue, studentsQueue, head, commonStack);
				break;
			default:
				cout<<"INVALID OPTION!!! Try again"<<endl;
			}
		}
	}
	else
	{
		cout<<"PROGRAM EXITING ... " << endl;
	}
	return 0;
}
