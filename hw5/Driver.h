#ifndef _DRIVER_H
#define _DRIVER_H

#include <iostream>
#include <string>
#include "Car.h"
using namespace std;

class Driver
{
public:
	Driver(Car & car_, double budget_);
	//~Driver();
	void drive (double);
	void repairCar(string);
	void setBudget(double);
	void display();
	void fullFuel();

private:
	Car & myCar;
	double myBudget;
};

#endif


