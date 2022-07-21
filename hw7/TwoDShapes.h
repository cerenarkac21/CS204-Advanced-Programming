#ifndef _TwoDShapes_H
#define _TwoDShapes_H

#include "Shape.h"

class TwoDShape : public Shape
{
public:
	TwoDShape(string name):Shape(name){setVol();}
	virtual ~TwoDShape(){}
	float volume();
	virtual float perimeter() = 0;
	virtual float area() = 0;

protected:
	void setVol();
	float Vol;
};

class Rectangle : public TwoDShape
{
public:
	Rectangle(float w, float len, string name): TwoDShape(name), width(w), length(len){}
	float area();
	float perimeter();

private:
	float width, length;

};

#endif
