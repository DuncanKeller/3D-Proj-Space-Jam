#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include "Mesh.h"
#include "Entity.h"

#include "Ship.h"
class BoxApp;

class World
{
public:
	World(void);
	~World(void);
	void AddEntity(Entity);
	void TransformEntity(Entity);
	void TransformWorld();

	void Init(ID3D11Device*,BoxApp*);
	void Draw(ID3D11DeviceContext*, ID3DX11EffectTechnique*);

	std::vector<Entity*> entities;
	Ship* playerShip;
	BoxApp* mainApp;

};

