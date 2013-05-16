#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"

class World;

class Ship : public Entity
{
public:
	Ship();
	~Ship();

	void Init(ID3D11Device*,World*, Mesh* m_);

	void push(float speed);
	void strafe(float speed);
	void update(float dt);

	float maxVel2;
	float vdec;

	float fireCooldown;
	float timeSinceFire;

	bool canFire;
};

#endif