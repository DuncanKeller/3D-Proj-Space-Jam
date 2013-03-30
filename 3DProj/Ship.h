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

	void Init(ID3D11Device*,World*);
private:
	Mesh mesh;

};

#endif