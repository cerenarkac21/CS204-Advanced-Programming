#include <iostream>
#include <string>
using namespace std; 

#include "ThreeDShapes.h"


void ThreeDShape::setPeri(){
	Peri = 0;
}

float ThreeDShape::perimeter()
{
	return Peri;
}



/********************************************************/

float Box::area()
{
	return 2*(width*length+width*height+length*height);
}

float Box::volume()
{
	return width*length*height;

}
