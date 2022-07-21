#ifndef _CAR_H
#define _CAR_H
#include <iostream>
#include <string>
using namespace std;

class Car
{
public:
	Car (double fuel_Level, double insurance_Fee, double total_Distance);
	//~Car();
	void setFuelLevel(double); // reduces the fuel level by the given double amount
	void setFuelLevel(); // maximize the fuel level
	void setTotalDistance(double);  // increases the total distance by amount of given double 
	void setInsuranceFee(double);  // used to increase infurance fee by the given double but in percentage
	double getFuelLevel() const;  // returns the current fuel level
	double getTotalDistance() const; // returns the current total distance
	double getInsuranceFee() const; // returns the current insurance fee
	double getMaxFuelLevel() const; // stores the fuel level which the object is initialized with
	void display(); // displays private data


private:
	double maxFuelLevel;
	double myInsuranceFee;
	double myTotalDistance;
	double myFuelLevel;
};

#endif

