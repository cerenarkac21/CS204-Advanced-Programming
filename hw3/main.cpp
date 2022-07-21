// created by ceren arkac

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "linkedlistutils.h"

using namespace std;

void printMainMenu(){
	cout << endl;
	cout <<"I***********************************************I"<<endl
		<<"I 0 - EXIT PROGRAM I"<<endl
		<<"I 1 - PRINT LINES I"<<endl
		<<"I 2 - ADD BUS LINE I"<<endl
		<<"I 3 - ADD BUS STOP I"<<endl
		<<"I 4 - DELETE BUS LINE I"<<endl
		<<"I 5 - DELETE BUS STOP I"<<endl
		<<"I 6 - PATH FINDER I"<<endl
		<<"I***********************************************I"<<endl
		<<">>";
	cout << endl;
}

void processMainMenu(linkedlistutils linkedList) {
	char input;
	do
	{
		if (!linkedList.ConsistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
		case '0':
			cout << "Thanks for using our program" << endl;
			linkedList.deleteList();
			return;
		case '1':
			linkedList.PrintBusLines();
			break;
		case '2':
			linkedList.addBusLine();
			break;
		case '3':
			linkedList.addBusStop();
			break;
		case '4':
			linkedList.deleteBusLine();
			break;
		case '5':
			linkedList.deleteBusStop();
			break;
		case '6':
			linkedList.pathfinder();
			break;
		default:
			cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu

int main(){
	ifstream in;
	string filename = "busLines.txt";
	in.open(filename.c_str());
	string line;
	if (!in.fail())
	{
		linkedlistutils linkedList;
		busLine * ptrR = linkedList.getHead();
		busLine * ptrD = linkedList.getHead();
		busStop * ptrForBusStops = NULL;

		while (getline(in, line))
		{
			string busLineName;
			istringstream ss(line);
			while (getline(ss, busLineName , ':'))
			{
				// add busLine
				if (linkedList.getHead() == NULL)
				{
					linkedList.SetHead(busLineName);
					ptrD = linkedList.getHead();
					ptrR = linkedList.getHead();
				}
				else
				{
					
					ptrD->next = new busLine(busLineName);
					ptrD = ptrD->next;
					ptrR = ptrD;
					
				}
				string busLineStopX;
				while (ss >> busLineStopX)
				{
					
					// take the busStop
					if (ptrR->busStops == NULL)
					{
						ptrR->busStops = new busStop(busLineStopX);
						ptrForBusStops = ptrR->busStops;
					}
					else
					{
						ptrForBusStops->right = new busStop(busLineStopX);
						ptrForBusStops->right->left = ptrForBusStops;
						ptrForBusStops = ptrForBusStops->right;
					}
				}
			}
		}
		processMainMenu(linkedList);
	}
	else
	{
		cout << "cannot found the file!" << endl;
	}

	return 0;

}
