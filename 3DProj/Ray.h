#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>

class Ray
{
public:
	Ray(void);
	~Ray(void);

	XMFLOAT3 origin;
	XMFLOAT3 direction;
};

