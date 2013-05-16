#include "DXUT.h"
#include "World.h"
#include "EmptyProject.h"



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
	shipMesh = Mesh();
	shipMesh.Load("Assets/SpaceShipTex.obj");
	shipMesh.texturePath =(L"Assets/ShipTex2.bmp");

	asteroidMesh = Mesh();
	asteroidMesh.Load("Assets/asteroid.obj");
	asteroidMesh.texturePath =(L"Assets/asteroidTex.bmp");

	stationMesh = Mesh();
	stationMesh.Load("Assets/EStation.obj");
	stationMesh.texturePath =(L"Assets/spacestation.bmp");

	skyBoxMesh = Mesh();
	asteroidMesh.Load("Assets/asteroid.obj");

	projManager = ProjectileManager();
	projManager.Init(device,this);
	playerShip = new Ship();
	playerShip->Init(device, this,&shipMesh);
	entities.push_back(playerShip);

	skyBox = new Skybox();
	skyBox->Init(device,this,&asteroidMesh);
	//Ship* tempShip = new Ship();
	//entities.push_back(tempShip);

// 	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
// 	{
// 		(*iter)->Init(device,this);
// 	}
	//tempShip->pos=XMFLOAT3(20,0,0);

	// asteroids
	for(int i = 0; i < 25; i++)
	{
		float x = (rand() % 800) - 400;
		float y = (rand() % 800) - 400;
		float z = (rand() % 800) - 400;
		Asteroid* a = new Asteroid();
		a->Init(device, this, XMFLOAT3(x, y, z), &asteroidMesh);
		entities.push_back(a);
	}

	EStation* temp = new EStation();
	temp->Init(device, this,XMFLOAT3(0,0,-100),&stationMesh);
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
	skyBox->Update();
}

void World::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter < entities.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}

	projManager.Draw(context, mainApp->mTech2);
	skyBox->Draw(context,mainApp->mTechSkyBox);
}