#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"

class World;

class Projectile : public Entity
{
public:
	Projectile();
	~Projectile();

	void Init(ID3D11Device*,World*,Mesh m);

	float lifetime;
	int velocity;

	float currentLifeTime;
private:
	Mesh mesh;

};

#endif