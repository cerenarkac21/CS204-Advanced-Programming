#include <iostream>
#include "linkedlistutils.h"

using namespace std;

linkedlistutils::linkedlistutils() // constructor
{
	head = NULL;
}

bool linkedlistutils::ConsistencyCheck() {
	busLine * currBL = head;
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName
					<< " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}
bool linkedlistutils::nodeExistenceCheck(string busLineName){ // checks busLines and returns true if there is one with busLineName
	busLine * ptr = head;
	while (ptr != NULL)
	{
		if (ptr->busLineName == busLineName)
		{
			return true;
		}
		ptr = ptr->next;
	}
	return false;

}
bool linkedlistutils::stopExistenceCheck(string busLineName, string busStopName){ // checks the corresponding busLine and returns true if there is one with busStopName
	busLine * ptrForBusLines = head;
	busStop * ptrForBusStops = NULL;
	while (ptrForBusLines != NULL)
	{
		if (ptrForBusLines->busLineName == busLineName)
		{
			ptrForBusStops = ptrForBusLines->busStops;
			while (ptrForBusStops != NULL)
			{
				if (ptrForBusStops->busStopName == busStopName)
				{
					return true;
				}
				ptrForBusStops = ptrForBusStops->right;
			}
			return false;
		}
		ptrForBusLines = ptrForBusLines->next;
	}
}
void linkedlistutils::deleteBusLineWith0Stops(string busLineName){ // deletes empty busLine
	busLine * temp = head;
	head = head->next;
	delete temp;
}

void linkedlistutils::deleteBusStop2(string busLineName, string busStopName){ // call this function in deleteBusStop()
	busLine * ptr = head;
	bool done = false;
	while (done == false && ptr != NULL)
	{
		if (ptr->busLineName == busLineName)
		{
			busStop * ptrForBusStops = ptr->busStops; // think like the head of the bus Stops
			while (done == false && ptrForBusStops != NULL) ////
			{
				if (ptrForBusStops->busStopName == busStopName)
				{
					// found the stop which will be deleted
					if (busStopName == ptr->busStops->busStopName)  // if it is the first stop of that line
					{
						if (ptrForBusStops->right == NULL) // if it is the only stop of that busLine
						{
							delete ptrForBusStops;
							ptrForBusStops = NULL;
							ptr->busStops = NULL;
							deleteBusLine2(busLineName); // then remove the line with no stops
						}
						else
						{
							busStop * temp = ptrForBusStops;
							temp->right->left = NULL;
							ptr->busStops = temp->right;
							delete temp;
							temp = NULL;
						}
						done = true;
					}
					else if (ptrForBusStops->right != NULL && ptrForBusStops != ptr->busStops)// the stop which will be deleted is neither at the beginning nor at the end 
					{
						busStop * temp = ptrForBusStops;
						temp->right->left = temp->left;
						temp->left->right = temp->right;
						delete temp;
						temp = NULL;
						done = true;
					}
					else if(ptrForBusStops->right == NULL) // the stop which will be deleted is the last stop
					{
						busStop * temp = ptrForBusStops;
						temp->left->right = NULL;
						delete temp;
						temp = NULL;
						done = true;
					}
				}
				else
				{
					ptrForBusStops = ptrForBusStops->right; 
				}
			}
		}
		ptr = ptr->next;
	}
}

void linkedlistutils::deleteBusLine2(string busLineName){
	busLine * ptr = head;
	busLine * temp = NULL;
	busStop * head2 = NULL;
	busStop * temp2 = NULL;
	bool done = false;
	while (done == false && ptr != NULL)
	{
		if (head->busLineName == busLineName && ptr->busLineName == head->busLineName) // // delete from beginning
		{
			if (ptr->busStops == NULL) // if the busLine is an empty busLine
			{
				head = head->next;
				delete ptr;
			}
			else
			{
				head2 = head->busStops;
				while (head2 != NULL)  // delete stops
				{
					temp2 = head2->right;
					head2->left = NULL;
					delete head2;
					head2 = temp2;
				}
				temp = head;
				head = head->next;
				delete temp;
				temp = NULL;
			}
			done = true;
		}
		else if (ptr->next->next != NULL && ptr->next->busLineName == busLineName) // not a busLine at the beginning or end
		{
			if (ptr->next->busStops == NULL)
			{
				temp = ptr->next;
				ptr->next = ptr->next->next;
				delete temp;
			}
			else
			{
				temp = ptr->next;
				head2 = ptr->next->busStops;
				ptr->next = ptr->next->next;
				// deleting stops again
				while (head2 != NULL)
				{
					temp2 = head2->right;
					head2->left = NULL;
					delete head2;
					head2 = temp2;
				}
				temp->next = NULL;
				temp->busStops = NULL;
				delete temp;
				temp = NULL;
			}
			done = true;
		}
		else if (ptr->next->next == NULL && ptr->next->busLineName == busLineName) // busLine is at the end
		{
			temp = ptr->next;
			head2 = ptr->next->busStops;
			ptr->next = ptr->next->next;

			while (head2 != NULL)
			{
				temp2 = head2->right;
				head2->left = NULL;
				delete head2;
				head2 = temp2;
			}
			temp->busStops = NULL;
			delete temp;
			temp = NULL;
			done = true;
		}
		else
		{
			ptr = ptr->next;
		}
	}	

}

void linkedlistutils::addBusLine(){
	string newBusLineInput;
	string newBusStopInput;
	string yesOrNo;
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> newBusLineInput;
	bool existingStop = false;
	bool lineNotFinished = true;
	bool returnMenu = false;
	busLine * ptrR = head;
	busLine * ptrD = head;
	busStop * ptrForBusStops = NULL;
	if (newBusLineInput != "0")
	{
		while (returnMenu == false && nodeExistenceCheck(newBusLineInput))
		{
			cout << "Bus line already exists: enter a new one (0 for exit to main menu)" << endl;
			cin >> newBusLineInput;
			if (newBusLineInput == "0")
			{
				returnMenu = true;
			}

		}
		if (!returnMenu)
		{
			addBusLine2Beginning(newBusLineInput, ptrR, ptrD);
			cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
			cin >> newBusStopInput;
			while (newBusStopInput != "0")
			{
				existingStop = stopExistenceCheck(newBusLineInput, newBusStopInput);
				if (existingStop) 
				{
					cout << "Bus stop already exists in the line" << endl;
				}
				else
				{
					addBusStop2(newBusStopInput, ptrR, ptrD, ptrForBusStops);
				}
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> newBusStopInput;

			}
			if (newBusStopInput == "0" && ptrR->busStops == NULL)  
			{
				cout << "You are not allowed to add an empty bus line" << endl;
				deleteBusLineWith0Stops(newBusLineInput);
			}
			else
			{
				cout << "The bus line information is shown below" << endl;
				PrintBusLine(newBusLineInput);
				cout << endl;
				cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
				cin >> yesOrNo;
				if (yesOrNo == "n" || yesOrNo == "N")
				{
					deleteBusLine2(newBusLineInput);
					PrintBusLines();
				}
				else if (yesOrNo == "y" || yesOrNo == "Y")
				{
					PrintBusLines();
				}
			}
		}
	}
}
// some of the functions are created by using reference to pointer, 
// these are the first functions I created, so, also same logic when I used in txt
// this function was created to be used in addBusLine()
void linkedlistutils::addBusStop2(string busStopName, busLine *& ptrR, busLine *& ptrD, busStop *& ptrForBusStops){
	if (ptrR->busStops == NULL)
	{
		ptrR->busStops = new busStop(busStopName);
		ptrForBusStops = ptrR->busStops;
	}
	else
	{
		ptrForBusStops->right = new busStop(busStopName);
		ptrForBusStops->right->left = ptrForBusStops;
		ptrForBusStops = ptrForBusStops->right;
	}

}

// this function is created to be used in just addBusLine()
void linkedlistutils::addBusLine2Beginning(string busLineName, busLine *& ptrR, busLine *& ptrD){
	busLine * ptr = new busLine(busLineName, head, NULL);
	head = ptr;
	ptrD = head;
	ptrR = head;
}

void linkedlistutils::PrintBusLine(string busLineName){
	busStop * ptrForBusStops = NULL;
	busLine * ptr = head;
	while ( ptr != NULL)
	{
		if (ptr->busLineName == busLineName)
		{
			ptrForBusStops = ptr->busStops;
			cout << ptr->busLineName << ": ";
			do
			{
				if (ptrForBusStops->right == NULL)
				{
					cout << ptrForBusStops->busStopName;
				}
				else
				{
					cout << ptrForBusStops->busStopName << " <-> ";
				}
				ptrForBusStops = ptrForBusStops->right;
			} while (ptrForBusStops != NULL);
		}
		ptr = ptr->next;
	}

}
// this function does the biggest chunk of the job
void linkedlistutils::addBusStop3(string newBusLineInput, string newBusStopName, string previousBusStopName){
	busLine * ptr = head;
	busStop * ptrForBusStops = NULL;
	bool done = false;
	while (ptr != NULL && done == false)
	{
		if (ptr->busLineName == newBusLineInput)
		{
			ptrForBusStops = ptr->busStops;
			while (done == false && ptrForBusStops != NULL)
			{
				if (ptrForBusStops->right != NULL && ptrForBusStops->busStopName == previousBusStopName)
				{
					busStop * temp = new busStop(newBusStopName);
					temp->right = ptrForBusStops->right;
					temp->left = ptrForBusStops;
					ptrForBusStops->right = temp;
					temp->right->left = temp;
					done = true;
					/*
					my mistake: (so it is just a reminder for me to do not this mistake again)
					new busStop(newBusStopName, ptrForBusStops, ptrForBusStops->right)
					ptrForBusStops->right = new busStop(newBusStopName, ptrForBusStops, ptrForBusStops->right);
					*/
				}
				else if (ptrForBusStops->right == NULL && ptrForBusStops->busStopName == previousBusStopName)
				{
					busStop * temp = new busStop(newBusStopName);
					temp->right = NULL;
					temp->left = ptrForBusStops;
					ptrForBusStops->right = temp;
					done = true;
				}
				ptrForBusStops = ptrForBusStops->right; 
			}

		}
		if (done == false)
		{
			ptr = ptr->next;
		}
	}

}
void linkedlistutils::addBusStop2Beginning(string newBusLineInput, string busStopName){
	busLine * ptr = head;
	while (ptr != NULL)
	{
		if (ptr->busLineName == newBusLineInput) 
		{
			ptr->busStops = new busStop(busStopName, NULL, ptr->busStops); // connect new stop with line
			ptr->busStops->right->left = ptr->busStops;
		}
		ptr = ptr->next;
	}

}

void linkedlistutils::addBusStop(){
	bool alreadyExistBusStop = false;
	bool returnMenu = false;
	string newBusLineInput;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> newBusLineInput;
	if (newBusLineInput != "0" && alreadyExistBusStop == false)
	{
		if (!nodeExistenceCheck(newBusLineInput))
		{
			cout << "Bus line cannot be found. Going back to previous menu." << endl;
		}
		else
		{
			cout << "The bus line information is shown below" << endl;
			PrintBusLine(newBusLineInput);
			cout << endl;
			string newBusStopName;
			cout << "Enter the name of the new bus stop" << endl;
			cin >> newBusStopName;
			if (stopExistenceCheck(newBusLineInput, newBusStopName)){

				cout << "Bus stop already exists. Going back to previous menu." << endl;
				alreadyExistBusStop = true;
			}
			else
			{
				string previousBusStopName;
				cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
				cin >> previousBusStopName;
				if (previousBusStopName == "0")
				{
					addBusStop2Beginning(newBusLineInput, newBusStopName);
					PrintBusLines();
				}
				else
				{
					if (stopExistenceCheck(newBusLineInput, previousBusStopName) == false)
					{
						while (returnMenu == false && stopExistenceCheck(newBusLineInput, previousBusStopName) != true)
						{
							cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
							cin >> previousBusStopName;
							if (previousBusStopName == "0")
							{
								returnMenu = true;
							}
						}
						if (!returnMenu)
						{
							addBusStop3(newBusLineInput, newBusStopName, previousBusStopName);
							PrintBusLines();
						}
					}
					else
					{
						addBusStop3(newBusLineInput, newBusStopName, previousBusStopName);
						PrintBusLines();
					}
				}
			}
		}
	}
}

void linkedlistutils::deleteBusLine(){
	string busLineName;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> busLineName;
	if (!nodeExistenceCheck(busLineName))
	{
		cout << "Bus line cannot be found. Going back to the previous (main) men" << endl;
	}
	else
	{
		deleteBusLine2(busLineName);
		PrintBusLines();
	}

}
void linkedlistutils::deleteBusStop(){
	string busLineName;
	bool returnMenu = false;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	cin >> busLineName;
	if (busLineName != "0" && (!nodeExistenceCheck(busLineName)))
	{
		cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
	}
	else if (busLineName != "0" && nodeExistenceCheck(busLineName))
	{
		cout << "The bus line information is shown below" << endl;
		PrintBusLine(busLineName);
		cout << endl;
		string busStopName;
		cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> busStopName;
		if (busStopName != "0")
		{
			if (!stopExistenceCheck(busLineName, busStopName))
			{
				while (returnMenu == false && !stopExistenceCheck(busLineName, busStopName))
				{
					cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
					cin >> busStopName;
					if (busStopName == "0")
					{
						returnMenu = true;
					}
				}
				if (!returnMenu)
				{
					deleteBusStop2(busLineName, busStopName);
					PrintBusLines();
				}
			}
			else
			{
				deleteBusStop2(busLineName, busStopName);
				PrintBusLines();
			}
		}
	}
}

bool linkedlistutils::existingStops(string busStopName){ // check whole stops
	busLine * ptr = head;
	busStop * ptrForBusStops = NULL;
	bool done = false;
	while (ptr != NULL)
	{
		ptrForBusStops = ptr->busStops;
		while (ptrForBusStops != NULL)
		{
			if (ptrForBusStops->busStopName == busStopName)
			{
				return true;
			}
			ptrForBusStops = ptrForBusStops->right;
		}
		ptr = ptr->next;
	}
	return false;

}

void linkedlistutils::pathfinder(){
	string starting;
	string hedef;
	cout << "Where are you now?" << endl;
	cin >> starting;
	cout << "Where do you want to go?" << endl;
	cin >> hedef;
	if ((!existingStops(starting)) || (!existingStops(hedef)))
	{
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
	}
	else if (starting == hedef){
		cout << "You are already at that bus stop!" << endl;
	}
	else
	{
		pathfinder2(starting, hedef);
	}

}

void linkedlistutils::pathfinder2(string starting, string hedef){
	busLine * ptr = head;
	bool done = false;
	bool foundBoth = false;
	while (ptr != NULL && done == false)
	{
		bool foundS = false;
		bool foundH = false;
		busStop * ptrForBusStops = ptr->busStops;  
		while (ptrForBusStops != NULL && foundBoth != true)
		{
			if (ptrForBusStops->busStopName == starting && ptrForBusStops->busStopName != hedef)
			{
				foundS = true;
			}
			else if (ptrForBusStops->busStopName != starting && ptrForBusStops->busStopName == hedef){
				foundH = true;
			}
			if (foundH == true && foundS == true) // they are at the same line
			{
				foundBoth = true;
			}
			ptrForBusStops = ptrForBusStops->right;
		}
		if (foundBoth == true)
		{
			busStop * ptr2 = ptr->busStops;
			while (ptr2 != NULL && done == false)
			{
				if (ptr2->busStopName == hedef || ptr2->busStopName == starting)
				{
					if (ptr2->busStopName == starting)
					{
						cout << ptr->busLineName << ": ";
						while (ptr2->busStopName != hedef)
						{
							cout << ptr2->busStopName << "->";
							ptr2 = ptr2->right;
						}
						cout << ptr2->busStopName;
						done = true;
					}
					else if (ptr2->busStopName == hedef)
					{
						cout << ptr->busLineName << ":";
						busStop * temp = ptr2;
						while (done == false)
						{
							if (ptr2->busStopName == starting){
								while(ptr2->busStopName != temp->busStopName){
									cout << ptr2->busStopName << "->";
									ptr2 = ptr2->left;
								}
								cout << ptr2->busStopName;
								done = true;
							}
							else{
								ptr2 = ptr2->right;
							}
						}
					}
				}
				else
				{
					ptr2 = ptr2->right;
				}
			}
		}
		else
		{
			ptr = ptr->next;
		}
	}
	if (foundBoth == false) // check all lines, then give the message
	{
		cout << "Sorry no path from " << starting << " to " << hedef << " could be found." << endl;
	}
}


void linkedlistutils::PrintBusLines()
{
	busStop * ptrForBusStops = NULL;
	busLine * copyHead = head;
	while ( copyHead != NULL)
	{
		ptrForBusStops = copyHead->busStops;
		cout << copyHead->busLineName << ": ";
		do
		{
			if (ptrForBusStops->right == NULL)
			{
				cout << ptrForBusStops->busStopName;
			}
			else
			{
				cout << ptrForBusStops->busStopName << " <-> ";
			}
			ptrForBusStops = ptrForBusStops->right;
		} while (ptrForBusStops != NULL);

		copyHead = copyHead->next;
		cout << endl;
	}
}

void linkedlistutils::deleteList(){
	busLine * temp = head;
	while (head != NULL)
	{
		temp = head->next;
		deleteBusLine2(head->busLineName);
		head = temp;
	}
}

busLine * linkedlistutils::getHead() const
{
	return head;
}

void linkedlistutils::SetHead(string busLineNamee){
	head = new busLine(busLineNamee);
}
