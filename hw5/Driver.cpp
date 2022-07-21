#include <iostream>
using namespace std;

#include "Driver.h"

Driver::Driver(Car & car_, double budget_)
	: myCar(car_), myBudget(budget_)
{}

void Driver::drive(double km){
	double wasted = km * 0.25;
	myCar.setFuelLevel(wasted);
	myCar.setTotalDistance(km);
}

void Driver::repairCar(string accidentType){
	double lowerBudget;
	if (accidentType == "SMALL")
	{
		lowerBudget = 50;
		myCar.setInsuranceFee(5);
	}
	else if (accidentType == "MEDIUM")
	{
		lowerBudget = 150;
		myCar.setInsuranceFee(10);
	}
	else if (accidentType == "LARGE")
	{
		lowerBudget = 300;
		myCar.setInsuranceFee(20);
	}
	setBudget(lowerBudget);
	cout << lowerBudget << "$ is reduced from the driver's budget because of the " << accidentType << " accident" << endl;
	cout << "Yearly insurance fee is increased to " << myCar.getInsuranceFee() << " because of the " << accidentType << " accident" << endl;

}

void Driver::setBudget(double reduceAmount){
	myBudget -= reduceAmount;
}


void Driver::display(){
	cout << "Driver Budget: " << myBudget << endl;
}

void Driver::fullFuel(){
	setBudget(myCar.getMaxFuelLevel()-myCar.getFuelLevel());
	myCar.setFuelLevel();
	cout << "Fuel is full" << endl;
}
