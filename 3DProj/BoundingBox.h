#pragma once
class BoundingBox
{
public:
	BoundingBox(float, float, float, float, float, float);
	~BoundingBox(void);

private:

	float xMax, xMin, yMax, yMin, zMax, zMin;
};

