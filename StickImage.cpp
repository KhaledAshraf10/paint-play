#include "StickImage.h"


StickImage::StickImage(Point p1, double Width, double Height, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{

	point1 = p1;
	width = Width;
	height = Height;
	
}

StickImage::~StickImage()
{
}

void StickImage::Draw(GUI* pUI) const
{
	pUI->DrawImage(point1, width, height, ShpGfxInfo);


}

void StickImage::SAVE(ofstream& OutFile)
{
}

bool StickImage::inShape(int, int) const
{
	return false;
}

string StickImage::shapeInfo()
{
	return string();
}

void StickImage::LOAD(ifstream& Infile)
{
}

double StickImage::getWidth()
{
	return 0.0;
}

double StickImage::getHeight()
{
	return 0.0;
}