#pragma once
class BoundingBox
{
public:
	BoundingBox(float, float, float, float, float, float);
	~BoundingBox(void);

	bool Intersects(BoundingBox* box2);

private:

	float xMax, xMin, yMax, yMin, zMax, zMin;
};

