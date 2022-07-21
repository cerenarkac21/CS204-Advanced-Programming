#ifndef _ThreeDShapes_H
#define _ThreeDShapes_H

#include "Shape.h"

class ThreeDShape : public Shape
{
public:
	ThreeDShape(string name):Shape(name){setPeri();}
	virtual ~ThreeDShape(){}
	virtual float volume() = 0;
	float perimeter();
	virtual float area()= 0;

protected:
	void setPeri();
	float Peri;
};

class Box : public ThreeDShape
{
public:
	Box(float w, float len, float h, string name): ThreeDShape(name), width(w), length(len), height(h){}
	float area();
	float volume();

private:
	float width, length, height;

};


#endif
