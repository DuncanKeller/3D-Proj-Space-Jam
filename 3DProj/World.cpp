#include "DXUT.h"
#include "World.h"



World::World(void)
{
	
}


World::~World(void)
{

}

void World::Init(ID3D11Device* device,BoxApp* mApp)
{
	
	Entity* e5 = new Ship();
	entities.push_back(e5);
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Init(device,this);
	}
	mainApp=mApp;
}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
}