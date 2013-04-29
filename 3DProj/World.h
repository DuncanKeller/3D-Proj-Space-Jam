#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include "Mesh.h"
#include "Entity.h"

#include "Ship.h"
#include "EStation.h"
<<<<<<< HEAD
#include "Asteroid.h"
=======
#include "ProjectileManager.h"

>>>>>>> 13e86b64c07722fc566db3b2696eca55a65fcb67
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

	ProjectileManager projManager;

};

