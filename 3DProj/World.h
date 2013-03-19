#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include "Entity.h"
#include "Triangle.h"
#include "Sphere.h"

class World
{
public:
	World(void);
	~World(void);
	void AddEntity(Entity);
	void TransformEntity(Entity);
	void TransformWorld();

	void Init(ID3D11Device*);
	void Draw(ID3D11DeviceContext*, ID3DX11EffectTechnique*);

	std::vector<Entity*> entities;

};

