#ifndef _LINKEDLISTUTILS_H
#define _LINKEDLISTUTILS_H

#include <string>

using namespace std;

struct busStop 
{
	string busStopName;
	busStop *left;
	busStop *right;

	busStop::busStop()
	{}

	busStop::busStop(const string & busStopName_, busStop * left_ = NULL, busStop * right_ = NULL)
		:busStopName(busStopName_), left(left_), right(right_) // parametric constructor
	{};

};
struct busLine 
{
	string busLineName;
	busLine *next;
	busStop *busStops;
	busLine::busLine(string busLineName_, busLine * next_ = NULL, busStop * busStops_ = NULL)
		: busLineName(busLineName_), next(next_), busStops(busStops_){}; // parametric constructor
};



class linkedlistutils
{
public:
	linkedlistutils();// constructor
	void SetHead(string busLineNamee);
	bool ConsistencyCheck();
	busLine * getHead() const;
	void PrintBusLines();
	bool nodeExistenceCheck(string busLineName);
	bool stopExistenceCheck(string busLineName, string busStopName);
	void addBusLine2Beginning(string newBusLineName, busLine *& ptrR, busLine *& ptrD);
	void addBusLine();
	void addBusStop();
	void addBusStop2(string busStopName, busLine *& ptrR, busLine *& ptrD, busStop *& ptrForBusStops);
	void addBusStop3(string newBusLineInput, string newBusStopName, string previousBusStopName); 
	void addBusStop2Beginning(string newBusLineInput, string busStopName);
	void PrintBusLine(string busLineName);
	void deleteBusLine();
	void deleteBusLine2(string busLineName);
	void deleteBusLineWith0Stops(string busLineName);
	void deleteBusStop();
	void deleteBusStop2(string busLineName, string busStopName);
	bool existingStops(string busStopName);
	void pathfinder();
	void pathfinder2(string starting, string hedef);
	void deleteList();
private:
	busLine * head;		//Head node, start of LinkedList
};

#endif
