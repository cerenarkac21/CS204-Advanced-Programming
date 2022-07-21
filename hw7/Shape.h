#ifndef _Shape_H
#define _Shape_H

#include <string>
using namespace std;

class Shape
{
public:
	Shape(string name){
		myName = name;
	}
	virtual ~Shape(){}
	virtual float perimeter() = 0;
	virtual float area()= 0;
	virtual float volume()= 0;
	string getName() const
	{
		return myName;
	}

protected:
	string myName;
};


#endif
