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

bool BoundingBox::Intersects(BoundingBox* box2, XMFLOAT3 pos1, XMFLOAT3 pos2)
{
	//float newMinX = XMMatrixTranslation(xMin, 0, 0);

	// check bounds
	if(xMin + pos1.x > box2->xMax + pos2.x ||
		box2->xMin + pos2.x > xMax + pos1.x) {
		return false;
	}
	if(yMin + pos1.y > box2->yMax + pos2.y ||
		box2->yMin + pos2.y > yMax + pos1.y) {
		return false;
	}
	if(zMin + pos1.z > box2->zMax + pos2.z ||
		box2->zMin + pos2.z > zMax + pos1.z) {
		return false;
	}

	return true;
}