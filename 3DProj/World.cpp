#include "DXUT.h"
#include "World.h"



World::World(void)
{
	
}


World::~World(void)
{

}

void World::AddEntity(Entity e)
{
	entities.push_back(&e);
}

void World::AddEntity(Entity* e)
{
	entities.push_back(e);
}

void World::AddStation(EStation* e)
{
	entities.push_back(e);
	stations.push_back(e);
}

void World::Init(ID3D11Device* device,BoxApp* mApp)
{
	projManager = ProjectileManager();
	projManager.Init(device,this);
	playerShip = new Ship();
	entities.push_back(playerShip);
	Ship* tempShip = new Ship();
	entities.push_back(tempShip);

	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Init(device,this);
	}
	tempShip->pos=XMFLOAT3(20,0,0);

	EStation* temp = new EStation();
	temp->Init(device, this,XMFLOAT3(0,0,-100));
	AddStation(temp);
	mainApp=mApp;
}

<<<<<<< HEAD
	// asteroids
	for(int i = 0; i < 25; i++)
	{
		float x = (rand() % 800) - 400;
		float y = (rand() % 800) - 400;
		float z = (rand() % 800) - 400;
		Asteroid* a = new Asteroid();
		a->Init(device, this, XMFLOAT3(x, y, z));
		entities.push_back(a);
=======
void World::Update()
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Update();
	}
	for(std::vector<EStation*>::iterator iter = stations.begin(); iter < stations.end(); iter++)
	{
		(*iter)->SpawnFighter();
>>>>>>> 13e86b64c07722fc566db3b2696eca55a65fcb67
	}
}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
	projManager.Draw(context, tech);
}