#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include "Mesh.h"
#include "Entity.h"

#include "Ship.h"
#include "EStation.h"
#include "Asteroid.h"
#include "ProjectileManager.h"
#include "Skybox.h"

class BoxApp;

class World
{
public:
	World(void);
	~World(void);
	void AddEntity(Entity);
	void AddEntity(Entity*);
	void AddStation(EStation* e);
	void TransformEntity(Entity);
	void TransformWorld();

	void Init(ID3D11Device*,BoxApp*);
	void Draw(ID3D11DeviceContext*, ID3DX11EffectTechnique*);
	void Update();

	std::vector<Entity*> entities;
	std::vector<EStation*> stations;
	Ship* playerShip;
	BoxApp* mainApp;
	Skybox* skyBox;

	Mesh shipMesh;
	Mesh asteroidMesh;
	Mesh stationMesh;
	Mesh skyBoxMesh;

	ProjectileManager projManager;

};

