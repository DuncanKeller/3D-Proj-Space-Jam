#pragma once
#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"

class Triangle : public Entity
{
public:
	Triangle(float* verts);
	~Triangle(void);

	void Init(ID3D11Device*);

private:
	float* verts;
};

