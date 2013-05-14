#pragma once
#include <d3dx11.h>
#include <xnamath.h>


class BoundingBox
{
public:
	BoundingBox(float, float, float, float, float, float);
	~BoundingBox(void);

	bool Intersects(BoundingBox* box2, XMFLOAT3 pos1, XMFLOAT3 pos2);

private:

	float xMax, xMin, yMax, yMin, zMax, zMin;
};

