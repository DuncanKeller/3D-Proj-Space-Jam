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
}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
}