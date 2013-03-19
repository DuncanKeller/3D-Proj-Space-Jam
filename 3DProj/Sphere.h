#pragma once
#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct TStruct
{
	Vertex v0, v1, v2;
};


class Sphere : public Entity
{

public:
	Sphere(float centerx, float centery, float centerz, float radius);
	~Sphere(void);

	void Init(ID3D11Device*);
	std::vector<TStruct> Divide(std::vector<TStruct>);

private:
	float centerx, centery, centerz;
	float radius;
};

