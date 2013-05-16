#pragma once
#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"

class Asteroid  : public Entity
{
public:
	Asteroid(void);
	~Asteroid(void);
	void Init(ID3D11Device* device, World* w, XMFLOAT3 position, Mesh* m);
	void Update();

private:
	World* gWorld;
	ID3D11Device* device;

};

