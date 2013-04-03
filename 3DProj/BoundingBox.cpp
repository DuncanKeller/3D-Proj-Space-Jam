#include "DXUT.h"
#include "BoundingBox.h"


BoundingBox::BoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
	this->zMin = zMin;
	this->zMax = zMax;
}


BoundingBox::~BoundingBox(void)
{
}
