#include <iostream>
using namespace std;

#include "Car.h"

Car::Car(double fuel_Level, double insurance_Fee, double total_Distance)
{
	myFuelLevel = fuel_Level;
	myInsuranceFee = insurance_Fee;
	myTotalDistance = total_Distance;
	maxFuelLevel = fuel_Level;
}

/*
Car::Car(int fuel_Level, int insurance_Fee, int total_Distance)
	: fuelLevel(fuel_Level), insuranceFee(insurance_Fee), totalDistance(total_Distance)
{ }
*/

void Car::display()
{   
	cout << "Fuel Level: " << myFuelLevel << endl;
	cout << "Insurance Fee: " << myInsuranceFee << endl;
	cout << "Total distance that the car has travelled: " << myTotalDistance << endl;
}

double Car::getFuelLevel() const
{
	return myFuelLevel;
}

void Car::setFuelLevel(double reduceAmount)
{
	myFuelLevel -= reduceAmount;
}

void Car::setFuelLevel(){
	myFuelLevel = maxFuelLevel;
}

double Car::getTotalDistance() const
{
	return myTotalDistance;
}

void Car::setTotalDistance(double increaseAmount)
{
	myTotalDistance += increaseAmount;
}

void Car::setInsuranceFee(double percentage)
{
	myInsuranceFee = ((myInsuranceFee * (100+percentage))/100);
}

double Car::getInsuranceFee() const
{
	return myInsuranceFee;
}

double Car::getMaxFuelLevel() const
{
	return maxFuelLevel;
}
