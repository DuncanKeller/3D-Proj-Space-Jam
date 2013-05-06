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

bool BoundingBox::Intersects(BoundingBox* box2)
{
	// check bounds
	if(xMin > box2->xMax ||
		box2->xMin > xMax) {
		return false;
	}
	if(yMin > box2->yMax ||
		box2->yMin > yMax) {
		return false;
	}
	if(zMin > box2->zMax ||
		box2->zMin > zMax) {
		return false;
	}

	return true;
}