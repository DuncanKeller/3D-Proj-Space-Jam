#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"
#include "Projectile.h"

class World;

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void Init(ID3D11Device*,World*);
	void Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech);

	void Fire(XMFLOAT4X4 mWorldNoTransl,XMFLOAT3 pos, XMFLOAT3 fwd,float vel, int lifetime);
	void Update(float dt);

	std::vector<Projectile*> projectiles;
	std::vector<Projectile*> active;
	std::vector<std::vector<Projectile*>::iterator> toRemove;
private:
	Mesh mesh;

};

#endif