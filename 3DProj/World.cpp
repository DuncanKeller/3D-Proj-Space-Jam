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
	/*Ship* tempShip = new Ship();
	entities.push_back(tempShip);*/

	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Init(device,this);
	}
	//tempShip->pos=XMFLOAT3(20,0,0);

	// asteroids
	for(int i = 0; i < 25; i++)
	{
		float x = (rand() % 800) - 400;
		float y = (rand() % 800) - 400;
		float z = (rand() % 800) - 400;
		Asteroid* a = new Asteroid();
		a->Init(device, this, XMFLOAT3(x, y, z));
		entities.push_back(a);
	}

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
		for(std::vector<EFighter*>::iterator iter2 = (*iter)->fighters.begin(); iter2 < (*iter)->fighters.end(); iter2++)
		{
			(*iter2)->Update();
		}

	}

}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
	projManager.Draw(context, tech);

	for(std::vector<EStation*>::iterator iter = stations.begin(); iter < stations.end(); iter++)
	{
		for(std::vector<EFighter*>::iterator iter2 = (*iter)->fighters.begin(); iter2 < (*iter)->fighters.end(); iter2++)
		{
			(*iter2)->Draw(context, tech);
		}

	}
}