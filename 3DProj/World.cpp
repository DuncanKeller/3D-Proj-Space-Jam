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
	entities.push_back(temp);
	mainApp=mApp;
}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
	projManager.Draw(context, tech);
}