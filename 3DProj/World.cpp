#include "DXUT.h"
#include "World.h"


World::World(void)
{
	
}


World::~World(void)
{

}

void World::Init(ID3D11Device* device)
{
	float v[] = {
		-7, -7, 20,
		 7, -7, 20,
		 7, -7, 0
	};

	float *vertexPointer = v;

	Entity* e = new Triangle(vertexPointer);
	entities.push_back(e);

	float v2[] = {
		-7,  -7, 20,
		 7,  -7, 0,
		-7,  -7, 0
	};

	float *vertexPointer2 = v2;

	Entity* e2 = new Triangle(vertexPointer2);
	entities.push_back(e2);
	
	Entity* e3 = new Sphere(0,-5.5, 10, 1);
	entities.push_back(e3);

	Entity* e4 = new Sphere(-1,-5 , 6, 1);
	entities.push_back(e4);

	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Init(device);
	}

}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
}