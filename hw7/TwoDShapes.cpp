#include <iostream>
#include <string>
using namespace std; 

#include "TwoDShapes.h"


void TwoDShape::setVol(){
	Vol = 0;
}

float TwoDShape::volume(){
	return Vol;
}



/********************************************************/

float Rectangle::area()
{
	return width * length;
}

float Rectangle::perimeter()
{
	return 2*(width + length);
}
