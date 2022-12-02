#include ".//ColorPallet.h"
ColorPallet::ColorPallet(GfxInfo shapeGfxInfo):shape(shapeGfxInfo){}
ColorPallet::~ColorPallet()
{}

void ColorPallet::Draw(GUI* pUI) const
{
	//call the function of draw color picker
	pUI->DrawColorPicker();
}

bool ColorPallet::inShape(int x, int y) const
{
	return false;
}

string ColorPallet::shapeInfo()
{
	return "";
}