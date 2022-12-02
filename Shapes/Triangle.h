#pragma once

#include "../Shapes/Shape.h"

class Triangle : public shape
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
public:
	Triangle(Point, Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Triangle();
	virtual void Draw(GUI* pUI) const;
	virtual bool inShape(int, int) const;		//check whether a point in the shape or not
	double getArea(int,int,int,int,int,int) const;						// Get the area of the triagnle 
};