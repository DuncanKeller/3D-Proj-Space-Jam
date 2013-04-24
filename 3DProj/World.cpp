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

void World::Update()
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Update();
	}
	for(std::vector<EStation*>::iterator iter = stations.begin(); iter < stations.end(); iter++)
	{
		(*iter)->SpawnFighter();
	}
}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
}