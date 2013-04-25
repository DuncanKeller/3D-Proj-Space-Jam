#include "DXUT.h"
#include "ProjectileManager.h"
#include "EmptyProject.h"
#include "World.h"
ProjectileManager::ProjectileManager(void)
{
	mesh = Mesh();
	projectiles = std::vector<Projectile*>();
	active = std::vector<Projectile*>();
}

ProjectileManager::~ProjectileManager(void)
{

}

void ProjectileManager::Init(ID3D11Device* device,World* w)
{
	mesh.Load("Assets/Projectile.obj");
	for(int i=0;i<1;i++)
	{
		Projectile* temp = new Projectile();
		temp->Init(device, w, mesh);
		projectiles.push_back(temp);
	}
}

void ProjectileManager::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	for(std::vector<Projectile*>::iterator iter = active.begin(); iter < active.end(); iter++)
	{
		(*iter)->Draw(context, tech);
	}
}

void ProjectileManager::Update(float dt)
{
	for(std::vector<Projectile*>::iterator iter = active.begin(); iter < active.end(); iter++)
	{
		XMFLOAT3 fwd = (*iter)->fwd;
		XMVECTOR temp = XMLoadFloat3(&fwd);
		temp = XMVectorScale(temp, .03);

		XMFLOAT3 temp2 = XMFLOAT3();
		XMStoreFloat3(&temp2,temp);
		(*iter)->pos.x+=temp2.x;
		(*iter)->pos.y+=temp2.y;
		(*iter)->pos.z+=temp2.z;

		(*iter)->currentLifeTime+=dt;

		if(((*iter)->currentLifeTime)>(*iter)->lifetime)
		{

		}
	}
}

void ProjectileManager::Fire(XMFLOAT4X4 mWorldNoTransl,XMFLOAT3 pos, XMFLOAT3 fwd,float vel, int lifetime)
{
	if(projectiles.size()>0)
	{
		Projectile* temp = projectiles.back();
		projectiles.pop_back();
		temp->mWorldNoTransl = mWorldNoTransl;
		temp->pos = XMFLOAT3();
		temp->pos.x = pos.x;
		temp->pos.y = pos.y;
		temp->pos.z = pos.z;
		temp->fwd = fwd;
		temp->lifetime=lifetime;
		temp->velocity=vel;

		temp->currentLifeTime=0;

		active.push_back(temp);

	}
}
